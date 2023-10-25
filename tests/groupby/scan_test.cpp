#include <gtest/gtest.h>

#include <fstream>
#include <groupby/operations/scan.hpp>
#include <memory>
#include <tuple>
#include <utility>

#include "data.hpp"

struct TestScan : public TestDataFixture {};

TEST_P(TestScan, Basic) {
  std::ifstream file(TestDataFixture::DATA_PATH.data());
  groupby::ScanOperation scan{groupby::RelationIn(file)};
  for (; !scan.End(); ++scan) {
    // std::cerr << *scan;
  }
}

INSTANTIATE_TEST_SUITE_P(
    ScanTests, TestScan,
    ::testing::Values(
        std::make_tuple(&groupby::testing::SmallRangeData::Instance(), 10)
        //        std::make_tuple(&groupby::testing::SmallRangeData::Instance(),
        //        5'000),
        //        std::make_tuple(&groupby::testing::BigRangeData::Instance(),
        //        5'000),
        //        std::make_tuple(&groupby::testing::MonotonicData::Instance(),
        //        5'000),
        //        std::make_tuple(&groupby::testing::SmallRangeData::Instance(),
        //        100'000'000)
        ));
