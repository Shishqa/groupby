#pragma once

#include <istream>
#include <ostream>
#include <variant>
#include <vector>

#include "value.hpp"

namespace groupby {

struct Record {
  static constexpr char CSV_DELIM = ',';
  std::vector<std::string> values;

  [[nodiscard]] Value Get(size_t idx) const;
};

std::istream& operator>>(std::istream& in, Record& r);
std::ostream& operator<<(std::ostream& out, const Record& r);

}  // namespace groupby
