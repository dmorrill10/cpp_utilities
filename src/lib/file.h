#pragma once

#include <cstdio>
#include <cassert>
#include <functional>
#include <string>

namespace Utilities {
namespace File {

// @todo It would be nice to be able to return a value from doFn and have
// withOpenFile return that as well, but I don't know how to do that yet. Having
// the return type be auto and using decltype I feel is on the right track, but
// I can't get it to work yet.
template <class Function>
// requires Function is callable, takes FILE* as input, and produces no output
void withOpenFile(const char* fileName, const char* mode, Function doFn) {
  FILE* f = fopen(fileName, mode);
  assert(f);

  doFn(f);

  fclose(f);
}

template <class Function>
// requires Function is callable, takes FILE* as input, and produces no output
void withOpenFile(const std::string& fileName,
                  const std::string& mode,
                  Function doFn) {
  withOpenFile(fileName.c_str(), mode.c_str(), doFn);
}
}
}