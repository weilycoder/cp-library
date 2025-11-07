#ifndef WEILYCODER_NUMBER_THEORY_PRIMITIVE_ROOT_HPP
#define WEILYCODER_NUMBER_THEORY_PRIMITIVE_ROOT_HPP

/**
 * @file primitive_root.hpp
 * @brief Functions to find primitive roots modulo a prime
 */

#include "factorize.hpp"
#include "mod_utility.hpp"
#include <array>
#include <cstdint>
#include <vector>

namespace weilycoder {
/**
 * @brief Check if g is a primitive root modulo p
 * @tparam N The size of the factors array
 * @tparam bit32 Whether to use 32-bit modular multiplication
 * @param g The candidate primitive root
 * @param p The prime modulus
 * @param factors The prime factors of p - 1
 * @return true if g is a primitive root modulo p, false otherwise
 */
template <size_t N = 64, bool bit32 = false>
constexpr bool is_primitive_root(uint64_t g, uint64_t p,
                                 const std::array<uint64_t, N> &factors) {
  for (size_t i = 0; i < N; ++i) {
    uint64_t q = factors[i];
    if (q == 0)
      break;
    if (mod_pow<bit32>(g, (p - 1) / q, p) == 1)
      return false;
  }
  return true;
}

/**
 * @brief Check if g is a primitive root modulo p
 * @tparam bit32 Whether to use 32-bit modular multiplication
 * @param g The candidate primitive root
 * @param p The prime modulus
 * @param factors The prime factors of p - 1
 * @return true if g is a primitive root modulo p, false otherwise
 */
template <bool bit32 = false>
bool is_primitive_root(uint64_t g, uint64_t p, const std::vector<uint64_t> &factors) {
  const size_t N = factors.size();
  for (size_t i = 0; i < N; ++i) {
    uint64_t q = factors[i];
    if (q == 0)
      break;
    if (mod_pow<bit32>(g, (p - 1) / q, p) == 1)
      return false;
  }
  return true;
}

/**
 * @brief Find a primitive root modulo a prime p
 * @tparam bit32 Whether to use 32-bit modular multiplication
 * @param p The prime modulus
 * @return A primitive root modulo p, or 0 if p is not prime
 */
template <bool bit32 = false, size_t N = 64>
constexpr uint64_t prime_primitive_root(uint64_t p) {
  if (p == 2)
    return 1;
  if (!is_prime(p))
    return 0;
  auto factors = factorize_fixed<N, bit32>(p - 1);
  auto factors_set = std::array<uint64_t, N>{};
  size_t factor_count = 0;
  for (size_t i = 0; i < N; ++i) {
    uint64_t q = factors[i];
    if (q == 0)
      break;
    if (i == 0 || q != factors[i - 1])
      factors_set[factor_count++] = q;
  }
  for (uint64_t g = 2; g < p; ++g)
    if (is_primitive_root<N, bit32>(g, p, factors_set))
      return g;
  return 0;
}

/**
 * @brief Find a primitive root modulo a prime (compile-time version)
 * @tparam prime The prime modulus
 * @return A primitive root modulo prime.
 */
template <uint64_t prime> constexpr uint64_t prime_primitive_root() {
  if constexpr (prime == 2)
    return 1;
  if (prime < UINT32_MAX)
    return prime_primitive_root<true, 32>(prime);
  return prime_primitive_root<false, 64>(prime);
}
} // namespace weilycoder

#endif
