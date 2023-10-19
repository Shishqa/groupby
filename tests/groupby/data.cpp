#include "data.hpp"

#include <filesystem>
#include <fstream>
#include <groupby/relation/record.hpp>
#include <numeric>

namespace groupby::testing {

//////////////////////////////////////////////////////////

IGenerator::IGenerator() : gen_(rd_()) {
}

//////////////////////////////////////////////////////////

UniformData::UniformData(num_t min, num_t max) : distrib_(min, max) {
}

std::string UniformData::Gen(size_t, size_t) {
  return std::to_string(distrib_(gen_));
}

//////////////////////////////////////////////////////////

BigRangeData::BigRangeData()
    : UniformData(std::numeric_limits<num_t>::min(),
                  std::numeric_limits<num_t>::max()) {
}

BigRangeData& BigRangeData::Instance() {
  static BigRangeData instance_;
  return instance_;
}

//////////////////////////////////////////////////////////

SmallRangeData::SmallRangeData() : UniformData(0, 10) {
}

SmallRangeData& SmallRangeData::Instance() {
  static SmallRangeData instance_;
  return instance_;
}

//////////////////////////////////////////////////////////

std::string MonotonicData::Gen(size_t i, size_t j) {
  return std::to_string(i + j);
}

MonotonicData& MonotonicData::Instance() {
  static MonotonicData instance_;
  return instance_;
}

//////////////////////////////////////////////////////////

}  // namespace groupby::testing

void TestDataFixture::TearDown() {
  std::filesystem::remove(DATA_PATH.data());
}

void TestDataFixture::SetUp() {
  std::ofstream tmp_file(DATA_PATH.data());

  auto gen = std::get<0>(GetParam());
  auto n_rows = std::get<1>(GetParam());

  for (size_t i = 0; i < n_rows; ++i) {
    for (size_t j = 0; j < N_COLUMNS; ++j) {
      tmp_file << gen->Gen(i, j);
      if (j != N_COLUMNS - 1) {
        tmp_file << groupby::Record::CSV_DELIM;
      } else {
        tmp_file << "\n";
      }
    }
  }
}
