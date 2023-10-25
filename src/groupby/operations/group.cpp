#include "group.hpp"

#include "aggregate.hpp"
#include "groupby/memory/block_manager.hpp"
#include "sort.hpp"

namespace groupby {

GroupOperation::GroupOperation(size_t key_idx, size_t agg_idx,
                               AggregatorList aggs)
    : key_idx_(key_idx), agg_idx_(agg_idx), aggs_(std::move(aggs)) {
}

//

SortedGroupOperation::SortedGroupOperation(SortedScanOperation& reader,
                                           size_t key_idx, size_t agg_idx,
                                           AggregatorList aggs)
    : GroupOperation(key_idx, agg_idx, std::move(aggs)), reader_(reader) {
  ConsumeRecord();
}

void SortedGroupOperation::ConsumeRecord() {
  r_.values.clear();

  /* aggs + key */
  r_.values.reserve(aggs_.size() + 1);
  for (auto& agg : aggs_) {
    auto& a = r_.values.emplace_back(agg->Init());
    agg->Aggregate(a, reader_->values.at(agg_idx_));
  }
  auto key = reader_->values.at(key_idx_);
  r_.values.emplace_back(std::move(key));

  while (!(++reader_).End() && reader_->values.at(key_idx_) == key) {
    for (size_t i = 0; i < aggs_.size(); ++i) {
      aggs_[i]->Aggregate(r_.values[i], reader_->values.at(agg_idx_));
    }
  }
}

Record& SortedGroupOperation::operator*() {
  return r_;
}

Record* SortedGroupOperation::operator->() {
  return &r_;
}

SortedGroupOperation& SortedGroupOperation::operator++() {
  if (!End()) {
    ConsumeRecord();
  }
  return *this;
}

bool SortedGroupOperation::End() {
  return reader_.End();
}

//////////////////////////////////////////////////////////////////////////////////

HashedGroupOperation::HashedGroupOperation(ScanOperation& reader,
                                           size_t key_idx, size_t agg_idx,
                                           AggregatorList aggs)
    : GroupOperation(key_idx, agg_idx, std::move(aggs)), reader_(reader) {
  ConsumeAll();
}

void HashedGroupOperation::ConsumeAll() {
  for (; !reader_.End(); ++reader_) {
    auto key = std::get<int_t>(reader_->values.at(key_idx_));
    if (!records_.count(key)) {
      records_[key].values.clear();
      for (auto& agg : aggs_) {
        auto& a = records_[key].values.emplace_back(agg->Init());
        agg->Aggregate(a, reader_->values.at(agg_idx_));
      }
      records_[key].values.emplace_back(key);
    } else {
      auto& r = records_[key];
      for (size_t i = 0; i < aggs_.size(); ++i) {
        aggs_[i]->Aggregate(r.values[i], reader_->values.at(agg_idx_));
      }
    }
  }
  curr_ = records_.begin();
}

Record& HashedGroupOperation::operator*() {
  return curr_->second;
}

Record* HashedGroupOperation::operator->() {
  return &(curr_->second);
}

HashedGroupOperation& HashedGroupOperation::operator++() {
  if (!End()) {
    ++curr_;
  }
  return *this;
}

bool HashedGroupOperation::End() {
  return curr_ == records_.end();
}

}  // namespace groupby
