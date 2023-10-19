#include <fstream>
#include <groupby/operations/scan.hpp>
#include <iostream>
#include <sstream>

int main(int, char* argv[]) {
  std::ifstream file(argv[1]);
  groupby::ops::Scan(groupby::RelationIn(file),
                     groupby::RelationOut(std::cout));
  return 0;
}
