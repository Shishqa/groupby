#pragma once

#include <list>
#include <optional>

#include "block.hpp"

namespace groupby {

class BlockManager {
 public:
  static constexpr size_t M = 10;
  static constexpr size_t B_SIZE = 1024;

  static BlockManager& Instance();

  class BlockHandle {
   public:
    explicit BlockHandle() = default;
    BlockHandle(std::list<Block>::iterator handle);
    ~BlockHandle();

    BlockHandle(const BlockHandle& other) = delete;

    BlockHandle(BlockHandle&& other);
    BlockHandle& operator=(BlockHandle&& other);

    Block& operator*();
    Block* operator->();

   private:
    std::optional<std::list<Block>::iterator> handle_;
  };

  BlockHandle Allocate(size_t m);

  friend class BlockHandle;

 private:
  void Deallocate(std::list<Block>::iterator b);

  explicit BlockManager();

 private:
  std::list<Block> blocks_;
  size_t size_;
};

}  // namespace groupby
