#include <gtest/gtest.h>

#include <fstream>
#include <groupby/operations/scan.hpp>
#include <memory>
#include <tuple>
#include <utility>

#include "data.hpp"

TEST_P(TestDataFixture, TestScan) {
  std::ifstream file(TestDataFixture::DATA_PATH.data());

  groupby::ops::Scan(groupby::RelationIn(file),
                     groupby::RelationOut(std::cerr));
}

INSTANTIATE_TEST_SUITE_P(
    ScanTests, TestDataFixture,
    ::testing::Values(
        std::make_tuple(&groupby::testing::SmallRangeData::Instance(), 5'000),
        std::make_tuple(&groupby::testing::BigRangeData::Instance(), 5'000),
        std::make_tuple(&groupby::testing::MonotonicData::Instance(), 5'000)));
