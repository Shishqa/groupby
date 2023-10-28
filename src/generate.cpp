#include <fstream>
#include <groupby/utils/data.hpp>
#include <iostream>
#include <sstream>
#include <string_view>

void print_help(std::string_view prog_name) {
  std::cout << "usage: " << prog_name << " <dist_type> <n_cols> <n_rows>\n\n"
            << "\targuments:\n"
            << "\t\tdist_type - distribution type (small, big, monotonic)\n"
            << "\t\tn_cols - number of columns\n"
            << "\t\tn_rows - number of rows\n";
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cerr << "error: wrong number of arguments\n";
    print_help(argv[0]);
    return 1;
  }

  size_t n_cols = std::strtoull(argv[2], nullptr, 10);
  size_t n_rows = std::strtoull(argv[3], nullptr, 10);

  if (std::string("small") == argv[1]) {
    groupby::testing::GenerateData(std::cout,
                                   groupby::testing::SmallRangeData::Instance(),
                                   n_rows, n_cols);
  } else if (std::string("big") == argv[1]) {
    groupby::testing::GenerateData(std::cout,
                                   groupby::testing::SmallRangeData::Instance(),
                                   n_rows, n_cols);
  } else if (std::string("monotonic") == argv[1]) {
    groupby::testing::GenerateData(std::cout,
                                   groupby::testing::SmallRangeData::Instance(),
                                   n_rows, n_cols);
  } else {
    std::cerr << "bad distribution type: " << argv[1] << "\n";
    print_help(argv[0]);
    return 1;
  }

  return 0;
}
