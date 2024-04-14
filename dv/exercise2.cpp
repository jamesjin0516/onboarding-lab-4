#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <iostream>
#include <VExercise2.h>

TEST_CASE("Exercise 2") {
  VExercise2 model;
  uint8_t critbits = 0;
  // Test each combination of the 4 bits participating in XOR operation
  while (critbits < 16) {
    uint16_t input = 0;
    // Set input according to current combination
    if (critbits & 1) input |= 2;
    if (critbits & 2) input |= 8;
    if (critbits & 4) input |= 256;
    if (critbits & 8) input |= 1024;
    // Test reset
    model.reset = 1;
    model.clk = 1;
    model.init = ~input;
    model.eval();
    model.clk = 0;
    model.eval();
    REQUIRE(model.out == input);
    // Test shift if reset succeeded
    model.reset = 0;
    model.clk = 1;
    model.eval();
    model.clk = 0;
    model.eval();
    uint16_t next_bit = ((input >> 1) & 1) ^ ((input >> 3) & 1) ^ ((input >> 8) & 1) ^ ((input >> 10) & 1);
    input = input << 1;
    input |= next_bit;
    REQUIRE(model.out == input);
    ++critbits;
  }
}
