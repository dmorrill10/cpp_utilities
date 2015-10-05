#pragma once

#include <cassert>
#include <functional>
#include <vector>
#include <initializer_list>

namespace Utilities {
namespace Array {
template <class T, class Size = unsigned int>
class Array {
 public:
  Array(T*&& data, Size capacity, std::function<void(T**)>&& deleteData)
      : data_(std::move(data)),
        capacity_(capacity),
        deleteData_(std::move(deleteData)) {
    assert(data_);
    assert(capacity_ > 0);
  }
  Array(T* data, Size capacity)
      : data_(data), capacity_(capacity), deleteData_([](T**) {}) {
    assert(data_);
    assert(capacity_ > 0);
  }
  virtual ~Array() { deleteData_(&data_); }

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

 protected:
  T* data_;
  Size capacity_;
  std::function<void(T**)> deleteData_;
};

/// Arranged in the same order as +dimensions+. So it is contiguous in the first
/// dimension.
class HyperCubeIndexer {
 public:
  HyperCubeIndexer(std::initializer_list<size_t> dimensions)
      : dimensions_(dimensions) {}
  virtual ~HyperCubeIndexer() {}

  inline size_t operator()(std::initializer_list<size_t> indices) const {
    size_t baseOffset = 0;
    size_t dimension = 0;
    size_t products = 1;
    for (const auto& coord : indices) {
      if (dimension >= dimensions_.size()) {
        break;
      }
      if (dimension > 0) {
        products *= dimensions_[dimension - 1];
      }
      baseOffset += (coord * products);
      ++dimension;
    }
    return baseOffset;
  }

  inline size_t size() const {
    return std::accumulate(dimensions_.begin(), dimensions_.end(), 1,
                           std::multiplies<size_t>());
  }

  inline size_t numDimensions() const { return dimensions_.size(); }

 private:
  std::vector<size_t> dimensions_;
};

/// Arranged in the same order as +dimensions+. So it is contiguous in the first
/// dimension.
template <class T>
class MultiDimensionalArray {
 public:
  MultiDimensionalArray(std::initializer_list<size_t> dimensions)
      : indexer_(dimensions), data_(indexer_.size()) {}
  MultiDimensionalArray(std::initializer_list<size_t> dimensions,
                        const T& initialValue)
      : indexer_(dimensions), data_(indexer_.size(), initialValue) {}
  virtual ~MultiDimensionalArray() {}

  void set(std::initializer_list<size_t> indices, const T& val) {
    data_[indexer_(indices)] = val;
  }
  const T& at(std::initializer_list<size_t> indices) const {
    return data_[indexer_(indices)];
  }
  T& at(std::initializer_list<size_t> indices) {
    return data_[indexer_(indices)];
  }

  const HyperCubeIndexer& indexer() const { return indexer_; }

 private:
  HyperCubeIndexer indexer_;
  std::vector<T> data_;
};
}
}
