---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: weilycoder/number_theory/factorize.hpp
    title: Functions for factorizing numbers using Pollard's Rho algorithm
  - icon: ':heavy_check_mark:'
    path: weilycoder/number_theory/mod_utility.hpp
    title: Modular Arithmetic Utilities
  - icon: ':heavy_check_mark:'
    path: weilycoder/number_theory/prime.hpp
    title: Prime Number Utilities
  - icon: ':heavy_check_mark:'
    path: weilycoder/random.hpp
    title: Lightweight Compile-Time Pseudo-Random Number Generators
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/elementary_func/exponential.hpp
    title: Polynomial Exponential Functions
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/elementary_func/inverse.hpp
    title: Polynomial Inversion functions using Newton's method and NTT.
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/elementary_func/logarithm.hpp
    title: Polynomial Logarithm Functions
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/elementary_func/multiply.hpp
    title: Polynomial Multiplication Functions
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/mtt_convolve.hpp
    title: Multiply two polynomials under modulo using MTT with 3 NTT-friendly moduli.
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/ntt.hpp
    title: Number Theoretic Transform (NTT) implementation
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/ntt_convolve.hpp
    title: Multiplying polynomials using Number Theoretic Transform (NTT)
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/convolution_mod.test.cpp
    title: test/convolution_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/convolution_mod_1000000007.test.cpp
    title: test/convolution_mod_1000000007.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/exp_of_formal_power_series.test.cpp
    title: test/exp_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/inv_of_formal_power_series.test.cpp
    title: test/inv_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/log_of_formal_power_series.test.cpp
    title: test/log_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/primitive_root.test.cpp
    title: test/primitive_root.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Functions to find primitive roots modulo a prime
    links: []
  bundledCode: "#line 1 \"weilycoder/number_theory/primitive_root.hpp\"\n\n\n\n/**\n\
    \ * @file primitive_root.hpp\n * @brief Functions to find primitive roots modulo\
    \ a prime\n */\n\n#line 1 \"weilycoder/number_theory/factorize.hpp\"\n\n\n\n/**\n\
    \ * @file factorize.hpp\n * @brief Functions for factorizing numbers using Pollard's\
    \ Rho algorithm\n */\n\n#line 1 \"weilycoder/random.hpp\"\n\n\n\n/**\n * @file\
    \ random.hpp\n * @brief Lightweight Compile-Time Pseudo-Random Number Generators\n\
    \ */\n\n#include <cstdint>\n\nnamespace weilycoder {\n/**\n * @brief Linear Congruential\
    \ Generator (LCG) to produce pseudo-random numbers\n *        at compile-time.\n\
    \ * @tparam a The multiplier.\n * @tparam c The increment.\n * @tparam m The modulus.\n\
    \ * @param state The current state of the generator.\n * @return The next state\
    \ of the generator.\n */\ntemplate <uint32_t a, uint32_t c, uint64_t m>\nconstexpr\
    \ uint32_t &lcg_next(uint32_t &state) {\n  state = (static_cast<uint64_t>(a) *\
    \ state + c) % m;\n  return state;\n}\n\n/**\n * @brief LCG using parameters from\
    \ \"Minimal Standard\" by Park and Miller.\n * @param state The current state\
    \ of the generator.\n * @return The next state of the generator.\n */\nconstexpr\
    \ uint32_t &lcg_minstd(uint32_t &state) {\n  return lcg_next<48271, 0, 2147483647>(state);\n\
    }\n\n/**\n * @brief LCG using parameters from \"minstd_rand0\" by Park and Miller.\n\
    \ * @param state The current state of the generator.\n * @return The next state\
    \ of the generator.\n */\nconstexpr uint32_t &lcg_minstd_rand0(uint32_t &state)\
    \ {\n  return lcg_next<16807, 0, 2147483647>(state);\n}\n\n/**\n * @brief LCG\
    \ using parameters from \"Numerical Recipes\".\n * @param state The current state\
    \ of the generator.\n * @return The next state of the generator.\n */\nconstexpr\
    \ uint32_t &lcg_nr(uint32_t &state) {\n  return lcg_next<1103515245, 12345, 4294967296>(state);\n\
    }\n} // namespace weilycoder\n\n\n#line 1 \"weilycoder/number_theory/mod_utility.hpp\"\
    \n\n\n\n/**\n * @file mod_utility.hpp\n * @brief Modular Arithmetic Utilities\n\
    \ */\n\n#line 10 \"weilycoder/number_theory/mod_utility.hpp\"\n\nnamespace weilycoder\
    \ {\nusing u128 = unsigned __int128;\n\n/**\n * @brief Perform modular addition\
    \ for 64-bit integers.\n * @tparam bit32 If true, won't use 128-bit arithmetic.\
    \ You should ensure that\n *         all inputs are small enough to avoid overflow\
    \ (i.e. bit-32).\n * @param a The first addend.\n * @param b The second addend.\n\
    \ * @param modulus The modulus.\n * @return (a + b) % modulus\n */\ntemplate <bool\
    \ bit32 = false>\nconstexpr uint64_t mod_add(uint64_t a, uint64_t b, uint64_t\
    \ modulus) {\n  if constexpr (bit32) {\n    uint64_t res = a + b;\n    if (res\
    \ >= modulus)\n      res -= modulus;\n    return res;\n  } else {\n    u128 res\
    \ = static_cast<u128>(a) + b;\n    if (res >= modulus)\n      res -= modulus;\n\
    \    return res;\n  }\n}\n\n/**\n * @brief Perform modular addition for 64-bit\
    \ integers with a compile-time\n *        modulus.\n * @tparam Modulus The modulus.\n\
    \ * @param a The first addend.\n * @param b The second addend.\n * @return (a\
    \ + b) % Modulus\n */\ntemplate <uint64_t Modulus> constexpr uint64_t mod_add(uint64_t\
    \ a, uint64_t b) {\n  if constexpr (Modulus <= UINT32_MAX) {\n    uint64_t res\
    \ = a + b;\n    if (res >= Modulus)\n      res -= Modulus;\n    return res;\n\
    \  } else {\n    u128 res = static_cast<u128>(a) + b;\n    if (res >= Modulus)\n\
    \      res -= Modulus;\n    return res;\n  }\n}\n\n/**\n * @brief Perform modular\
    \ subtraction for 64-bit integers.\n * @tparam bit32 If true, won't use 128-bit\
    \ arithmetic. You should ensure that\n *         all inputs are small enough to\
    \ avoid overflow (i.e. bit-32).\n * @param a The minuend.\n * @param b The subtrahend.\n\
    \ * @param modulus The modulus.\n * @return (a - b) % modulus\n */\ntemplate <bool\
    \ bit32 = false>\nconstexpr uint64_t mod_sub(uint64_t a, uint64_t b, uint64_t\
    \ modulus) {\n  if constexpr (bit32) {\n    uint64_t res = (a >= b) ? (a - b)\
    \ : (modulus + a - b);\n    return res;\n  } else {\n    u128 res = (a >= b) ?\
    \ (a - b) : (static_cast<u128>(modulus) + a - b);\n    return res;\n  }\n}\n\n\
    /**\n * @brief Perform modular subtraction for 64-bit integers with a compile-time\n\
    \ *        modulus.\n * @tparam Modulus The modulus.\n * @param a The minuend.\n\
    \ * @param b The subtrahend.\n * @return (a - b) % Modulus\n */\ntemplate <uint64_t\
    \ Modulus> constexpr uint64_t mod_sub(uint64_t a, uint64_t b) {\n  if constexpr\
    \ (Modulus <= UINT32_MAX) {\n    uint64_t res = (a >= b) ? (a - b) : (Modulus\
    \ + a - b);\n    return res;\n  } else {\n    u128 res = (a >= b) ? (a - b) :\
    \ (static_cast<u128>(Modulus) + a - b);\n    return res;\n  }\n}\n\n/**\n * @brief\
    \ Perform modular multiplication for 64-bit integers.\n * @tparam bit32 If true,\
    \ won't use 128-bit arithmetic. You should ensure that\n *         all inputs\
    \ are small enough to avoid overflow (i.e. bit-32).\n * @param a The first multiplicand.\n\
    \ * @param b The second multiplicand.\n * @param modulus The modulus.\n * @return\
    \ (a * b) % modulus\n */\ntemplate <bool bit32 = false>\nconstexpr uint64_t mod_mul(uint64_t\
    \ a, uint64_t b, uint64_t modulus) {\n  if constexpr (bit32)\n    return a * b\
    \ % modulus;\n  else\n    return static_cast<u128>(a) * b % modulus;\n}\n\n/**\n\
    \ * @brief Perform modular multiplication for 64-bit integers with a compile-time\n\
    \ *        modulus.\n * @tparam Modulus The modulus.\n * @param a The first multiplicand.\n\
    \ * @param b The second multiplicand.\n * @return (a * b) % Modulus\n */\ntemplate\
    \ <uint64_t Modulus> constexpr uint64_t mod_mul(uint64_t a, uint64_t b) {\n  if\
    \ constexpr (Modulus <= UINT32_MAX)\n    return a * b % Modulus;\n  else\n   \
    \ return static_cast<u128>(a) * b % Modulus;\n}\n\n/**\n * @brief Perform modular\
    \ exponentiation for 64-bit integers.\n * @tparam bit32 If true, won't use 128-bit\
    \ arithmetic. You should ensure that\n *         all inputs are small enough to\
    \ avoid overflow (i.e. bit-32).\n * @param base The base number.\n * @param exponent\
    \ The exponent.\n * @param modulus The modulus.\n * @return (base^exponent) %\
    \ modulus\n */\ntemplate <bool bit32 = false>\nconstexpr uint64_t mod_pow(uint64_t\
    \ base, uint64_t exponent, uint64_t modulus) {\n  uint64_t result = 1 % modulus;\n\
    \  base %= modulus;\n  while (exponent > 0) {\n    if (exponent & 1)\n      result\
    \ = mod_mul<bit32>(result, base, modulus);\n    base = mod_mul<bit32>(base, base,\
    \ modulus);\n    exponent >>= 1;\n  }\n  return result;\n}\n\n/**\n * @brief Perform\
    \ modular exponentiation for 64-bit integers with a compile-time\n *        modulus.\n\
    \ * @tparam Modulus The modulus.\n * @param base The base number.\n * @param exponent\
    \ The exponent.\n * @return (base^exponent) % Modulus\n */\ntemplate <uint64_t\
    \ Modulus>\nconstexpr uint64_t mod_pow(uint64_t base, uint64_t exponent) {\n \
    \ uint64_t result = 1 % Modulus;\n  base %= Modulus;\n  while (exponent > 0) {\n\
    \    if (exponent & 1)\n      result = mod_mul<Modulus>(result, base);\n    base\
    \ = mod_mul<Modulus>(base, base);\n    exponent >>= 1;\n  }\n  return result;\n\
    }\n\n/**\n * @brief Compute the modular inverse of a 64-bit integer using Fermat's\
    \ Little\n *        Theorem.\n * @tparam Modulus The modulus (must be prime).\n\
    \ * @param a The number to find the modular inverse of.\n * @return The modular\
    \ inverse of a modulo Modulus.\n */\ntemplate <uint64_t Modulus> constexpr uint64_t\
    \ mod_inv(uint64_t a) {\n  return mod_pow<Modulus>(a, Modulus - 2);\n}\n\n/**\n\
    \ * @brief Compute the modular inverse of a compile-time 64-bit integer using\n\
    \ *        Fermat's Little Theorem.\n * @tparam Modulus The modulus (must be prime).\n\
    \ * @tparam a The number to find the modular inverse of.\n * @return The modular\
    \ inverse of a modulo Modulus.\n */\ntemplate <uint64_t Modulus, uint64_t a> constexpr\
    \ uint64_t mod_inv() {\n  return mod_pow<Modulus>(a, Modulus - 2);\n}\n} // namespace\
    \ weilycoder\n\n\n#line 1 \"weilycoder/number_theory/prime.hpp\"\n\n\n\n/**\n\
    \ * @file prime.hpp\n * @brief Prime Number Utilities\n */\n\n#line 11 \"weilycoder/number_theory/prime.hpp\"\
    \n#include <type_traits>\n\nnamespace weilycoder {\n/**\n * @brief Miller-Rabin\
    \ primality test for a given base.\n * @tparam bit32 If true, won't use 128-bit\
    \ arithmetic. You should ensure that\n *         all inputs are small enough to\
    \ avoid overflow (i.e. bit-32).\n * @tparam base The base to test.\n * @param\
    \ n The number to test for primality.\n * @param d An odd component of n-1 (n-1\
    \ = d * 2^s).\n * @param s The exponent of 2 in the factorization of n-1.\n *\
    \ @return true if n is probably prime for the given base, false if composite.\n\
    \ */\ntemplate <bool bit32, uint64_t base>\nconstexpr bool miller_rabin_test(uint64_t\
    \ n, uint64_t d, uint32_t s) {\n  uint64_t x = mod_pow<bit32>(base, d, n);\n \
    \ if (x == 0 || x == 1 || x == n - 1)\n    return true;\n  for (uint32_t r = 1;\
    \ r < s; ++r) {\n    x = mod_mul<bit32>(x, x, n);\n    if (x == n - 1)\n     \
    \ return true;\n  }\n  return false;\n}\n\n/**\n * @brief Variadic template to\
    \ test multiple bases in Miller-Rabin test.\n * @tparam bit32 If true, won't use\
    \ 128-bit arithmetic. You should ensure that\n *         all inputs are small\
    \ enough to avoid overflow (i.e. bit-32).\n * @tparam base The first base to test.\n\
    \ * @tparam Rest The remaining bases to test.\n * @param n The number to test\
    \ for primality.\n * @param d An odd component of n-1 (n-1 = d * 2^s).\n * @param\
    \ s The exponent of 2 in the factorization of n-1.\n * @return true if n is probably\
    \ prime for all given bases, false if composite.\n */\ntemplate <bool bit32, uint64_t\
    \ base, uint64_t... Rest>\nconstexpr std::enable_if_t<(sizeof...(Rest) != 0),\
    \ bool>\nmiller_rabin_test(uint64_t n, uint64_t d, uint32_t s) {\n  return miller_rabin_test<bit32,\
    \ base>(n, d, s) &&\n         miller_rabin_test<bit32, Rest...>(n, d, s);\n}\n\
    \n/**\n * @brief Miller-Rabin primality test using multiple bases.\n * @tparam\
    \ bit32 If true, won't use 128-bit arithmetic. You should ensure that\n *    \
    \     all inputs are small enough to avoid overflow (i.e. bit-32).\n * @tparam\
    \ bases The bases to test.\n * @param n The number to test for primality.\n *\
    \ @return true if n is probably prime, false if composite.\n */\ntemplate <bool\
    \ bit32, uint64_t... bases> constexpr bool miller_rabin(uint64_t n) {\n  if (n\
    \ < 2)\n    return false;\n  if (n == 2 || n == 3)\n    return true;\n  if (n\
    \ % 2 == 0)\n    return false;\n\n  uint64_t d = n - 1, s = 0;\n  for (; d % 2\
    \ == 0; d /= 2)\n    ++s;\n\n  return miller_rabin_test<bit32, bases...>(n, d,\
    \ s);\n}\n\n/**\n * @brief Miller-Rabin primality test optimized for 64-bit integers.\n\
    \ *        Uses a fixed set of bases that guarantee correctness\n *        for\
    \ 64-bit integers.\n * @param n The number to test for primality.\n * @return\
    \ true if n is prime, false if not prime.\n */\nconstexpr bool miller_rabin64(uint64_t\
    \ n) {\n  return miller_rabin<false, 2, 325, 9375, 28178, 450775, 9780504, 1795265022>(n);\n\
    }\n\n/**\n * @brief Miller-Rabin primality test optimized for 32-bit integers.\n\
    \ *        Uses a fixed set of bases that guarantee correctness\n *        for\
    \ 32-bit integers.\n * @param n The number to test for primality.\n * @return\
    \ true if n is prime, false if not prime.\n */\nconstexpr bool miller_rabin32(uint32_t\
    \ n) { return miller_rabin<true, 2, 7, 61>(n); }\n\nconstexpr bool is_prime(uint64_t\
    \ n) {\n  if (n <= UINT32_MAX)\n    return miller_rabin32(static_cast<uint32_t>(n));\n\
    \  return miller_rabin64(n);\n}\n\n/**\n * @brief Compile-time primality test\
    \ for a given integer.\n * @tparam x The integer to test for primality.\n * @return\
    \ true if x is prime, false otherwise.\n */\ntemplate <uint64_t x> constexpr bool\
    \ is_prime() { return is_prime(x); }\n} // namespace weilycoder\n\n\n#line 12\
    \ \"weilycoder/number_theory/factorize.hpp\"\n#include <algorithm>\n#include <array>\n\
    #line 15 \"weilycoder/number_theory/factorize.hpp\"\n#include <numeric>\n#include\
    \ <random>\n#include <utility>\n#include <vector>\n\nnamespace weilycoder {\n\
    /**\n * @brief Pollard's Rho algorithm to find a non-trivial factor of x\n * @tparam\
    \ bit32 Whether to use 32-bit modular multiplication\n * @param x The number to\
    \ factorize\n * @param c The constant in the polynomial x^2 + c\n * @return A\
    \ non-trivial factor of x\n */\ntemplate <bool bit32 = false> constexpr uint64_t\
    \ pollard_rho(uint64_t x, uint64_t c) {\n  if (x % 2 == 0)\n    return 2;\n  c\
    \ = c % (x - 1) + 1;\n  uint32_t step = 0, goal = 1;\n  uint64_t s = 0, t = 0;\n\
    \  uint64_t value = 1;\n  for (;; goal <<= 1, s = t, value = 1) {\n    for (step\
    \ = 1; step <= goal; ++step) {\n      t = mod_mul<bit32>(t, t, x) + c;\n     \
    \ if (t >= x)\n        t -= x;\n      uint64_t diff = (s >= t ? s - t : t - s);\n\
    \      value = mod_mul<bit32>(value, diff, x);\n      if (step % 127 == 0) {\n\
    \        uint64_t d = std::gcd(value, x);\n        if (d > 1)\n          return\
    \ d;\n      }\n    }\n    uint64_t d = std::gcd(value, x);\n    if (d > 1)\n \
    \     return d;\n  }\n  return x;\n}\n\n/**\n * @brief Pollard's Rho algorithm\
    \ to find a non-trivial factor of x\n * @tparam bit32 Whether to use 32-bit modular\
    \ multiplication\n * @param x The number to factorize\n * @return A non-trivial\
    \ factor of x\n */\ntemplate <bool bit32 = false> uint64_t pollard_rho(uint64_t\
    \ x) {\n  if (x % 2 == 0)\n    return 2;\n  static std::minstd_rand rng{};\n \
    \ return pollard_rho<bit32>(x, rng());\n}\n\n/**\n * @brief Factorize a number\
    \ into its prime factors\n * @tparam bit32 Whether to use 32-bit modular multiplication\n\
    \ * @param x The number to factorize\n * @return A vector of prime factors of\
    \ x\n */\ntemplate <bool bit32 = false> std::vector<uint64_t> factorize(uint64_t\
    \ x) {\n  std::vector<uint64_t> factors;\n  std::vector<std::pair<uint64_t, size_t>>\
    \ stk;\n  stk.emplace_back(x, 1);\n  while (!stk.empty()) {\n    auto [cur, cnt]\
    \ = stk.back();\n    stk.pop_back();\n    if (cur == 1)\n      continue;\n   \
    \ if (is_prime(cur)) {\n      factors.resize(factors.size() + cnt, cur);\n   \
    \   continue;\n    }\n    uint64_t factor = cur;\n    do\n      factor = pollard_rho<bit32>(cur);\n\
    \    while (factor == cur);\n    size_t factor_count = 0;\n    while (cur % factor\
    \ == 0)\n      cur /= factor, ++factor_count;\n    stk.emplace_back(cur, cnt);\n\
    \    stk.emplace_back(factor, factor_count * cnt);\n  }\n  std::sort(factors.begin(),\
    \ factors.end());\n  return factors;\n}\n\n/**\n * @brief Factorize a number into\
    \ its prime factors with fixed-size array\n * @tparam N The size of the output\
    \ array\n * @tparam bit32 Whether to use 32-bit modular multiplication\n * @param\
    \ x The number to factorize\n * @return An array of prime factors of x\n */\n\
    template <size_t N = 64, bool bit32 = false>\nconstexpr std::array<uint64_t, N>\
    \ factorize_fixed(uint64_t x) {\n  uint32_t random_state = 1;\n  size_t factor_idx\
    \ = 0, stk_idx = 0;\n  std::array<uint64_t, N> factors{};\n  std::array<uint64_t,\
    \ 64> stk_val{};\n  std::array<size_t, 64> stk_cnt{};\n  stk_val[stk_idx] = x,\
    \ stk_cnt[stk_idx++] = 1;\n  while (stk_idx > 0) {\n    uint64_t cur = stk_val[--stk_idx];\n\
    \    size_t cnt = stk_cnt[stk_idx];\n    if (cur == 1)\n      continue;\n    if\
    \ (is_prime(cur)) {\n      for (size_t i = 0; i < cnt; ++i)\n        factors[factor_idx++]\
    \ = cur;\n    } else {\n      uint64_t factor = cur;\n      do\n        factor\
    \ = pollard_rho<bit32>(cur, lcg_nr(random_state));\n      while (factor == cur);\n\
    \      size_t factor_count = 0;\n      while (cur % factor == 0)\n        cur\
    \ /= factor, ++factor_count;\n      stk_val[stk_idx] = cur, stk_cnt[stk_idx++]\
    \ = cnt;\n      stk_val[stk_idx] = factor, stk_cnt[stk_idx++] = factor_count *\
    \ cnt;\n    }\n  }\n  for (size_t i = 1; i < factor_idx; ++i) {\n    uint64_t\
    \ key = factors[i];\n    size_t j = i;\n    while (j > 0 && factors[j - 1] > key)\
    \ {\n      factors[j] = factors[j - 1];\n      --j;\n    }\n    factors[j] = key;\n\
    \  }\n  return factors;\n}\n} // namespace weilycoder\n\n\n#line 14 \"weilycoder/number_theory/primitive_root.hpp\"\
    \n\nnamespace weilycoder {\n/**\n * @brief Check if g is a primitive root modulo\
    \ p\n * @tparam N The size of the factors array\n * @tparam bit32 Whether to use\
    \ 32-bit modular multiplication\n * @param g The candidate primitive root\n *\
    \ @param p The prime modulus\n * @param factors The prime factors of p - 1\n *\
    \ @return true if g is a primitive root modulo p, false otherwise\n */\ntemplate\
    \ <size_t N = 64, bool bit32 = false>\nconstexpr bool is_primitive_root(uint64_t\
    \ g, uint64_t p,\n                                 const std::array<uint64_t,\
    \ N> &factors) {\n  for (size_t i = 0; i < N; ++i) {\n    uint64_t q = factors[i];\n\
    \    if (q == 0)\n      break;\n    if (mod_pow<bit32>(g, (p - 1) / q, p) == 1)\n\
    \      return false;\n  }\n  return true;\n}\n\n/**\n * @brief Check if g is a\
    \ primitive root modulo p\n * @tparam bit32 Whether to use 32-bit modular multiplication\n\
    \ * @param g The candidate primitive root\n * @param p The prime modulus\n * @param\
    \ factors The prime factors of p - 1\n * @return true if g is a primitive root\
    \ modulo p, false otherwise\n */\ntemplate <bool bit32 = false>\nbool is_primitive_root(uint64_t\
    \ g, uint64_t p, const std::vector<uint64_t> &factors) {\n  const size_t N = factors.size();\n\
    \  for (size_t i = 0; i < N; ++i) {\n    uint64_t q = factors[i];\n    if (q ==\
    \ 0)\n      break;\n    if (mod_pow<bit32>(g, (p - 1) / q, p) == 1)\n      return\
    \ false;\n  }\n  return true;\n}\n\n/**\n * @brief Find a primitive root modulo\
    \ a prime p\n * @tparam bit32 Whether to use 32-bit modular multiplication\n *\
    \ @param p The prime modulus\n * @return A primitive root modulo p, or 0 if p\
    \ is not prime\n */\ntemplate <bool bit32 = false, size_t N = 64>\nconstexpr uint64_t\
    \ prime_primitive_root(uint64_t p) {\n  if (p == 2)\n    return 1;\n  if (!is_prime(p))\n\
    \    return 0;\n  auto factors = factorize_fixed<N, bit32>(p - 1);\n  auto factors_set\
    \ = std::array<uint64_t, N>{};\n  size_t factor_count = 0;\n  for (size_t i =\
    \ 0; i < N; ++i) {\n    uint64_t q = factors[i];\n    if (q == 0)\n      break;\n\
    \    if (i == 0 || q != factors[i - 1])\n      factors_set[factor_count++] = q;\n\
    \  }\n  for (uint64_t g = 2; g < p; ++g)\n    if (is_primitive_root<N, bit32>(g,\
    \ p, factors_set))\n      return g;\n  return 0;\n}\n\n/**\n * @brief Find a primitive\
    \ root modulo a prime (compile-time version)\n * @tparam prime The prime modulus\n\
    \ * @return A primitive root modulo prime.\n */\ntemplate <uint64_t prime> constexpr\
    \ uint64_t prime_primitive_root() {\n  if constexpr (prime == 2)\n    return 1;\n\
    \  if (prime < UINT32_MAX)\n    return prime_primitive_root<true, 32>(prime);\n\
    \  return prime_primitive_root<false, 64>(prime);\n}\n} // namespace weilycoder\n\
    \n\n"
  code: "#ifndef WEILYCODER_NUMBER_THEORY_PRIMITIVE_ROOT_HPP\n#define WEILYCODER_NUMBER_THEORY_PRIMITIVE_ROOT_HPP\n\
    \n/**\n * @file primitive_root.hpp\n * @brief Functions to find primitive roots\
    \ modulo a prime\n */\n\n#include \"factorize.hpp\"\n#include \"mod_utility.hpp\"\
    \n#include <array>\n#include <cstdint>\n#include <vector>\n\nnamespace weilycoder\
    \ {\n/**\n * @brief Check if g is a primitive root modulo p\n * @tparam N The\
    \ size of the factors array\n * @tparam bit32 Whether to use 32-bit modular multiplication\n\
    \ * @param g The candidate primitive root\n * @param p The prime modulus\n * @param\
    \ factors The prime factors of p - 1\n * @return true if g is a primitive root\
    \ modulo p, false otherwise\n */\ntemplate <size_t N = 64, bool bit32 = false>\n\
    constexpr bool is_primitive_root(uint64_t g, uint64_t p,\n                   \
    \              const std::array<uint64_t, N> &factors) {\n  for (size_t i = 0;\
    \ i < N; ++i) {\n    uint64_t q = factors[i];\n    if (q == 0)\n      break;\n\
    \    if (mod_pow<bit32>(g, (p - 1) / q, p) == 1)\n      return false;\n  }\n \
    \ return true;\n}\n\n/**\n * @brief Check if g is a primitive root modulo p\n\
    \ * @tparam bit32 Whether to use 32-bit modular multiplication\n * @param g The\
    \ candidate primitive root\n * @param p The prime modulus\n * @param factors The\
    \ prime factors of p - 1\n * @return true if g is a primitive root modulo p, false\
    \ otherwise\n */\ntemplate <bool bit32 = false>\nbool is_primitive_root(uint64_t\
    \ g, uint64_t p, const std::vector<uint64_t> &factors) {\n  const size_t N = factors.size();\n\
    \  for (size_t i = 0; i < N; ++i) {\n    uint64_t q = factors[i];\n    if (q ==\
    \ 0)\n      break;\n    if (mod_pow<bit32>(g, (p - 1) / q, p) == 1)\n      return\
    \ false;\n  }\n  return true;\n}\n\n/**\n * @brief Find a primitive root modulo\
    \ a prime p\n * @tparam bit32 Whether to use 32-bit modular multiplication\n *\
    \ @param p The prime modulus\n * @return A primitive root modulo p, or 0 if p\
    \ is not prime\n */\ntemplate <bool bit32 = false, size_t N = 64>\nconstexpr uint64_t\
    \ prime_primitive_root(uint64_t p) {\n  if (p == 2)\n    return 1;\n  if (!is_prime(p))\n\
    \    return 0;\n  auto factors = factorize_fixed<N, bit32>(p - 1);\n  auto factors_set\
    \ = std::array<uint64_t, N>{};\n  size_t factor_count = 0;\n  for (size_t i =\
    \ 0; i < N; ++i) {\n    uint64_t q = factors[i];\n    if (q == 0)\n      break;\n\
    \    if (i == 0 || q != factors[i - 1])\n      factors_set[factor_count++] = q;\n\
    \  }\n  for (uint64_t g = 2; g < p; ++g)\n    if (is_primitive_root<N, bit32>(g,\
    \ p, factors_set))\n      return g;\n  return 0;\n}\n\n/**\n * @brief Find a primitive\
    \ root modulo a prime (compile-time version)\n * @tparam prime The prime modulus\n\
    \ * @return A primitive root modulo prime.\n */\ntemplate <uint64_t prime> constexpr\
    \ uint64_t prime_primitive_root() {\n  if constexpr (prime == 2)\n    return 1;\n\
    \  if (prime < UINT32_MAX)\n    return prime_primitive_root<true, 32>(prime);\n\
    \  return prime_primitive_root<false, 64>(prime);\n}\n} // namespace weilycoder\n\
    \n#endif\n"
  dependsOn:
  - weilycoder/number_theory/factorize.hpp
  - weilycoder/random.hpp
  - weilycoder/number_theory/mod_utility.hpp
  - weilycoder/number_theory/prime.hpp
  isVerificationFile: false
  path: weilycoder/number_theory/primitive_root.hpp
  requiredBy:
  - weilycoder/poly/mtt_convolve.hpp
  - weilycoder/poly/elementary_func/multiply.hpp
  - weilycoder/poly/elementary_func/inverse.hpp
  - weilycoder/poly/elementary_func/exponential.hpp
  - weilycoder/poly/elementary_func/logarithm.hpp
  - weilycoder/poly/ntt.hpp
  - weilycoder/poly/ntt_convolve.hpp
  timestamp: '2025-11-09 18:18:23+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/exp_of_formal_power_series.test.cpp
  - test/convolution_mod.test.cpp
  - test/log_of_formal_power_series.test.cpp
  - test/primitive_root.test.cpp
  - test/convolution_mod_1000000007.test.cpp
  - test/inv_of_formal_power_series.test.cpp
documentation_of: weilycoder/number_theory/primitive_root.hpp
layout: document
redirect_from:
- /library/weilycoder/number_theory/primitive_root.hpp
- /library/weilycoder/number_theory/primitive_root.hpp.html
title: Functions to find primitive roots modulo a prime
---
