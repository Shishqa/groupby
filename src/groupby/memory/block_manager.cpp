#include "block_manager.hpp"

#include <cassert>
#include <new>

namespace groupby {

BlockManager::BlockManager() : size_(0) {
}

BlockManager& BlockManager::Instance() {
  static BlockManager instance_;
  return instance_;
}

BlockManager::BlockHandle BlockManager::Allocate(size_t m) {
  assert(m > 0);
  if (size_ + m > M) {
    throw std::bad_alloc();
  }
  size_ += m;

  BlockManager::BlockHandle b(blocks_.emplace(blocks_.end()));
  b->reserve(m * B_SIZE);
  assert(b->capacity() > 0);
  return b;
}

void BlockManager::Deallocate(std::list<Block>::iterator b) {
  size_ -= b->size() / B_SIZE;
  blocks_.erase(b);
}

BlockManager::BlockHandle::BlockHandle(std::list<Block>::iterator handle)
    : handle_(handle) {
}

BlockManager::BlockHandle::BlockHandle(BlockManager::BlockHandle&& other)
    : handle_(std::move(other.handle_)) {
}

BlockManager::BlockHandle& BlockManager::BlockHandle::operator=(
    BlockManager::BlockHandle&& other) {
  if (this != &other) {
    handle_ = std::move(other.handle_);
  }
  return *this;
}

BlockManager::BlockHandle::~BlockHandle() {
  if (handle_.has_value()) {
    BlockManager::Instance().Deallocate(handle_.value());
  }
}

Block& BlockManager::BlockHandle::operator*() {
  return *handle_.value();
}

Block* BlockManager::BlockHandle::operator->() {
  return &(*handle_.value());
}

}  // namespace groupby
