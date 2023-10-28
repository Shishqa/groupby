#pragma once

#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "groupby/operations/aggregate.hpp"
#include "groupby/operations/group.hpp"
#include "groupby/operations/sort.hpp"

namespace groupby {

class RequestBuilder {
 public:
  RequestBuilder();

  RequestBuilder& From(std::string_view path);

  RequestBuilder& GroupBy(size_t key, size_t agg_key,
                          std::string_view agg_type);

  void Select(std::ostream& out);

 private:
  std::ifstream file_;
  bool is_large_file_;
  std::unique_ptr<Aggregator> agg_{};
  std::vector<std::unique_ptr<BaseOperation>> ops_{};
};

}  // namespace groupby
