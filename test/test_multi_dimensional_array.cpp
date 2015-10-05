#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <string>

#include <test_helper.hpp>

#include <lib/array.h>

using namespace Utilities;

SCENARIO("MultiDimensionalArray") {
  GIVEN("A new empty 3D-array") {
    Array::MultiDimensionalArray<int> patient({3, 2, 4});
    WHEN("All elements are set") {
      for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 2; ++j) {
          for (size_t k = 0; k < 4; ++k) {
            patient.set({i, j, k}, 1 * i + 2 * j + 3 * k);
          }
        }
      }
      THEN("All elements can be retrieved") {
        for (size_t i = 0; i < 3; ++i) {
          for (size_t j = 0; j < 2; ++j) {
            for (size_t k = 0; k < 4; ++k) {
              CHECK(patient.at({i, j, k}) == (1 * i + 2 * j + 3 * k));
            }
          }
        }
      }
    }
  }
}
