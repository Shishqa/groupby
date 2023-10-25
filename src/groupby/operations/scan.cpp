///////////////////////////////////////////////////////////////////////////////

#include "scan.hpp"

#include "groupby/memory/block.hpp"

///////////////////////////////////////////////////////////////////////////////
namespace groupby {
///////////////////////////////////////////////////////////////////////////////

ScanOperation::ScanOperation(RelationIn reader, size_t b_size)
    : reader_(std::move(reader)),
      b_(BlockManager::Instance().Allocate(b_size)),
      curr_(0) {
  reader_ = BlockRead(*b_, reader_);
}

ScanOperation::ScanOperation(ScanOperation&& other)
    : reader_(std::move(other.reader_)),
      b_(std::move(other.b_)),
      curr_(other.curr_) {
}

ScanOperation& ScanOperation::operator=(ScanOperation&& other) {
  if (this != &other) {
    reader_ = std::move(other.reader_);
    b_ = std::move(other.b_);
    curr_ = other.curr_;
  }
  return *this;
}

Record& ScanOperation::operator*() {
  return b_->at(curr_);
}

Record* ScanOperation::operator->() {
  return &b_->at(curr_);
}

ScanOperation& ScanOperation::operator++() {
  if (!End()) {
    if (++curr_ == b_->size() && reader_ != RelationIn()) {
      reader_ = BlockRead(*b_, reader_);
      curr_ = 0;
    }
  }
  return *this;
}

bool ScanOperation::End() {
  return reader_ == RelationIn() && curr_ == b_->size();
}

///////////////////////////////////////////////////////////////////////////////
}  // namespace groupby
///////////////////////////////////////////////////////////////////////////////
