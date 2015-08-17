#pragma once

#include <string>
#include <cstdio>
#include <stdexcept>

namespace Utilities {
namespace String {
template <class T>
std::string toString(T toPrintToString,
                     std::string&& format,
                     size_t maxLength = 128) {
  const auto lengthWithTerminator = maxLength + 1;
  char s[lengthWithTerminator];
  std::fill(s, s + lengthWithTerminator, 0);
  const auto retVal =
      snprintf(s, lengthWithTerminator, format.c_str(), toPrintToString);
  if (retVal <= 0 || size_t(retVal) > maxLength) {
    throw std::runtime_error("Unable to use \"" + format + "\" to encode \"" +
                             std::to_string(toPrintToString) +
                             "\" in a string with a maximum size of " +
                             std::to_string(maxLength) + ": " +
                             std::to_string(retVal));
  }
  return s;
}
}
}
