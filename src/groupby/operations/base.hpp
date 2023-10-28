#pragma once

#include "groupby/relation/record.hpp"

namespace groupby {

struct BaseOperation {
  virtual ~BaseOperation() = default;
  virtual Record& operator*() = 0;
  virtual Record* operator->() = 0;
  virtual BaseOperation& operator++() = 0;
  virtual bool End() = 0;
};

}  // namespace groupby
