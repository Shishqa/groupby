#pragma once

#include <vector>

#include "block.hpp"

namespace groupby {

class BlockManager {
 public:
  static constexpr size_t M = 10;

  std::vector<Block> blocks;

  static BlockManager& Instance();

 private:
  explicit BlockManager();
};

}  // namespace groupby
