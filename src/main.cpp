#include <fstream>
#include <groupby/operations/aggregate.hpp>
#include <groupby/operations/group.hpp>
#include <groupby/operations/sort.hpp>
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

  std::ifstream file(argv[1]);

  groupby::MaxAggregator agg{};
  groupby::SortedGroupOperation group(
      groupby::SortedScanOperation(groupby::RelationIn(file), key_idx), key_idx,
      agg_idx, {&agg});

  while (!group.End()) {
    std::cout << *group;
    ++group;
  }

  return 0;
}
