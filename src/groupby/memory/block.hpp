#pragma once

#include <vector>

#include "groupby/relation/record.hpp"
#include "groupby/relation/relation.hpp"

namespace groupby {

using Block = std::vector<Record>;

void BlockRead(Block& b, RelationIn& in);
void BlockWrite(const Block& b, RelationOut& out);

}  // namespace groupby
