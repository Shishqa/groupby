#include "sort.hpp"

#include <algorithm>
#include <cassert>
#include <cstdio>

#include "groupby/relation/value.hpp"
#include "groupby/settings.hpp"

namespace groupby {

SortedScanOperation::SortedScanOperation(std::istream& in, size_t key_idx)
    : cursors_(), key_idx_(key_idx) {
  Prepare(in);
}

void SortedScanOperation::Prepare(std::istream& in) {
  auto cmp = [key_idx = key_idx_](const Record& a, const Record& b) {
    return std::get<int_t>(a.Get(key_idx)) < std::get<int_t>(b.Get(key_idx));
  };

  {
    ScanOperation scan(in, Settings::Instance().BLOCKS_IN_MEMORY);
    for (size_t i = 0; !scan.End(); ++i, scan.NextBlock()) {
      auto& b = scan.GetBlock();
      std::sort(b.begin(), b.end(), cmp);

      auto& file = files_.emplace_back(
          ".sorted-" + std::to_string(i),
          std::fstream::in | std::fstream::out | std::fstream::trunc);
      assert(files_.size() <= Settings::Instance().BLOCKS_IN_MEMORY - 1);

      WriteOperation writer(file, Settings::Instance().BLOCKS_IN_MEMORY);
      writer.WriteBlock(b);
      file.flush();
      file.seekg(0);
    }
  }

  for (size_t i = 0; i < files_.size(); ++i) {
    auto& c = cursors_.emplace_back(files_[i], 1);
    order_.emplace(std::get<int_t>(c->Get(key_idx_)), i);
  }
}

Record& SortedScanOperation::operator*() {
  auto& top = order_.top();
  return *cursors_[top.second];
}

Record* SortedScanOperation::operator->() {
  return &(**this);
}

SortedScanOperation& SortedScanOperation::operator++() {
  auto top = order_.top();
  order_.pop();

  auto& cursor = cursors_[top.second];
  ++cursor;
  if (!cursor.End()) {
    order_.emplace(std::get<int_t>(cursor->Get(key_idx_)), top.second);
  } else {
    std::remove((".sorted-" + std::to_string(top.second)).data());
  }
  return *this;
}

bool SortedScanOperation::End() {
  return order_.empty();
}

}  // namespace groupby
