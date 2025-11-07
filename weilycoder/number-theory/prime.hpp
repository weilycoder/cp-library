#ifndef WEILYCODER_PRIME_HPP
#define WEILYCODER_PRIME_HPP

/**
 * @file prime.hpp
 * @brief Prime Number Utilities
 */

#include "mod_utility.hpp"
#include <cstdint>
#include <type_traits>

namespace weilycoder {
/**
 * @brief Miller-Rabin primality test for a given base.
 * @tparam bit32 If true, won't use 128-bit arithmetic. You should ensure that
 *         all inputs are small enough to avoid overflow (i.e. bit-32).
 * @tparam base The base to test.
 * @param n The number to test for primality.
 * @param d An odd component of n-1 (n-1 = d * 2^s).
 * @param s The exponent of 2 in the factorization of n-1.
 * @return true if n is probably prime for the given base, false if composite.
 */
template <bool bit32, uint64_t base>
constexpr bool miller_rabin_test(uint64_t n, uint64_t d, uint32_t s) {
  uint64_t x = mod_pow<bit32>(base, d, n);
  if (x == 0 || x == 1 || x == n - 1)
    return true;
  for (uint32_t r = 1; r < s; ++r) {
    x = mod_mul<bit32>(x, x, n);
    if (x == n - 1)
      return true;
  }
  return false;
}

/**
 * @brief Variadic template to test multiple bases in Miller-Rabin test.
 * @tparam bit32 If true, won't use 128-bit arithmetic. You should ensure that
 *         all inputs are small enough to avoid overflow (i.e. bit-32).
 * @tparam base The first base to test.
 * @tparam Rest The remaining bases to test.
 * @param n The number to test for primality.
 * @param d An odd component of n-1 (n-1 = d * 2^s).
 * @param s The exponent of 2 in the factorization of n-1.
 * @return true if n is probably prime for all given bases, false if composite.
 */
template <bool bit32, uint64_t base, uint64_t... Rest>
constexpr std::enable_if_t<(sizeof...(Rest) != 0), bool>
miller_rabin_test(uint64_t n, uint64_t d, uint32_t s) {
  return miller_rabin_test<bit32, base>(n, d, s) &&
         miller_rabin_test<bit32, Rest...>(n, d, s);
}

/**
 * @brief Miller-Rabin primality test using multiple bases.
 * @tparam bit32 If true, won't use 128-bit arithmetic. You should ensure that
 *         all inputs are small enough to avoid overflow (i.e. bit-32).
 * @tparam bases The bases to test.
 * @param n The number to test for primality.
 * @return true if n is probably prime, false if composite.
 */
template <bool bit32, uint64_t... bases> constexpr bool miller_rabin(uint64_t n) {
  if (n < 2)
    return false;
  if (n == 2 || n == 3)
    return true;
  if (n % 2 == 0)
    return false;

  uint64_t d = n - 1, s = 0;
  for (; d % 2 == 0; d /= 2)
    ++s;

  return miller_rabin_test<bit32, bases...>(n, d, s);
}

/**
 * @brief Miller-Rabin primality test optimized for 64-bit integers.
 *        Uses a fixed set of bases that guarantee correctness
 *        for 64-bit integers.
 * @param n The number to test for primality.
 * @return true if n is prime, false if not prime.
 */
constexpr bool miller_rabin64(uint64_t n) {
  return miller_rabin<false, 2, 325, 9375, 28178, 450775, 9780504, 1795265022>(n);
}

/**
 * @brief Miller-Rabin primality test optimized for 32-bit integers.
 *        Uses a fixed set of bases that guarantee correctness
 *        for 32-bit integers.
 * @param n The number to test for primality.
 * @return true if n is prime, false if not prime.
 */
constexpr bool miller_rabin32(uint32_t n) { return miller_rabin<true, 2, 7, 61>(n); }

constexpr bool is_prime(uint64_t n) {
  if (n <= UINT32_MAX)
    return miller_rabin32(static_cast<uint32_t>(n));
  return miller_rabin64(n);
}
} // namespace weilycoder

#endif
