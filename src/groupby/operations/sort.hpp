#pragma once

#include <fstream>
#include <queue>
#include <tuple>

#include "groupby/memory/block_manager.hpp"
#include "scan.hpp"

namespace groupby {

class SortedScanOperation {
 public:
  SortedScanOperation(RelationIn reader, size_t key_idx);

  SortedScanOperation(const SortedScanOperation& other) = delete;
  SortedScanOperation(SortedScanOperation&& other) = delete;

  Record& operator*();
  Record* operator->();

  SortedScanOperation& operator++();

  bool End();

 private:
  void Prepare(RelationIn reader);

  std::vector<std::fstream> files_;
  std::vector<ScanOperation> cursors_;
  std::priority_queue<std::pair<int_t, size_t>> order_;
  size_t key_idx_;
};

}  // namespace groupby
