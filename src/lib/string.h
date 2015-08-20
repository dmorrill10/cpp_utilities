#pragma once

#include <string>
#include <cstdio>
#include <stdexcept>

namespace Utilities {
namespace String {
template <class T>
std::string toString(const T& toPrintToString,
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

template <class T>
std::string toString(const T& toPrintToString,
                     const std::string& format,
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

template <class T>
std::string toString(const T* data,
                     size_t numElements,
                     std::function<std::string(const T& data_i)> elemToString) {
  std::string str = "";
  for (size_t i = 0; i < numElements; ++i) {
    str += elemToString(data[i]);
    if ((i + 1) < numElements) {
      str += ", ";
    }
  }
  return str;
}

template <class T>
std::string toString(const T* data,
                     size_t numElements,
                     const std::string& format,
                     size_t maxLength = 128) {
  return toString<T>(data, numElements, [&](const T& data_i) {
    return toString<T>(data_i, format, maxLength);
  });
}
}
}
