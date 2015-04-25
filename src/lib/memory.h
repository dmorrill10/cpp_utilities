#pragma once

namespace Utilities {
  namespace Memory {
    template <typename Type>
    void freePointer(Type* ptr) {
      if (ptr) {
        free(static_cast<void *>(ptr));
        ptr = nullptr;
      }
    }
    template <typename Type>
    void deletePointer(Type* ptr) {
      if (ptr) {
        delete ptr;
        ptr = nullptr;
      }
    }
    template <typename Type>
    void deleteArray(Type* array) {
      if (array) {
        delete[] array;
        array = nullptr;
      }
    }
  }
}
