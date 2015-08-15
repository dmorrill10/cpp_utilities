#pragma once
#include <cmath>
#include <algorithm>

namespace Utilities {
namespace Math {
// Thanks to OJ
// http://stackoverflow.com/questions/17333/most-effective-way-for-float-and-double-comparison
// for these.
inline bool areClose(double a, double b, double epsilon = 1e-30) {
  return fabs(a - b) < epsilon;
}
inline bool isCloseToZero(double a, double epsilon = 1e-30) {
  return fabs(a) < epsilon;
}
// Partially sorts indices
static double median(const double* __restrict__ v,
                     size_t numElements,
                     size_t* __restrict__ indices = nullptr) {
  const auto isEven = numElements % 2 == 0;
  const auto middle = isEven ? numElements / 2 : ((numElements + 1) / 2) - 1;
  if (!indices) {
    double vCopy[numElements];
    std::copy(v, v + numElements, vCopy);
    std::nth_element(vCopy, vCopy + middle, vCopy + numElements);
    return isEven ? (vCopy[(numElements / 2) - 1] / 2.0) + (vCopy[middle] / 2.0)
                  : vCopy[middle];
  }
  std::nth_element(
      indices, indices + middle, indices + numElements,
      [v](const size_t& a, const size_t& b) { return v[a] < v[b]; });
  return isEven
             ? (v[indices[(numElements / 2) - 1]] / 2.0) +
                   (v[indices[middle]] / 2.0)
             : v[indices[middle]];
}
static double mean(const double* __restrict__ v,
                   size_t numElements,
                   size_t* __restrict__ indices = nullptr) {
  double m = 0.0;
  if (!indices) {
    for (size_t i = 0; i < numElements; ++i) {
      m += (v[i] / numElements);
    }
  } else {
    for (size_t i = 0; i < numElements; ++i) {
      m += (v[indices[i]] / numElements);
    }
  }
  return m;
}
}
}
