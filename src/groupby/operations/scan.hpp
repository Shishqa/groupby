#pragma once

#include "groupby/memory/block_manager.hpp"
#include "groupby/relation/relation.hpp"

namespace groupby {

class ScanOperation {
 public:
  ScanOperation(RelationIn reader, size_t b_size = 1);

  ScanOperation(const ScanOperation& other) = delete;

  ScanOperation(ScanOperation&& other);
  ScanOperation& operator=(ScanOperation&& other);

  Record& operator*();
  Record* operator->();

  ScanOperation& operator++();

  bool End();

 private:
  RelationIn reader_;
  BlockManager::BlockHandle b_;
  size_t curr_;
};

}  // namespace groupby
