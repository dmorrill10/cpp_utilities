#pragma once

#include <cassert>
#include <vector>
#include <cmath>
#include <utility>

namespace Utilities {
namespace DataStore {

using uint = unsigned int;

template <class T>
class Store {
 public:
  Store(uint blockSize, uint initalNumElements = 1e1)
      : data_(initalNumElements * blockSize),
        base_(0),
        top_(0),
        blockSize_(blockSize) {}
  virtual ~Store() {}

  void push(const T* newData) {
    base_ = top_;
    top_ += blockSize_;
    ensureLargeEnough();
    std::copy(newData, newData + blockSize_, data_.begin() + base_);
  }

  void push() {
    base_ = top_;
    top_ += blockSize_;
    ensureLargeEnough();
    std::fill(&data_[base_], &data_[top_], 0.0);
  }

  void clear() {
    data_.clear();
    base_ = 0;
    top_ = 0;
  }
  T* data(uint blockIndex) { return &data_[baseIndex(blockIndex)]; }
  const T* data(uint blockIndex) const { return &data_[baseIndex(blockIndex)]; }

  T* back() { return data(size() - 1); }

  uint blockSize() const { return blockSize_; }

  uint baseIndex(uint blockIndex) const { return blockIndex * blockSize_; }

  uint size() const { return top_ / blockSize_; }

 protected:
  void ensureLargeEnough() {
    if (data_.size() <= top_) {
      const auto& dataEnd = data_.end();

      data_.insert(dataEnd,
                   std::max(uint(2 * data_.size()), uint(top_)) - data_.size(),
                   0.0);
    }
  }

 protected:
  std::vector<T> data_;
  uint base_;
  uint top_;
  const uint blockSize_;
};
}
}
