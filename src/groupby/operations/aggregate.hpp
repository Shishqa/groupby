#pragma once

#include "groupby/relation/value.hpp"

namespace groupby {

class Aggregator {
 protected:
  Aggregator() = default;

 public:
  virtual ~Aggregator() = default;

  virtual Value Init() = 0;
  virtual void Aggregate(Value& a, const Value& b) = 0;
};

class CountAggregator : public Aggregator {
 public:
  virtual Value Init() override;
  virtual void Aggregate(Value& a, const Value& b) override;
};

class MinAggregator : public Aggregator {
 public:
  virtual Value Init() override;
  virtual void Aggregate(Value& a, const Value& b) override;
};

class MaxAggregator : public Aggregator {
 public:
  virtual Value Init() override;
  virtual void Aggregate(Value& a, const Value& v) override;
};

}  // namespace groupby
