#pragma once

#include <cassert>

namespace Utilities {
namespace Array {
template <class T, class Size = unsigned int>
class Array {
 public:
  Array(T* data, Size capacity) : data_(data), capacity_(capacity) {
    assert(data_);
    assert(capacity_ > 0);
  }

  T& operator[](Size index) {
    assert(index < capacity_);
    return data_[index];
  }
  const T& operator[](Size index) const {
    assert(index < capacity_);
    return data_[index];
  }
  T& operator*() { return *data_; }
  const T& operator*() const { return *data_; }
  T* data() { return data_; }
  const T* data() const { return data_; }

  /**
   * If T is primitive but not floating point, or if value is zero, the
   * caller should probably use memset on the raw pointer instead
   */
  void assign(Size numElements, const T& value) {
#pragma vector always assert
    for (Size i = 0; i < numElements; ++i) {
      data_[i] = value;
    }
  }
  void clear() { capacity_ = 0; }

  Size capacity() const { return capacity_; }
  Size size() const { return capacity_; }
  Size length() const { return capacity_; }

 private:
  T* data_;
  Size capacity_;
};
}
}
