#ifndef WEILYCODER_MOD_UTILITY_HPP
#define WEILYCODER_MOD_UTILITY_HPP

/**
 * @file mod_utility.hpp
 * @brief Modular Arithmetic Utilities
 */

#include <cstdint>

namespace weilycoder {
using u128 = unsigned __int128;

/**
 * @brief Perform modular addition for 64-bit integers.
 * @tparam bit32 If true, won't use 128-bit arithmetic. You should ensure that
 *         all inputs are small enough to avoid overflow (i.e. bit-32).
 * @param a The first addend.
 * @param b The second addend.
 * @param modulus The modulus.
 * @return (a + b) % modulus
 */
template <bool bit32 = false>
constexpr uint64_t mod_add(uint64_t a, uint64_t b, uint64_t modulus) {
  if constexpr (bit32) {
    uint64_t res = a + b;
    if (res >= modulus)
      res -= modulus;
    return res;
  } else {
    u128 res = static_cast<u128>(a) + b;
    if (res >= modulus)
      res -= modulus;
    return res;
  }
}

/**
 * @brief Perform modular subtraction for 64-bit integers.
 * @tparam bit32 If true, won't use 128-bit arithmetic. You should ensure that
 *         all inputs are small enough to avoid overflow (i.e. bit-32).
 * @param a The minuend.
 * @param b The subtrahend.
 * @param modulus The modulus.
 * @return (a - b) % modulus
 */
template <bool bit32 = false>
constexpr uint64_t mod_sub(uint64_t a, uint64_t b, uint64_t modulus) {
  if constexpr (bit32) {
    uint64_t res = (a >= b) ? (a - b) : (modulus + a - b);
    return res;
  } else {
    u128 res = (a >= b) ? (a - b) : (static_cast<u128>(modulus) + a - b);
    return res;
  }
}

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
constexpr uint64_t mod_mul(uint64_t a, uint64_t b, uint64_t modulus) {
  if constexpr (bit32)
    return a * b % modulus;
  else
    return static_cast<u128>(a) * b % modulus;
}

/**
 * @brief Perform modular multiplication for 64-bit integers with a compile-time
 *        modulus.
 * @tparam Modulus The modulus.
 * @param a The first multiplicand.
 * @param b The second multiplicand.
 * @return (a * b) % Modulus
 */
template <uint64_t Modulus> constexpr uint64_t mod_mul(uint64_t a, uint64_t b) {
  if constexpr (Modulus <= UINT32_MAX)
    return a * b % Modulus;
  else
    return static_cast<u128>(a) * b % Modulus;
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
constexpr uint64_t mod_pow(uint64_t base, uint64_t exponent, uint64_t modulus) {
  uint64_t result = 1 % modulus;
  base %= modulus;
  while (exponent > 0) {
    if (exponent & 1)
      result = mod_mul<bit32>(result, base, modulus);
    base = mod_mul<bit32>(base, base, modulus);
    exponent >>= 1;
  }
  return result;
}
} // namespace weilycoder

#endif
