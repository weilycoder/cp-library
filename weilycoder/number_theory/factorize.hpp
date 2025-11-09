#ifndef WEILYCODER_NUMBER_THEORY_FACTORIZE_HPP
#define WEILYCODER_NUMBER_THEORY_FACTORIZE_HPP

/**
 * @file factorize.hpp
 * @brief Functions for factorizing numbers using Pollard's Rho algorithm
 */

#include "../random.hpp"
#include "mod_utility.hpp"
#include "prime.hpp"
#include <algorithm>
#include <array>
#include <cstdint>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

namespace weilycoder {
/**
 * @brief Pollard's Rho algorithm to find a non-trivial factor of x
 * @tparam bit32 Whether to use 32-bit modular multiplication
 * @param x The number to factorize
 * @param c The constant in the polynomial x^2 + c
 * @return A non-trivial factor of x
 */
template <bool bit32 = false> constexpr uint64_t pollard_rho(uint64_t x, uint64_t c) {
  if (x % 2 == 0)
    return 2;
  c = c % (x - 1) + 1;
  uint32_t step = 0, goal = 1;
  uint64_t s = 0, t = 0;
  uint64_t value = 1;
  for (;; goal <<= 1, s = t, value = 1) {
    for (step = 1; step <= goal; ++step) {
      t = mod_mul<bit32>(t, t, x) + c;
      if (t >= x)
        t -= x;
      uint64_t diff = (s >= t ? s - t : t - s);
      value = mod_mul<bit32>(value, diff, x);
      if (step % 127 == 0) {
        uint64_t d = std::gcd(value, x);
        if (d > 1)
          return d;
      }
    }
    uint64_t d = std::gcd(value, x);
    if (d > 1)
      return d;
  }
  return x;
}

/**
 * @brief Pollard's Rho algorithm to find a non-trivial factor of x
 * @tparam bit32 Whether to use 32-bit modular multiplication
 * @param x The number to factorize
 * @return A non-trivial factor of x
 */
template <bool bit32 = false> uint64_t pollard_rho(uint64_t x) {
  if (x % 2 == 0)
    return 2;
  static std::minstd_rand rng{};
  return pollard_rho<bit32>(x, rng());
}

/**
 * @brief Factorize a number into its prime factors
 * @tparam bit32 Whether to use 32-bit modular multiplication
 * @param x The number to factorize
 * @return A vector of prime factors of x
 */
template <bool bit32 = false> std::vector<uint64_t> factorize(uint64_t x) {
  std::vector<uint64_t> factors;
  std::vector<std::pair<uint64_t, size_t>> stk;
  stk.emplace_back(x, 1);
  while (!stk.empty()) {
    auto [cur, cnt] = stk.back();
    stk.pop_back();
    if (cur == 1)
      continue;
    if (is_prime(cur)) {
      factors.resize(factors.size() + cnt, cur);
      continue;
    }
    uint64_t factor = cur;
    do
      factor = pollard_rho<bit32>(cur);
    while (factor == cur);
    size_t factor_count = 0;
    while (cur % factor == 0)
      cur /= factor, ++factor_count;
    stk.emplace_back(cur, cnt);
    stk.emplace_back(factor, factor_count * cnt);
  }
  std::sort(factors.begin(), factors.end());
  return factors;
}

/**
 * @brief Factorize a number into its prime factors with fixed-size array
 * @tparam N The size of the output array
 * @tparam bit32 Whether to use 32-bit modular multiplication
 * @param x The number to factorize
 * @return An array of prime factors of x
 */
template <size_t N = 64, bool bit32 = false>
constexpr std::array<uint64_t, N> factorize_fixed(uint64_t x) {
  uint32_t random_state = 1;
  size_t factor_idx = 0, stk_idx = 0;
  std::array<uint64_t, N> factors{};
  std::array<uint64_t, 64> stk_val{};
  std::array<size_t, 64> stk_cnt{};
  stk_val[stk_idx] = x, stk_cnt[stk_idx++] = 1;
  while (stk_idx > 0) {
    uint64_t cur = stk_val[--stk_idx];
    size_t cnt = stk_cnt[stk_idx];
    if (cur == 1)
      continue;
    if (is_prime(cur)) {
      for (size_t i = 0; i < cnt; ++i)
        factors[factor_idx++] = cur;
    } else {
      uint64_t factor = cur;
      do
        factor = pollard_rho<bit32>(cur, lcg_nr(random_state));
      while (factor == cur);
      size_t factor_count = 0;
      while (cur % factor == 0)
        cur /= factor, ++factor_count;
      stk_val[stk_idx] = cur, stk_cnt[stk_idx++] = cnt;
      stk_val[stk_idx] = factor, stk_cnt[stk_idx++] = factor_count * cnt;
    }
  }
  for (size_t i = 1; i < factor_idx; ++i) {
    uint64_t key = factors[i];
    size_t j = i;
    while (j > 0 && factors[j - 1] > key) {
      factors[j] = factors[j - 1];
      --j;
    }
    factors[j] = key;
  }
  return factors;
}
} // namespace weilycoder

#endif
