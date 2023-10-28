#pragma once

#include <fstream>
#include <queue>
#include <tuple>

#include "base.hpp"
#include "scan.hpp"

namespace groupby {

class SortedScanOperation : public BaseOperation {
 public:
  SortedScanOperation(std::istream& in, size_t key_idx);

  SortedScanOperation(const SortedScanOperation& other) = delete;
  SortedScanOperation(SortedScanOperation&& other) = delete;

  Record& operator*() override;
  Record* operator->() override;

  SortedScanOperation& operator++() override;

  bool End() override;

 private:
  using CursorId = std::pair<int_t, size_t>;

  void Prepare(std::istream& in);

  std::vector<std::fstream> files_;
  std::vector<ScanOperation> cursors_;
  std::priority_queue<CursorId, std::vector<CursorId>, std::greater<CursorId>>
      order_;
  size_t key_idx_;
};

}  // namespace groupby
