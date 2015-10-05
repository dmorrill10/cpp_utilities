#pragma once

#include <cassert>
#include <vector>

namespace Utilities {
namespace Normalize {
template <typename Numeric = double>
std::vector<Numeric> normalized(const std::vector<Numeric>& v) {
  Numeric sum = 0.0;
  std::vector<Numeric> n(v.size(), 1.0 / v.size());
  for (auto elem : v) {
    sum += elem;
  }
  if (sum > 0) {
    for (size_t i = 0; i < v.size(); ++i) {
      n[i] = v[i] > 0.0 ? exp(log(v[i]) - log(sum)) : 0.0;
    }
  }
  return n;
}

template <typename Numeric = double>
void normalize(const std::vector<Numeric>& from, std::vector<Numeric>* to) {
  Numeric sum = 0.0;
  for (auto elem : from) {
    sum += elem;
  }
  if (sum > 0) {
    for (size_t i = 0; i < from.size(); ++i) {
      (*to)[i] = from[i] > 0.0 ? exp(log(from[i]) - log(sum)) : 0.0;
    }
  } else {
    for (size_t i = 0; i < from.size(); ++i) {
      (*to)[i] = 1.0 / from.size();
    }
  }
}
}
}
