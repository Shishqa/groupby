#include <gtest/gtest.h>

#include <groupby/count.hpp>

// Demonstrate some basic assertions.
TEST(Test, BasicAssertions) {
  EXPECT_EQ(count(1), 1);
  EXPECT_NE(count(2), 1);
}
