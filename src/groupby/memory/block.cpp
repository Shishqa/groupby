#include "block.hpp"

#include <iostream>

namespace groupby {

Block::Block() {
  records.reserve(SIZE);
}

RelationIn Block::read(RelationIn in) {
  records.clear();
  auto end = RelationIn();
  for (; in != end && records.size() < SIZE; ++in) {
    records.emplace_back(std::move(*in));
  }
  return in;
}

RelationOut Block::write(RelationOut out) {
  for (size_t i = 0; i < records.size(); ++i, ++out) {
    *out = records[i];
  }
  records.clear();
  return out;
}

}  // namespace groupby
