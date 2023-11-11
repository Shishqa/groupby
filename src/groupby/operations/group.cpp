#include "group.hpp"

#include <sstream>

#include "aggregate.hpp"
#include "sort.hpp"

namespace groupby {

GroupOperation::GroupOperation(BaseOperation& reader, size_t key_idx,
                               size_t agg_idx, AggregatorList aggs)
    : key_idx_(key_idx),
      agg_idx_(agg_idx),
      aggs_(std::move(aggs)),
      reader_(reader) {
}

//

SortedGroupOperation::SortedGroupOperation(SortedScanOperation& reader,
                                           size_t key_idx, size_t agg_idx,
                                           AggregatorList aggs)
    : GroupOperation(reader, key_idx, agg_idx, std::move(aggs)), end_(false) {
  ConsumeRecord();
}

void SortedGroupOperation::ConsumeRecord() {
  r_.values.clear();

  auto key = reader_->Get(key_idx_);

  std::vector<Value> key_aggs{};
  for (auto& agg : aggs_) {
    key_aggs.emplace_back(agg->Init());
  }

  for (; !reader_.End() && reader_->Get(key_idx_) == key; ++reader_) {
    for (size_t i = 0; i < aggs_.size(); ++i) {
      aggs_[i]->Aggregate(key_aggs[i], reader_->Get(agg_idx_));
    }
  }

  std::ostringstream os{};
  os << key;
  r_.values.emplace_back(os.str());
  for (auto agg : key_aggs) {
    std::ostringstream os{};
    os << agg;
    r_.values.emplace_back(os.str());
  }
}

Record& SortedGroupOperation::operator*() {
  return r_;
}

Record* SortedGroupOperation::operator->() {
  return &r_;
}

SortedGroupOperation& SortedGroupOperation::operator++() {
  if (reader_.End()) {
    end_ = true;
  } else {
    ConsumeRecord();
  }
  return *this;
}

bool SortedGroupOperation::End() {
  return end_;
}

//////////////////////////////////////////////////////////////////////////////////

HashedGroupOperation::HashedGroupOperation(ScanOperation& reader,
                                           size_t key_idx, size_t agg_idx,
                                           AggregatorList aggs)
    : GroupOperation(reader, key_idx, agg_idx, std::move(aggs)) {
  ConsumeAll();
}

void HashedGroupOperation::ConsumeAll() {
  for (; !reader_.End(); ++reader_) {
    auto key = std::get<int_t>(reader_->Get(key_idx_));
    if (!records_.count(key)) {
      records_[key].clear();
      for (auto& agg : aggs_) {
        auto& a = records_[key].emplace_back(agg->Init());
        agg->Aggregate(a, reader_->Get(agg_idx_));
      }
    } else {
      auto& r = records_[key];
      for (size_t i = 0; i < aggs_.size(); ++i) {
        aggs_[i]->Aggregate(r.at(i), reader_->Get(agg_idx_));
      }
    }
  }
  curr_ = records_.begin();
  ConsumeRecord();
}

void HashedGroupOperation::ConsumeRecord() {
  record_.values.clear();
  std::ostringstream os{};
  os << curr_->first;
  record_.values.emplace_back(os.str());
  for (auto& agg : curr_->second) {
    std::ostringstream os{};
    os << agg;
    record_.values.emplace_back(os.str());
  }
}

Record& HashedGroupOperation::operator*() {
  return record_;
}

Record* HashedGroupOperation::operator->() {
  return &record_;
}

HashedGroupOperation& HashedGroupOperation::operator++() {
  if (!End()) {
    ++curr_;
    if (!End()) {
      ConsumeRecord();
    }
  }
  return *this;
}

bool HashedGroupOperation::End() {
  return curr_ == records_.end();
}

}  // namespace groupby
