#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <string>

#include <test_helper.hpp>

#include <lib/stack.h>

using namespace Utilities;

SCENARIO("Using a NeverDeallocatedStack") {
  GIVEN("A new empty stack") {
    Stack::NeverDeallocatedStack<int> patient;
    THEN("#push adds a frame and #pop removes it") {
      patient.push(1);
      REQUIRE(patient.get(0) == 0);
      patient.set(0, 18);
      REQUIRE(patient.get(0) == 18);
      patient.pop();
      patient.push(1);
      REQUIRE(patient.get(0) == 0);
    }
    THEN("Moving up and down the stack works properly") {
      patient.nextContext(1, [&]() {
        REQUIRE(patient.get(0) == 0);
        patient.nextContext(1, [&]() {
          REQUIRE(patient.get(0) == 0);
          REQUIRE(patient.context()[0] == 0);
          REQUIRE(patient.getPrevious(0) == 0);
          REQUIRE(patient.previousContext()[0] == 0);
          patient.set(0, 18);
          REQUIRE(patient.get(0) == 18);
          REQUIRE(patient.context()[0] == 18);
          REQUIRE(patient.getPrevious(0) == 0);
          REQUIRE(patient.previousContext()[0] == 0);
          patient.context()[0] = 96;
          REQUIRE(patient.get(0) == 96);
          REQUIRE(patient.context()[0] == 96);
          patient.setPrevious(0, 32);
          REQUIRE(patient.get(0) == 96);
          REQUIRE(patient.context()[0] == 96);
          REQUIRE(patient.getPrevious(0) == 32);
          REQUIRE(patient.previousContext()[0] == 32);
        });
        REQUIRE(patient.get(0) == 32);
        REQUIRE(patient.context()[0] == 32);
        patient.nextContext(1, [&]() {
          REQUIRE(patient.get(0) == 0);
          REQUIRE(patient.context()[0] == 0);
          REQUIRE(patient.getPrevious(0) == 32);
          REQUIRE(patient.previousContext()[0] == 32);
          patient.set(0, 28);
          REQUIRE(patient.get(0) == 28);
          REQUIRE(patient.context()[0] == 28);
          REQUIRE(patient.getPrevious(0) == 32);
          REQUIRE(patient.previousContext()[0] == 32);
          patient.context()[0] = 96;
          REQUIRE(patient.get(0) == 96);
          REQUIRE(patient.context()[0] == 96);
          patient.setPrevious(0, 62);
          REQUIRE(patient.get(0) == 96);
          REQUIRE(patient.context()[0] == 96);
          REQUIRE(patient.getPrevious(0) == 62);
          REQUIRE(patient.previousContext()[0] == 62);
        });
        REQUIRE(patient.get(0) == 62);
        REQUIRE(patient.context()[0] == 62);
      });
    }
  }
}
