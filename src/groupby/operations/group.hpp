#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "groupby/memory/block_manager.hpp"
#include "groupby/operations/aggregate.hpp"
#include "groupby/operations/scan.hpp"
#include "groupby/operations/sort.hpp"

namespace groupby {

class GroupOperation {
 public:
  using AggregatorList = std::vector<Aggregator*>;

  GroupOperation(size_t key_idx, size_t agg_idx, AggregatorList aggs);

  GroupOperation(const GroupOperation& other) = delete;
  GroupOperation(GroupOperation&& other) = delete;

 protected:
  size_t key_idx_;
  size_t agg_idx_;
  AggregatorList aggs_;
};

class SortedGroupOperation : public GroupOperation {
 public:
  SortedGroupOperation(SortedScanOperation& reader, size_t key_idx,
                       size_t agg_idx, AggregatorList aggs);

  Record& operator*();
  Record* operator->();

  SortedGroupOperation& operator++();

  bool End();

 private:
  void ConsumeRecord();

  Record r_;
  SortedScanOperation& reader_;
};

class HashedGroupOperation : public GroupOperation {
 public:
  HashedGroupOperation(ScanOperation& reader, size_t key_idx, size_t agg_idx,
                       AggregatorList aggs);

  Record& operator*();
  Record* operator->();

  HashedGroupOperation& operator++();

  bool End();

 private:
  void ConsumeAll();

  using RecordBuckets = std::unordered_map<int_t, Record>;

  ScanOperation& reader_;
  RecordBuckets::iterator curr_;
  RecordBuckets records_;
};

}  // namespace groupby
