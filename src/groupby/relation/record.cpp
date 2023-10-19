#include "record.hpp"

#include <wheels/string.hpp>

namespace groupby {

std::istream& operator>>(std::istream& in, Record& r) {
  std::string line{};
  auto& res = std::getline(in, line);
  r.values = wheels::str::Split(line, Record::CSV_DELIM);
  return res;
}

std::ostream& operator<<(std::ostream& out, const Record& r) {
  out << wheels::str::Join(r.values, Record::CSV_DELIM) << "\n";
  return out;
}

}  // namespace groupby
