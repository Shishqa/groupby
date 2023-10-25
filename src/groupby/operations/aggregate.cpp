#include "aggregate.hpp"

#include <cassert>
#include <limits>

namespace groupby {

Value CountAggregator::Init() {
  return 0;
}

void CountAggregator::Aggregate(Value& a, const Value&) {
  std::get<int_t>(a)++;
}

//

Value MinAggregator::Init() {
  return std::numeric_limits<int_t>::max();
}

void MinAggregator::Aggregate(Value& a, const Value& b) {
  auto& a_ = std::get<int_t>(a);
  a_ = std::min(a_, std::get<int_t>(b));
}

//

Value MaxAggregator::Init() {
  return std::numeric_limits<int_t>::min();
}

void MaxAggregator::Aggregate(Value& a, const Value& b) {
  auto& a_ = std::get<int_t>(a);
  a_ = std::max(a_, std::get<int_t>(b));
}

}  // namespace groupby
