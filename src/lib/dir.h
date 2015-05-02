#pragma once

#include <stdexcept>
#include <algorithm>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

namespace Utilities {
namespace Dir {
void mkdirp(const std::string &path,
            mode_t mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) {
  struct stat st;

  auto nextSlash = std::find(path.begin(), path.end(), '/');
  while (nextSlash != path.end()) {
    const auto directory = std::string(path.begin(), nextSlash);

    if (stat(directory.c_str(), &st) != 0) {
      if (mkdir(directory.c_str(), mode) != 0 && errno != EEXIST) {
        throw std::runtime_error("Cannot create directory \"" + directory +
                                 "\": " + strerror(errno) + "\n");
      }
    } else {
      if (!S_ISDIR(st.st_mode)) {
        errno = ENOTDIR;
        throw std::runtime_error("path \"" + directory +
                                 "\" is not a directory\n");
      } else {
        continue;
      }
    }
    ++nextSlash;
    if (nextSlash != path.end()) {
      nextSlash = std::find(nextSlash, path.end(), '/');
    }
  }
}
}
}
