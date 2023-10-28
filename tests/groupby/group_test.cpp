#include <gtest/gtest.h>
#include <sys/resource.h>

#include <fstream>
#include <groupby/operations/aggregate.hpp>
#include <groupby/operations/group.hpp>
#include <groupby/operations/scan.hpp>
#include <groupby/operations/sort.hpp>
#include <groupby/settings.hpp>
#include <memory>
#include <tuple>
#include <unordered_set>
#include <utility>

#include "data.hpp"

struct TestHashedGroup : public TestDataFixture {};
struct TestSortedGroup : public TestDataFixture {};

TEST_P(TestHashedGroup, GroupCount) {
  std::ifstream file(TestDataFixture::DATA_PATH.data());
  groupby::CountAggregator agg{};
  groupby::ScanOperation scan{file, 1};
  groupby::HashedGroupOperation group{scan, 0, 1, {&agg}};

  groupby::int_t cnt = 0;
  std::unordered_set<groupby::int_t> seen_keys{};
  for (; !group.End(); ++group) {
    auto key = std::get<groupby::int_t>(group->values.at(1));
    ASSERT_NE(1, seen_keys.count(key));
    seen_keys.insert(key);
    cnt += std::get<groupby::int_t>(group->values.at(0));
  }
  ASSERT_EQ(cnt, 10000);
}

TEST_P(TestHashedGroup, GroupMax) {
  std::ifstream file(TestDataFixture::DATA_PATH.data());
  groupby::MaxAggregator agg{};
  groupby::ScanOperation scan{file, 1};
  groupby::HashedGroupOperation group{scan, 0, 1, {&agg}};

  std::unordered_set<groupby::int_t> seen_keys{};
  for (; !group.End(); ++group) {
    auto key = std::get<groupby::int_t>(group->values.at(1));
    ASSERT_NE(1, seen_keys.count(key));
    seen_keys.insert(key);
  }
}

INSTANTIATE_TEST_SUITE_P(
    SmallGroupTests, TestHashedGroup,
    ::testing::Values(
        std::make_tuple(&groupby::testing::SmallRangeData::Instance(), 10000),
        std::make_tuple(&groupby::testing::BigRangeData::Instance(), 10000),
        std::make_tuple(&groupby::testing::MonotonicData::Instance(), 10000)));

TEST_P(TestSortedGroup, GroupCount) {
  std::ifstream file(TestDataFixture::DATA_PATH.data());
  groupby::CountAggregator agg{};

  // sort by first, aggregate second.
  groupby::SortedScanOperation scan{file, 0};
  groupby::SortedGroupOperation group{scan, 0, 1, {&agg}};

  groupby::int_t cnt = 0;
  std::unordered_set<groupby::int_t> seen_keys{};
  for (; !group.End(); ++group) {
    auto key = std::get<groupby::int_t>(group->values.at(1));
    ASSERT_NE(1, seen_keys.count(key));
    seen_keys.insert(key);
    cnt += std::get<groupby::int_t>(group->values.at(0));
  }
  ASSERT_EQ(cnt, 600'000);
}

INSTANTIATE_TEST_SUITE_P(
    LargeGroupTests, TestSortedGroup,
    ::testing::Values(
        std::make_tuple(&groupby::testing::SmallRangeData::Instance(), 600'000),
        std::make_tuple(&groupby::testing::BigRangeData::Instance(), 600'000),
        std::make_tuple(&groupby::testing::MonotonicData::Instance(),
                        600'000)));
