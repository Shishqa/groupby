#include "request.hpp"

#include <exception>
#include <filesystem>
#include <iostream>
#include <memory>

#include "groupby/operations/aggregate.hpp"
#include "groupby/operations/group.hpp"
#include "groupby/operations/sort.hpp"
#include "groupby/settings.hpp"

namespace groupby {

RequestBuilder::RequestBuilder() {
}

RequestBuilder& RequestBuilder::From(std::string_view path) {
  file_.open(path.data());
  size_t file_size_bytes = std::filesystem::file_size(path);
  size_t large_threshold = Settings::Instance().RECORDS_IN_BLOCK *
                           Settings::Instance().BLOCKS_IN_MEMORY *
                           Settings::Instance().RECORD_SIZE;

  is_large_file_ = (file_size_bytes >= large_threshold);
  return *this;
}

RequestBuilder& RequestBuilder::GroupBy(size_t key, size_t agg_key,
                                        std::string_view agg_type) {
  if (agg_type == "max") {
    agg_ = std::make_unique<MaxAggregator>();
  } else if (agg_type == "min") {
    agg_ = std::make_unique<MinAggregator>();
  } else if (agg_type == "count") {
    agg_ = std::make_unique<CountAggregator>();
  } else {
    throw std::runtime_error("unknown aggregator type");
  }

  if (is_large_file_) {
    ops_.emplace_back(std::make_unique<SortedScanOperation>(file_, key));
    ops_.emplace_back(std::make_unique<SortedGroupOperation>(
        dynamic_cast<SortedScanOperation&>(*ops_.back().get()), key, agg_key,
        GroupOperation::AggregatorList{agg_.get()}));
  } else {
    ops_.emplace_back(std::make_unique<ScanOperation>(file_, 1));
    ops_.emplace_back(std::make_unique<HashedGroupOperation>(
        dynamic_cast<ScanOperation&>(*ops_.back().get()), key, agg_key,
        GroupOperation::AggregatorList{agg_.get()}));
  }

  return *this;
}

void RequestBuilder::Select(std::ostream& out) {
  auto& op = ops_.back();
  for (; !op->End(); ++(*op)) {
    out << *(*op);
  }
}

}  // namespace groupby
