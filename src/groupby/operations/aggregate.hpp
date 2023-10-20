#pragma once

#include <iterator>

#include "groupby/relation/relation.hpp"

namespace groupby::ops {

using Aggregator =

    void Scan(RelationIn in, RelationOut out);

}  // namespace groupby::ops
