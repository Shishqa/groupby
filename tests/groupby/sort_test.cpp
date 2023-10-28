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

  // sort by the first key.
  groupby::SortedScanOperation sort{file, 0};

  groupby::int_t prev_value = std::get<groupby::int_t>(sort->values[0]);
  size_t cnt = 0;
  for (; !sort.End(); ++sort, ++cnt) {
    groupby::int_t curr_value = std::get<groupby::int_t>(sort->values[0]);
    ASSERT_LE(prev_value, curr_value);
    prev_value = curr_value;
  }
  ASSERT_EQ(cnt, 600'000);
}

INSTANTIATE_TEST_SUITE_P(
    SortTests, TestSort,
    ::testing::Values(
        std::make_tuple(&groupby::testing::SmallRangeData::Instance(), 600'000),
        std::make_tuple(&groupby::testing::BigRangeData::Instance(), 600'000),
        std::make_tuple(&groupby::testing::MonotonicData::Instance(),
                        600'000)));
