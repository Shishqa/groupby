#pragma once

#include <iterator>

#include "record.hpp"

namespace groupby {

using RelationIn = std::istream_iterator<Record>;
using RelationOut = std::ostream_iterator<Record>;

}  // namespace groupby
