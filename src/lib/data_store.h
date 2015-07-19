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
      : data_(initalNumElements * blockSize), base_(0), blockSize_(blockSize) {}
  virtual ~Store() {}

  void push(const T* newData) {
    const auto top = base_ + blockSize_;

    if (data_.size() <= top) {
      const auto& dataEnd = data_.end();

      data_.insert(dataEnd,
                   std::max(uint(2 * data_.size()), uint(top)) - data_.size(),
                   0.0);
    }

    std::copy(newData, newData + blockSize_, data_.begin() + base_);
    base_ = top;
  }

  void clear() {
    data_.clear();
    base_ = 0;
  }
  T* data(uint blockIndex) { return &data_[baseIndex(blockIndex)]; }
  const T* data(uint blockIndex) const { return &data_[baseIndex(blockIndex)]; }

  uint blockSize() const { return blockSize_; }

  uint baseIndex(uint blockIndex) const { return blockIndex * blockSize_; }

  uint size() const { return base_ / blockSize_; }

 protected:
  std::vector<T> data_;
  uint base_;
  const uint blockSize_;
};
}
}
