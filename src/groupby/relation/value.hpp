#pragma once

#include <cstdint>
#include <istream>
#include <ostream>
#include <variant>
#include <vector>

namespace groupby {

using str_t = std::string;
using int_t = std::int64_t;
using Value = std::variant<str_t, int_t>;

std::istream& operator>>(std::istream& in, Value& v);
std::ostream& operator<<(std::ostream& out, const Value& v);

}  // namespace groupby
