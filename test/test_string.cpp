#include <test_helper.hpp>

#include <lib/string.h>

SCENARIO("toString") {
  GIVEN("A double") {
    const double v = 0.54;
    WHEN("It is allowed a large number of characters") {
      THEN("It can encode the string properly") {
        CHECK(Utilities::String::toString(v, "%0.2lg") == "0.54");
        CHECK(Utilities::String::toString(v, "%0.2lg", 4) == "0.54");
      }
    }
    WHEN("It is allowed too few characters") {
      THEN("It throws an exception") {
        CHECK_THROWS(Utilities::String::toString(v, "%0.2lg", 1));
      }
    }
  }
}
