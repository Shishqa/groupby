#include "value.hpp"

#include <sstream>

namespace groupby {

std::istream& operator>>(std::istream& in, Value& v) {
  v.emplace<int_t>();
  if (in >> std::get<int_t>(v)) {
    return in;
  }

  v.emplace<str_t>();
  in >> std::get<str_t>(v);

  return in;
}

std::ostream& operator<<(std::ostream& out, const Value& v) {
  switch (v.index()) {
    case 0:
      out << std::get<0>(v);
      break;
    case 1:
      out << std::get<1>(v);
      break;
    default:
      break;
  }
  return out;
}

}  // namespace groupby
