#include <groupby/count.hpp>
#include <iostream>

int main(int, char* argv[]) {
  std::cout << argv[0] << " " << count(42) << std::endl;
  return 0;
}
