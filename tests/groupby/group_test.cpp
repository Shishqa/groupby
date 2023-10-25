#include <gtest/gtest.h>

#include <fstream>
#include <groupby/operations/group.hpp>
#include <groupby/operations/sort.hpp>
#include <memory>
#include <tuple>
#include <utility>

#include "data.hpp"

struct TestGroup : public TestDataFixture {};

TEST_P(TestGroup, Basic) {
  std::ifstream file(TestDataFixture::DATA_PATH.data());
  groupby::CountAggregator agg{};
  groupby::SortedScanOperation scan{groupby::RelationIn(file), 2};
  groupby::SortedGroupOperation group(scan, 2, 5, {&agg});
  for (; !group.End(); ++group) {
    std::cerr << *group;
  }
}

INSTANTIATE_TEST_SUITE_P(GroupTests, TestGroup,
                         ::testing::Values(std::make_tuple(
                             &groupby::testing::SmallRangeData::Instance(),
                             10)));
