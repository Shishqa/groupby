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

  SortedScanOperation(SortedScanOperation&& other);
  SortedScanOperation& operator=(SortedScanOperation&& other);

  Record& operator*();
  Record* operator->();

  SortedScanOperation& operator++();

  bool End();

 private:
  void Prepare(RelationIn reader);

  struct Cursor {
    std::ifstream file;
    ScanOperation reader;

    Cursor(std::ifstream f);
  };

  std::vector<Cursor> cursors_;
  std::priority_queue<std::tuple<int_t, size_t>> order_;
  size_t key_idx_;
};

}  // namespace groupby
