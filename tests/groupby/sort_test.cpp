#include <gtest/gtest.h>

#include <fstream>
#include <groupby/operations/sort.hpp>
#include <memory>
#include <tuple>
#include <utility>

#include "data.hpp"

struct TestSort : public TestDataFixture {};

TEST_P(TestSort, Basic) {
  std::ifstream file(TestDataFixture::DATA_PATH.data());
  groupby::SortedScanOperation scan{groupby::RelationIn(file), 0};
  for (; !scan.End(); ++scan) {
    std::cerr << *scan;
  }
}

INSTANTIATE_TEST_SUITE_P(
    SortTests, TestSort,
    ::testing::Values(
        std::make_tuple(&groupby::testing::SmallRangeData::Instance(), 5'000),
        std::make_tuple(&groupby::testing::BigRangeData::Instance(), 5'000),
        std::make_tuple(&groupby::testing::MonotonicData::Instance(), 5'000)));
