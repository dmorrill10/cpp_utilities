#pragma once

#include <cassert>
#include <random>

namespace Utilities {
namespace Random {
template <typename Numeric = double, typename RandomEngine = std::mt19937>
bool flipCoin(Numeric probTrue, RandomEngine* randomEngine) {
  assert(randomEngine);
  std::bernoulli_distribution coin(probTrue);
  return coin(*randomEngine);
}
}
}
