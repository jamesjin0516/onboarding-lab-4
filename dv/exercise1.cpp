#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <iostream>
#include <VExercise1.h>


uint8_t operation(uint8_t code, uint8_t a, uint8_t b) {
  if (code == 0) return a ^ b;
  if (code == 1) return b < 8 ? a << b : 0;
  if (code == 2) return a % b;
  if (code == 3) return ~(a & b);
  std::cerr << "Unknown opcode: " << code << std::endl;
  exit(1);
}


TEST_CASE("Exercise 1") {
  VExercise1 model;
  for (uint8_t code = 0; code < 4; ++code) {
    model.op = code;
    model.a = 0;
    model.b = 0;
    do {
      if (code == 2 && model.b == 0) continue;
      do {
        model.eval();
        uint8_t ans = operation(code, model.a, model.b);
        REQUIRE(model.out == ans);
      } while (++model.a);
    } while (++model.b);
  }
}
