#pragma once

#include <cassert>
#include <functional>

namespace Utilities {
namespace SaveAndRestore {
template <typename T>
T copyAndReturnAfter(T valueToSaveAndRestore, std::function<void()> doFn) {
  doFn();
  return valueToSaveAndRestore;
}
}
}
