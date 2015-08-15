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
  if (!indices) {
    double vCopy[numElements];
    std::copy(v, v + numElements, vCopy);
    std::nth_element(vCopy, vCopy + numElements / 2, vCopy + numElements);
    return vCopy[numElements / 2];
  }
  std::nth_element(
      indices, indices + numElements / 2, indices + numElements,
      [v](const size_t& a, const size_t& b) { return v[a] < v[b]; });
  return v[indices[numElements / 2]];
}
}
}
