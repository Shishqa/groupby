#pragma once

#include <istream>
#include <vector>

#include "base.hpp"
#include "groupby/relation/block.hpp"
#include "groupby/relation/relation.hpp"

namespace groupby {

class ScanOperation : public BaseOperation {
 public:
  ScanOperation(std::istream& in, size_t b_size = 1);

  ScanOperation(const ScanOperation& other) = delete;

  ScanOperation(ScanOperation&& other);
  ScanOperation& operator=(ScanOperation&& other);

  Record& operator*() override;
  Record* operator->() override;

  ScanOperation& operator++() override;

  bool End() override;

  Block& GetBlock();
  void NextBlock();

 private:
  RelationIn reader_;
  std::vector<char> buffer_;
  Block block_;
  size_t curr_;
};

class WriteOperation {
 public:
  WriteOperation(std::ostream& out, size_t b_size = 1);

  WriteOperation(const WriteOperation& other) = delete;

  WriteOperation(WriteOperation&& other);
  WriteOperation& operator=(WriteOperation&& other);

  RelationOut& operator*();

  WriteOperation& operator++();

  void WriteBlock(const Block& block);

 private:
  RelationOut writer_;
  std::vector<char> buffer_;
};

}  // namespace groupby
