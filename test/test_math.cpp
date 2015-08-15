#include <test_helper.hpp>

#include <lib/math.h>

SCENARIO("Median") {
  GIVEN("Data and indices") {
    double targets[] = {28, 56, 84, 112, 140};
    const auto numExamples = 3;
    size_t indices[] = {1, 3, 4};

    THEN("It returns the median") {
      CHECK(Utilities::Math::median(targets, numExamples) == 56);
      CHECK(Utilities::Math::median(targets, numExamples, indices) == 112);
    }
  }
}
