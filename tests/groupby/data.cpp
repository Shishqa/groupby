#include "data.hpp"

#include <filesystem>
#include <fstream>
#include <groupby/relation/record.hpp>
#include <numeric>

void TestDataFixture::TearDown() {
  std::filesystem::remove(DATA_PATH.data());
}

void TestDataFixture::SetUp() {
  std::ofstream tmp_file(DATA_PATH.data());
  groupby::testing::GenerateData(tmp_file, *std::get<0>(GetParam()),
                                 std::get<1>(GetParam()), N_COLUMNS);
}
