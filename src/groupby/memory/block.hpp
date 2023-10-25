#pragma once

#include <vector>

#include "groupby/relation/record.hpp"
#include "groupby/relation/relation.hpp"

namespace groupby {

using Block = std::vector<Record>;

RelationIn BlockRead(Block& b, RelationIn in);
RelationOut BlockWrite(const Block& b, RelationOut out);

}  // namespace groupby
