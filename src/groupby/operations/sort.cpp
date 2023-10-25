#include "sort.hpp"

#include <algorithm>
#include <cassert>
#include <cstdio>

#include "groupby/memory/block_manager.hpp"
#include "groupby/relation/value.hpp"

namespace groupby {

SortedScanOperation::SortedScanOperation(RelationIn reader, size_t key_idx)
    : cursors_(), key_idx_(key_idx) {
  Prepare(reader);
}

void SortedScanOperation::Prepare(RelationIn reader) {
  auto cmp = [key_idx = key_idx_](const Record& a, const Record& b) {
    return std::get<int_t>(a.values[key_idx]) <
           std::get<int_t>(b.values[key_idx]);
  };

  {
    auto b = BlockManager::Instance().Allocate(BlockManager::M);
    assert(b->size() == 0 && b->capacity() > 0);
    for (size_t i = 0; reader != RelationIn(); ++i) {
      BlockRead(*b, reader);
      std::sort(b->begin(), b->end(), cmp);
      assert(i < 2);

      auto& file = files_.emplace_back(
          ".sorted-" + std::to_string(i),
          std::fstream::in | std::fstream::out | std::fstream::trunc);

      RelationOut out(file);
      BlockWrite(*b, out);
      file.flush();
      file.seekg(0);
    }
  }

  assert(files_.size() <= BlockManager::M - 1);

  for (size_t i = 0; i < files_.size(); ++i) {
    auto& c = cursors_.emplace_back(RelationIn(files_[i]));
    order_.emplace(std::get<int_t>(c->values.at(key_idx_)), i);
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
  if (!cursor.End()) {
    ++cursor;
    if (!cursor.End()) {
      order_.emplace(std::get<int_t>(cursor->values.at(key_idx_)), top.second);
    } else {
      std::remove((".sorted-" + std::to_string(top.second)).data());
    }
  }
  return *this;
}

bool SortedScanOperation::End() {
  return order_.empty();
}

}  // namespace groupby
