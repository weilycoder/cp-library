#ifndef WEILYCODER_NUMBER_THEORY_FACTORIZE_HPP
#define WEILYCODER_NUMBER_THEORY_FACTORIZE_HPP

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
template <bool bit32 = false> constexpr uint64_t pollard_rho(uint64_t x, uint64_t c) {
  if (x % 2 == 0)
    return 2;
  uint32_t step = 0, goal = 1;
  uint64_t s = 0, t = 0;
  uint64_t value = 1;
  for (;; goal <<= 1, s = t, value = 1) {
    for (step = 1; step <= goal; ++step) {
      t = modular_multiply_64<bit32>(t, t, x) + c;
      if (t >= x)
        t -= x;
      uint64_t diff = (s >= t ? s - t : t - s);
      value = modular_multiply_64<bit32>(value, diff, x);
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

template <bool bit32 = false> uint64_t pollard_rho(uint64_t x) {
  static std::minstd_rand rng{};
  if (x % 2 == 0)
    return 2;
  uint64_t c = rng() % (x - 1) + 1;
  return pollard_rho<bit32>(x, c);
}

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

template <size_t N = 64, bool bit32 = false>
constexpr std::array<uint64_t, N> factorize_fixed(uint64_t x) {
  size_t factor_idx = 0, stk_idx = 0;
  std::array<uint64_t, N> factors{};
  std::array<std::pair<uint64_t, size_t>, 64> stk{};
  stk[stk_idx++] = {x, 1};
  while (stk_idx > 0) {
    auto [cur, cnt] = stk[--stk_idx];
    if (cur == 1)
      continue;
    if (is_prime(cur))
      std::fill(factors.begin() + factor_idx, factors.begin() + factor_idx + cnt, cur),
          factor_idx += cnt;
    else {
      uint64_t factor = cur;
      do
        factor = pollard_rho<bit32>(cur);
      while (factor == cur);
      size_t factor_count = 0;
      while (cur % factor == 0)
        cur /= factor, ++factor_count;
      stk[stk_idx++] = {cur, cnt};
      stk[stk_idx++] = {factor, factor_count * cnt};
    }
  }
  std::sort(factors.begin(), factors.begin() + factor_idx);
  return factors;
}
} // namespace weilycoder

#endif
