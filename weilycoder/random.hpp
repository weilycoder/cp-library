#ifndef WEILYCODER_CONST_RAND_HPP
#define WEILYCODER_CONST_RAND_HPP

/**
 * @file random.hpp
 * @brief Lightweight Compile-Time Pseudo-Random Number Generators
 */

#include <cstdint>

namespace weilycoder {
/**
 * @brief Linear Congruential Generator (LCG) to produce pseudo-random numbers
 *        at compile-time.
 * @tparam a The multiplier.
 * @tparam c The increment.
 * @tparam m The modulus.
 * @param state The current state of the generator.
 * @return The next state of the generator.
 */
template <uint32_t a, uint32_t c, uint64_t m>
constexpr uint32_t &lcg_next(uint32_t &state) {
  state = (static_cast<uint64_t>(a) * state + c) % m;
  return state;
}

/**
 * @brief LCG using parameters from "Minimal Standard" by Park and Miller.
 * @param state The current state of the generator.
 * @return The next state of the generator.
 */
constexpr uint32_t &lcg_minstd(uint32_t &state) {
  return lcg_next<48271, 0, 2147483647>(state);
}

/**
 * @brief LCG using parameters from "minstd_rand0" by Park and Miller.
 * @param state The current state of the generator.
 * @return The next state of the generator.
 */
constexpr uint32_t &lcg_minstd_rand0(uint32_t &state) {
  return lcg_next<16807, 0, 2147483647>(state);
}

/**
 * @brief LCG using parameters from "Numerical Recipes".
 * @param state The current state of the generator.
 * @return The next state of the generator.
 */
constexpr uint32_t &lcg_nr(uint32_t &state) {
  return lcg_next<1103515245, 12345, 4294967296>(state);
}
} // namespace weilycoder

#endif
