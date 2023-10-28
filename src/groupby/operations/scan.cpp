///////////////////////////////////////////////////////////////////////////////

#include "scan.hpp"

#include <cassert>

#include "groupby/settings.hpp"

///////////////////////////////////////////////////////////////////////////////
namespace groupby {
///////////////////////////////////////////////////////////////////////////////

ScanOperation::ScanOperation(std::istream& in, size_t b_size)
    : reader_(in), curr_(0) {
  block_.reserve(Settings::Instance().RECORDS_IN_BLOCK * b_size);
  buffer_.reserve(Settings::Instance().RECORD_SIZE * block_.capacity());

  in.rdbuf()->pubsetbuf(buffer_.data(), static_cast<long>(buffer_.capacity()));
  NextBlock();
}

ScanOperation::ScanOperation(ScanOperation&& other)
    : reader_(std::move(other.reader_)),
      buffer_(std::move(other.buffer_)),
      block_(std::move(other.block_)),
      curr_(other.curr_) {
}

ScanOperation& ScanOperation::operator=(ScanOperation&& other) {
  if (this != &other) {
    reader_ = std::move(other.reader_);
    buffer_ = std::move(other.buffer_);
    block_ = std::move(other.block_);
    curr_ = other.curr_;
  }
  return *this;
}

Record& ScanOperation::operator*() {
  return block_.at(curr_);
}

Record* ScanOperation::operator->() {
  return &block_.at(curr_);
}

ScanOperation& ScanOperation::operator++() {
  if (!End()) {
    if (++curr_ == block_.size() && reader_ != RelationIn()) {
      NextBlock();
    }
  }
  return *this;
}

Block& ScanOperation::GetBlock() {
  return block_;
}

void ScanOperation::NextBlock() {
  auto end = RelationIn();
  const size_t capacity = block_.capacity();
  assert(capacity > 0);
  block_.clear();
  for (; reader_ != end && block_.size() < capacity; ++reader_) {
    block_.emplace_back(std::move(*reader_));
  }
  curr_ = 0;
}

bool ScanOperation::End() {
  return reader_ == RelationIn() && curr_ == block_.size();
}

///////////////////////////////////////////////////////////////////////////////

WriteOperation::WriteOperation(std::ostream& out, size_t b_size)
    : writer_(out) {
  buffer_.reserve(Settings::Instance().RECORD_SIZE *
                  Settings::Instance().RECORDS_IN_BLOCK * b_size);
  out.rdbuf()->pubsetbuf(buffer_.data(), static_cast<long>(buffer_.capacity()));
}

WriteOperation::WriteOperation(WriteOperation&& other)
    : writer_(std::move(other.writer_)), buffer_(std::move(other.buffer_)) {
}

WriteOperation& WriteOperation::operator=(WriteOperation&& other) {
  if (this != &other) {
    writer_ = std::move(other.writer_);
    buffer_ = std::move(other.buffer_);
  }
  return *this;
}

RelationOut& WriteOperation::operator*() {
  return *writer_;
}

WriteOperation& WriteOperation::operator++() {
  ++writer_;
  return *this;
}

void WriteOperation::WriteBlock(const Block& block) {
  assert(block.size() > 0);
  for (size_t i = 0; i < block.size(); ++i, ++writer_) {
    *writer_ = block.at(i);
  }
}

///////////////////////////////////////////////////////////////////////////////
}  // namespace groupby
///////////////////////////////////////////////////////////////////////////////
