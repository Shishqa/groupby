#pragma once

#include <vector>

#include "groupby/relation/record.hpp"
#include "groupby/relation/relation.hpp"

namespace groupby {

class Block {
 public:
  static constexpr size_t SIZE = 1024;

  std::vector<Record> records;

  explicit Block();

  RelationIn read(RelationIn in);
  RelationOut write(RelationOut out);
};

}  // namespace groupby
