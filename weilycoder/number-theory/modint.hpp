#ifndef WEILYCODER_MODINT_HPP
#define WEILYCODER_MODINT_HPP

#include <cstdint>

/**
 * @file modint.hpp
 * @brief Modular Integer Arithmetic Utilities
 */

namespace weilycoder {
/**
 * @brief Perform modular multiplication for 64-bit integers.
 * @tparam bit32 If true, won't use 128-bit arithmetic. You should ensure that
 *         all inputs are small enough to avoid overflow (i.e. bit-32).
 * @param a The first multiplicand.
 * @param b The second multiplicand.
 * @param modulus The modulus.
 * @return (a * b) % modulus
 */
template <bool bit32 = false>
uint64_t modular_multiply_64(uint64_t a, uint64_t b, uint64_t modulus) {
  if constexpr (bit32)
    return a * b % modulus;
  else
    return static_cast<unsigned __int128>(a) * b % modulus;
}

/**
 * @brief Perform modular exponentiation for 64-bit integers.
 * @tparam bit32 If true, won't use 128-bit arithmetic. You should ensure that
 *         all inputs are small enough to avoid overflow (i.e. bit-32).
 * @param base The base number.
 * @param exponent The exponent.
 * @param modulus The modulus.
 * @return (base^exponent) % modulus
 */
template <bool bit32 = false>
constexpr uint64_t fast_power_64(uint64_t base, uint64_t exponent, uint64_t modulus) {
  uint64_t result = 1 % modulus;
  base %= modulus;
  while (exponent > 0) {
    if (exponent & 1)
      result = modular_multiply_64<bit32>(result, base, modulus);
    base = modular_multiply_64<bit32>(base, base, modulus);
    exponent >>= 1;
  }
  return result;
}
} // namespace weilycoder

#endif
