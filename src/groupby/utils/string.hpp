#pragma once

#include <string>
#include <vector>

namespace groupby {

std::vector<std::string> Split(std::string_view s, char c);
std::string Join(const std::vector<std::string>& v, char c);

}  // namespace groupby
