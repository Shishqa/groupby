#include "record.hpp"

#include <sstream>

#include "groupby/utils/string.hpp"
#include "value.hpp"

namespace groupby {

Value Record::Get(size_t idx) const {
  std::istringstream ss{values.at(idx)};
  Value v{};
  ss >> v;
  return v;
}

std::istream& operator>>(std::istream& in, Record& r) {
  std::string line{};
  auto& res = std::getline(in, line);
  r.values = Split(line, Record::CSV_DELIM);
  return res;
}

std::ostream& operator<<(std::ostream& out, const Record& r) {
  for (size_t i = 0; i < r.values.size(); ++i) {
    out << r.values[i];
    if (i != r.values.size() - 1) {
      out << Record::CSV_DELIM;
    } else {
      out << "\n";
    }
  }
  return out;
}

}  // namespace groupby
