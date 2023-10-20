#include "record.hpp"

#include <sstream>
#include <wheels/string.hpp>

#include "value.hpp"

namespace groupby {

std::istream& operator>>(std::istream& in, Record& r) {
  std::string line{};
  auto& res = std::getline(in, line);

  r.values.clear();
  for (auto str : wheels::str::Split(line, Record::CSV_DELIM)) {
    std::istringstream ss(std::move(str));
    Value v{};
    ss >> v;
    r.values.emplace_back(std::move(v));
  }

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
