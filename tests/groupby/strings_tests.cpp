#include <gtest/gtest.h>

#include <groupby/utils/string.hpp>

using namespace groupby;

TEST(TestWheelsStr, Split) {
  static constexpr std::string_view s = "1,22,333,4444";

  auto res = Split(s, ',');

  EXPECT_EQ(4, res.size());
  EXPECT_STREQ("1", res[0].data());
  EXPECT_STREQ("22", res[1].data());
  EXPECT_STREQ("333", res[2].data());
  EXPECT_STREQ("4444", res[3].data());

  res = Split(s, '2');

  EXPECT_EQ(3, res.size());
  EXPECT_STREQ("1,", res[0].data());
  EXPECT_STREQ("", res[1].data());
  EXPECT_STREQ(",333,4444", res[2].data());
}

TEST(TestWheelsStr, Join) {
  std::vector<std::string> v = {"1", "22", "333", "4444"};

  EXPECT_STREQ("1,22,333,4444", Join(v, ',').data());
  EXPECT_STREQ("1;22;333;4444", Join(v, ';').data());
}
