#include "scan.hpp"

#include "groupby/memory/block_manager.hpp"

namespace groupby::ops {

void Scan(RelationIn from, RelationOut out) {
  Block& b = BlockManager::Instance().blocks[0];
  while (from != RelationIn()) {
    from = b.read(from);
    out = b.write(out);
  }
}

}  // namespace groupby::ops
