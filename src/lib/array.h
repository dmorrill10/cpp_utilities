#pragma once

template <class T>
class Array {
 public:
  Array(T* data, size_t capacity) : data_(data), capacity_(capacity) {
    assert(data_);
    assert(capacity_ > 0);
  }

  T& operator[](size_t index) {
    assert(index < capacity_);
    return data_[index];
  }
  const T& operator[](size_t index) const {
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
  void assign(size_t numElements, const T& value) {
#pragma vector always assert
    for (size_t i = 0; i < numElements; ++i) {
      data_[i] = value;
    }
  }
  void clear() { capacity_ = 0; }

  size_t capacity() const { return capacity_; }
  size_t size() const { return capacity_; }
  size_t length() const { return capacity_; }

 private:
  T* data_;
  size_t capacity_;
};
