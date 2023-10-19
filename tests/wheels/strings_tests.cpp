#include <gtest/gtest.h>

#include <wheels/string.hpp>

using namespace wheels;

TEST(TestWheelsStr, Split) {
  static constexpr std::string_view s = "1,22,333,4444";

  auto res = str::Split(s, ',');

  EXPECT_EQ(4, res.size());
  EXPECT_STREQ("1", res[0].data());
  EXPECT_STREQ("22", res[1].data());
  EXPECT_STREQ("333", res[2].data());
  EXPECT_STREQ("4444", res[3].data());

  res = str::Split(s, '2');

  EXPECT_EQ(3, res.size());
  EXPECT_STREQ("1,", res[0].data());
  EXPECT_STREQ("", res[1].data());
  EXPECT_STREQ(",333,4444", res[2].data());
}

TEST(TestWheelsStr, Join) {
  std::vector<std::string> v = {"1", "22", "333", "4444"};

  EXPECT_STREQ("1,22,333,4444", str::Join(v, ',').data());
  EXPECT_STREQ("1;22;333;4444", str::Join(v, ';').data());
}
