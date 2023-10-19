#include "block_manager.hpp"

namespace groupby {

BlockManager::BlockManager() {
  blocks.reserve(M);
}

BlockManager& BlockManager::Instance() {
  static BlockManager instance_;
  return instance_;
}

}  // namespace groupby
