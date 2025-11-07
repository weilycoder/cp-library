#ifndef WEILYCODER_POLY_NTT_HPP
#define WEILYCODER_POLY_NTT_HPP

#include "../number-theory/mod_utility.hpp"
#include "../number-theory/primitive_root.hpp"
#include "fft_utility.hpp"
#include <cstdint>
#include <vector>

namespace weilycoder {
/**
 * @brief Number Theoretic Transform (NTT)
 * @tparam mod The prime modulus
 * @tparam inverse Whether to perform the inverse NTT
 * @tparam bit32 Whether to use 32-bit modular multiplication
 * @tparam root A primitive root modulo mod
 * @param y The input/output vector to be transformed
 */
template <uint64_t mod, bool inverse = false, bool bit32 = false,
          uint64_t root = prime_primitive_root<mod>()>
void ntt(std::vector<uint64_t> &y) {
  static_assert(is_prime(mod), "mod must be a prime");
  fft_change(y);
  size_t len = y.size();
  if (len == 0 || (len & (len - 1)) != 0)
    throw std::invalid_argument("Length of input vector must be a power of two");
  if ((mod - 1) % len != 0)
    throw std::invalid_argument(
        "mod - 1 must be divisible by the length of input vector");
  constexpr uint64_t g = inverse ? mod_pow<bit32>(root, mod - 2, mod) : root;
  for (size_t h = 2; h <= len; h <<= 1) {
    uint64_t wn = mod_pow<bit32>(g, (mod - 1) / h, mod);
    for (size_t j = 0; j < len; j += h) {
      uint64_t w = 1;
      for (size_t k = j; k < j + (h >> 1); ++k) {
        uint64_t u = y[k];
        uint64_t t = mod_mul<bit32>(w, y[k + (h >> 1)], mod);
        y[k] = mod_add<bit32>(u, t, mod);
        y[k + (h >> 1)] = mod_sub<bit32>(u, t, mod);
        w = mod_mul<bit32>(w, wn, mod);
      }
    }
  }
  if constexpr (inverse) {
    uint64_t inv_len = mod_pow<bit32>(len, mod - 2, mod);
    for (size_t i = 0; i < len; ++i)
      y[i] = mod_mul<bit32>(y[i], inv_len, mod);
  }
}

/**
 * @brief Number Theoretic Transform (NTT) using 32-bit modular multiplication
 * @tparam mod The prime modulus
 * @tparam inverse Whether to perform the inverse NTT
 * @tparam root A primitive root modulo mod
 * @param y The input/output vector to be transformed
 */
template <uint64_t mod, bool inverse = false, uint64_t root = prime_primitive_root(mod)>
void ntt_32(std::vector<uint64_t> &y) {
  ntt<mod, inverse, true, root>(y);
}
} // namespace weilycoder

#endif
