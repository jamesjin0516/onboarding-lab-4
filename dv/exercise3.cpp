#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <iostream>
#include <VExercise3.h>


uint8_t mystery1(uint8_t a, uint8_t b, uint8_t c) {
  // Simulate Mystery1 module's output
  if (a == 0) return (b & 7) << 3 | (c & 7) & ((1 << 6) - 1);
  if (a == 1) return 1 << 6 | (c & 7) << 3 | (b & 7);
  if (a == 2) return b;
  if (a == 3) return c;
  std::cerr << "Invalid opcode a: " << static_cast<unsigned>(a) << " (valid values: 0 - 3)" << std::endl;
  exit(1);
}


void step(VExercise3* const model) {
  model->clk = 1;
  model->eval();
  model->clk = 0;
  model->eval();
}


TEST_CASE("Exercise 3") {
  VExercise3 model;
  uint16_t b, c;
  model.a = 0;
  // Test all combinations of Mystery1 output
  while (model.a < 16) {
    model.b = b;
    model.c = c;
    model.reset = 1;
    step(&model);
    // Verify Mystery1 output by checking whether Mystery2 resets correctly
    uint8_t a_in = mystery1(model.a & 3, b & 255, c & 255);
    uint8_t b_in = mystery1((model.a & 12) >> 2, (b & 65280) >> 8, (c & 65280) >> 8);
    uint16_t out = b_in << 8 | a_in;
    REQUIRE(model.out == out);
    model.reset = 0;
    // If Mystery1 functions correctly, test Mystery2's output cycles
    for (unsigned state = 0; state < 5; ++state) {
      step(&model);
      if (state == 0) out = a_in << 8 | out & 255;
      else if (state == 1) out = out & 65280 | b_in;
      else if (state == 2) out = (out & 255) << 8 | (out & 65280) >> 8;
      else if (state == 3) out = (out & 15) << 12 | (out & 240) << 4 | (out & 3840) >> 4 | (out & 61440) >> 12;
      else if (state == 4) {
        // Manually perform XOR reduction operation
        uint16_t reduced = 0;
        uint16_t mask = 1;
        for (unsigned digit = 0; digit < 16; ++digit) {
          reduced ^= (out & mask) >> digit;
          mask <<= 1;
        }
        out = reduced;
      }
      REQUIRE(model.out == out);
    }
    ++model.a;
  }
}
