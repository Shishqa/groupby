#include <gtest/gtest.h>

#include <groupby/operations/aggregate.hpp>

using namespace groupby;
using groupby::int_t;

TEST(TestAggregator, CountAggregator) {
  CountAggregator agg{};

  Value v = agg.Init();

  static constexpr size_t CNT = 42;
  for (size_t i = 0; i < CNT; ++i) {
    agg.Aggregate(v, {});
  }

  EXPECT_EQ(CNT, std::get<int_t>(v));
}

TEST(TestAggregator, MinAggregator) {
  MinAggregator agg{};

  Value v = agg.Init();

  static constexpr int_t MIN = 42;
  for (int_t i = MIN; i < MIN + 10; ++i) {
    agg.Aggregate(v, i);
  }

  EXPECT_EQ(MIN, std::get<int_t>(v));
}

TEST(TestAggregator, MaxAggregator) {
  MaxAggregator agg{};

  Value v = agg.Init();

  static constexpr int_t MAX = 102;
  for (int_t i = MAX; i > MAX - 10; --i) {
    agg.Aggregate(v, i);
  }

  EXPECT_EQ(MAX, std::get<int_t>(v));
}
