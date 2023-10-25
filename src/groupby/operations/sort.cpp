#include "sort.hpp"

#include <algorithm>
#include <cassert>

#include "groupby/memory/block_manager.hpp"
#include "groupby/relation/value.hpp"

namespace groupby {

SortedScanOperation::Cursor::Cursor(std::ifstream f)
    : file(std::move(f)), reader(RelationIn(file)) {
}

SortedScanOperation::SortedScanOperation(RelationIn reader, size_t key_idx)
    : cursors_(), key_idx_(key_idx) {
  Prepare(reader);
}

SortedScanOperation::SortedScanOperation(SortedScanOperation&& other)
    : cursors_(std::move(other.cursors_)),
      order_(std::move(other.order_)),
      key_idx_(other.key_idx_) {
}

SortedScanOperation& SortedScanOperation::operator=(
    SortedScanOperation&& other) {
  if (this != &other) {
    cursors_ = std::move(other.cursors_);
    order_ = std::move(other.order_);
    key_idx_ = other.key_idx_;
  }
  return *this;
}

void SortedScanOperation::Prepare(RelationIn reader) {
  auto cmp = [key_idx = key_idx_](const Record& a, const Record& b) {
    return std::get<int_t>(a.values[key_idx]) <
           std::get<int_t>(b.values[key_idx]);
  };

  size_t n_cursors = 0;
  {
    auto b = BlockManager::Instance().Allocate(BlockManager::M);
    while (reader != RelationIn()) {
      reader = BlockRead(*b, reader);
      std::sort(b->begin(), b->end(), cmp);
      std::ofstream file(".sorted-" + std::to_string(n_cursors++));
      BlockWrite(*b, RelationOut(file));
    }
  }

  assert(n_cursors <= BlockManager::M - 1);

  for (size_t i = 0; i < n_cursors; ++i) {
    std::ifstream file(".sorted-" + std::to_string(i));
    auto& c = cursors_.emplace_back(std::move(file));
    order_.emplace(std::get<int_t>(c.reader->values.at(key_idx_)), i);
  }
}

Record& SortedScanOperation::operator*() {
  auto& top = order_.top();
  return *cursors_[std::get<1>(top)].reader;
}

Record* SortedScanOperation::operator->() {
  return &(**this);
}

SortedScanOperation& SortedScanOperation::operator++() {
  auto top = order_.top();
  order_.pop();

  auto& cursor = cursors_[std::get<1>(top)];
  if (!cursor.reader.End()) {
    ++cursor.reader;
    order_.emplace(std::get<int_t>(cursor.reader->values.at(key_idx_)),
                   std::get<0>(top));
  }
  return *this;
}

bool SortedScanOperation::End() {
  return order_.empty();
}

}  // namespace groupby
