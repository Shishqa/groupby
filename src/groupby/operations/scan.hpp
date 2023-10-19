#pragma once

#include <iterator>

#include "groupby/relation/relation.hpp"

namespace groupby::ops {

void Scan(RelationIn in, RelationOut out);

}  // namespace groupby::ops
