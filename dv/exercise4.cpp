#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <VExercise4.h>


TEST_CASE("Exercise 4") {
  VExercise4 model;
  model.cs = 0;
  // Ensure any sel value and cs = 0 produce out = 0
  for (model.sel = 0; model.sel < 4; ++model.sel) {
    model.eval();
    REQUIRE(model.out == 0);
  }
  model.cs = 1;
  model.alpha = 0;
  model.beta = 0;
  model.gamma = 0;
  // Test all input combinations between alpha, beta, and gamma
  do {
    do {
      do {
        // Test all sel values given current combinations of inputs
        for (model.sel = 0; model.sel < 4; ++model.sel) {
          model.eval();
          uint8_t expected;
          if (model.sel == 0) expected = model.alpha;
          else if (model.sel == 1) expected = model.beta;
          else if (model.sel == 2) expected = model.gamma;
          else if (model.sel == 3) expected = model.alpha & (model.beta | model.gamma);
          REQUIRE(model.out == expected);
        }
      } while (++model.gamma);
    } while (++model.beta);
  } while (++model.alpha);
}
