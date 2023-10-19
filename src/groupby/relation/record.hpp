#pragma once

#include <istream>
#include <ostream>
#include <vector>

namespace groupby {

struct Record {
 public:
  static constexpr char CSV_DELIM = ',';

  friend std::istream& operator>>(std::istream& in, Record& r);
  friend std::ostream& operator<<(std::ostream& out, const Record& r);

  std::vector<std::string> values;
};

}  // namespace groupby
