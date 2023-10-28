#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "groupby/operations/aggregate.hpp"
#include "groupby/operations/scan.hpp"
#include "groupby/operations/sort.hpp"

namespace groupby {

class GroupOperation : public BaseOperation {
 public:
  using AggregatorList = std::vector<Aggregator*>;

  GroupOperation(BaseOperation& reader, size_t key_idx, size_t agg_idx,
                 AggregatorList aggs);

  GroupOperation(const GroupOperation& other) = delete;
  GroupOperation(GroupOperation&& other) = delete;

 protected:
  size_t key_idx_;
  size_t agg_idx_;
  AggregatorList aggs_;
  BaseOperation& reader_;
};

class SortedGroupOperation : public GroupOperation {
 public:
  SortedGroupOperation(SortedScanOperation& reader, size_t key_idx,
                       size_t agg_idx, AggregatorList aggs);

  Record& operator*() override;
  Record* operator->() override;

  SortedGroupOperation& operator++() override;

  bool End() override;

 private:
  void ConsumeRecord();

  Record r_;
  bool end_;
};

class HashedGroupOperation : public GroupOperation {
 public:
  HashedGroupOperation(ScanOperation& reader, size_t key_idx, size_t agg_idx,
                       AggregatorList aggs);

  Record& operator*() override;
  Record* operator->() override;

  HashedGroupOperation& operator++() override;

  bool End() override;

 private:
  void ConsumeAll();

  using RecordBuckets = std::unordered_map<int_t, Record>;

  RecordBuckets::iterator curr_;
  RecordBuckets records_;
};

}  // namespace groupby
