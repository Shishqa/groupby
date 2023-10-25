#include "block_manager.hpp"

#include <new>

namespace groupby {

BlockManager::BlockManager() : size_(0) {
}

BlockManager& BlockManager::Instance() {
  static BlockManager instance_;
  return instance_;
}

BlockManager::BlockHandle BlockManager::Allocate(size_t m) {
  if (size_ + m > M) {
    throw std::bad_alloc();
  }
  size_ += m;

  Block b{};
  b.reserve(m * B_SIZE);
  return blocks_.emplace(blocks_.end(), std::move(b));
}

void BlockManager::Deallocate(std::list<Block>::iterator b) {
  size_ -= b->size() / B_SIZE;
  blocks_.erase(b);
}

BlockManager::BlockHandle::BlockHandle(std::list<Block>::iterator handle)
    : handle_(handle) {
}

BlockManager::BlockHandle::BlockHandle(BlockManager::BlockHandle&& other)
    : handle_(other.handle_) {
  other.handle_.reset();
}

BlockManager::BlockHandle& BlockManager::BlockHandle::operator=(
    BlockManager::BlockHandle&& other) {
  if (this != &other) {
    handle_ = std::move(other.handle_);
    other.handle_.reset();
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
