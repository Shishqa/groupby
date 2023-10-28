#pragma once

#include <gtest/gtest.h>

#include <cstdint>
#include <groupby/utils/data.hpp>
#include <memory>
#include <random>
#include <string_view>
#include <tuple>

class TestDataFixture : public ::testing::TestWithParam<
                            std::tuple<groupby::testing::IGenerator*, size_t>> {
 public:
  static constexpr std::string_view DATA_PATH = ".test_data.csv";

  static constexpr size_t N_COLUMNS = 20;

  void SetUp() override;
  void TearDown() override;
};
