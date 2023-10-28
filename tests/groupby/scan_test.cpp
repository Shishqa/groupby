#include <gtest/gtest.h>

#include <fstream>
#include <groupby/operations/scan.hpp>
#include <groupby/settings.hpp>
#include <memory>
#include <tuple>
#include <utility>

#include "data.hpp"

struct TestScan : public TestDataFixture {};

TEST_P(TestScan, Basic) {
  std::ifstream file(TestDataFixture::DATA_PATH.data());

  groupby::ScanOperation scan{file,
                              groupby::Settings::Instance().BLOCKS_IN_MEMORY};

  size_t cnt = 0;
  for (; !scan.End(); ++scan, ++cnt) {
    // pass
  }
  ASSERT_EQ(cnt, 600'000);
}

INSTANTIATE_TEST_SUITE_P(
    ScanTests, TestScan,
    ::testing::Values(
        std::make_tuple(&groupby::testing::SmallRangeData::Instance(), 600'000),
        std::make_tuple(&groupby::testing::BigRangeData::Instance(), 600'000),
        std::make_tuple(&groupby::testing::MonotonicData::Instance(),
                        600'000)));
