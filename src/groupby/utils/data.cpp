#include "data.hpp"

#include <filesystem>
#include <fstream>
#include <numeric>

#include "groupby/relation/record.hpp"

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
    : UniformData(std::numeric_limits<groupby::int_t>::min(),
                  std::numeric_limits<groupby::int_t>::max()) {
}

BigRangeData& BigRangeData::Instance() {
  static BigRangeData instance_;
  return instance_;
}

//////////////////////////////////////////////////////////

SmallRangeData::SmallRangeData() : UniformData(1, 10) {
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

void GenerateData(std::ostream& out, IGenerator& generator, size_t n_rows,
                  size_t n_columns) {
  std::vector<char> buffer;
  buffer.reserve(1'000'000'000);
  out.rdbuf()->pubsetbuf(buffer.data(), static_cast<long>(buffer.capacity()));

  groupby::Record r{};
  r.values.reserve(n_columns);
  for (size_t i = 0; i < n_rows; ++i) {
    r.values.clear();
    for (size_t j = 0; j < n_columns; ++j) {
      r.values.emplace_back(generator.Gen(i, j));
    }
    out << r;
  }
}

}  // namespace groupby::testing
