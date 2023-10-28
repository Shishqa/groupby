#include <fstream>
#include <groupby/request.hpp>
#include <iostream>
#include <sstream>
#include <string_view>

void print_help(std::string_view prog_name) {
  std::cout
      << "usage: " << prog_name
      << " <path> <grouping_field> <aggregation_field> <aggregation_type>\n\n"
      << "\targuments:\n"
      << "\t\tpath - path to your csv file\n"
      << "\t\tgrouping_field - idx of field to group by\n"
      << "\t\taggregation_field - idx of field to aggregate by groups\n"
      << "\t\taggregation_type - which function to use for aggregation (min, "
         "max, count)\n";
}

int main(int argc, char* argv[]) {
  if (argc != 5) {
    std::cerr << "error: wrong number of arguments\n";
    print_help(argv[0]);
    return 1;
  }

  size_t key_idx = std::strtoull(argv[2], nullptr, 10);
  size_t agg_idx = std::strtoull(argv[3], nullptr, 10);

  groupby::RequestBuilder()
      .From(argv[1])
      .GroupBy(key_idx, agg_idx, argv[4])
      .Select(std::cout);

  return 0;
}
