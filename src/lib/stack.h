#pragma once

#include <cassert>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <functional>

namespace Utilities {
namespace Stack {
template <class T>
class NeverDeallocatedStack {
 public:
  NeverDeallocatedStack() : data_(), bases_({0}) {}

  void nextContext(size_t numElements, std::function<void()> doFn) {
    push(numElements);
    doFn();
    pop();
  }

  void clear() {
    data_.clear();
    bases_.clear();
    bases_.push_back(0);
  }

  std::string toString() const {
    std::string s = "";
    for (size_t i = 0; i < data_.size(); ++i) {
      s += std::to_string(data_[i]);
      if (i != (data_.size() - 1)) {
        s += ", ";
      }
    }
    return s;
  }

  void push(size_t numElements) {
    const auto nextBase = top();
    const auto nextTop = nextBase + numElements;

    bases_.push_back(nextTop);
    if (data_.size() <= nextTop) {
      const auto& dataEnd = data_.end();

      // Doubling wastes memory but could be faster, not sure which
      // is better here
      data_.insert(dataEnd,
                   std::max(2 * data_.size(), size_t(nextTop)) - data_.size(),
                   0.0);
    }
    std::fill(context(), &data_[nextTop], 0.0);
  }

  void pop() { bases_.pop_back(); }

  // @todo #ithContext() pointers may not be valid after calling nextContext
  const T* ithContext(size_t i) const {
    return &data_[*(bases_.end() - (2 + i))];
  }
  // @todo #ithContext() pointers may not be valid after calling nextContext
  T* ithContext(size_t i) { return &data_[*(bases_.end() - (2 + i))]; }

  // @todo #context() pointers may not be valid after calling nextContext
  const T* context() const { return ithContext(0); }
  // @todo #context() pointers may not be valid after calling nextContext
  T* context() { return ithContext(0); }

  // @todo #previousContext() pointers may not be valid after calling
  // nextContext
  const T* previousContext() const { return ithContext(1); }
  // @todo #previousContext() pointers may not be valid after calling
  // nextContext
  T* previousContext() { return ithContext(1); }

  /// Zero indexed
  const T getFromIthContext(size_t i, size_t j) const {
    return data_[*(bases_.end() - (2 + i)) + j];
  }

  /// Zero indexed
  void setToIthContext(size_t i, size_t j, T val) {
    data_[*(bases_.end() - (2 + i)) + j] = std::move(val);
  }

  const T get(size_t j) const { return getFromIthContext(0, j); }
  void set(size_t j, T val) { setToIthContext(0, j, val); }

  const T getPrevious(size_t j) const { return getFromIthContext(1, j); }
  void setPrevious(size_t j, T val) { setToIthContext(1, j, val); }

 private:
  uint top() const { return bases_.back(); }

 private:
  std::vector<T> data_;
  std::vector<uint> bases_;
};
}
}
