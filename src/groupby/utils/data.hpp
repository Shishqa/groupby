#pragma once

#include <cstdint>
#include <memory>
#include <random>
#include <string_view>
#include <tuple>

namespace groupby::testing {

class IGenerator {
 public:
  using num_t = std::int64_t;

  explicit IGenerator();

  virtual std::string Gen(size_t i, size_t j) = 0;

 protected:
  std::random_device rd_ = {};
  std::mt19937 gen_;
};

class UniformData : public IGenerator {
 public:
  std::string Gen(size_t i, size_t j) override;

 protected:
  explicit UniformData(num_t min, num_t max);

  std::uniform_int_distribution<num_t> distrib_;
};

class BigRangeData : public UniformData {
 public:
  static BigRangeData& Instance();

 protected:
  explicit BigRangeData();
};

class SmallRangeData : public UniformData {
 public:
  static SmallRangeData& Instance();

 protected:
  explicit SmallRangeData();
};

class MonotonicData : public IGenerator {
 public:
  static MonotonicData& Instance();

  std::string Gen(size_t i, size_t j) override;
};

void GenerateData(std::ostream& out, IGenerator& generator, size_t n_rows,
                  size_t n_columns);

}  // namespace groupby::testing
