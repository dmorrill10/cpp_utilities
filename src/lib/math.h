#pragma once
#include <cmath>

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
}
}
