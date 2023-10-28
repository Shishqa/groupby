#include "string.hpp"

namespace groupby {

std::vector<std::string> Split(std::string_view s, char c) {
  std::vector<std::string> res{};
  for (;;) {
    auto pos = s.find(c);
    res.emplace_back(s.substr(0, pos));
    if (pos == std::string_view::npos) {
      break;
    }
    s = s.substr(pos + 1);
  }
  return res;
}

std::string Join(const std::vector<std::string>& v, char c) {
  std::string res = "";
  for (size_t i = 0; i < v.size(); ++i) {
    if (i != 0) {
      res.append(1, c);
    }
    res.append(v[i]);
  }
  return res;
}

}  // namespace groupby
