---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: weilycoder/number-theory/modint.hpp
    title: Modular Integer Arithmetic Utilities
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/primality_test.test.cpp
    title: test/primality_test.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Prime Number Utilities
    links: []
  bundledCode: "#line 1 \"weilycoder/number-theory/prime.hpp\"\n\n\n\n/**\n * @file\
    \ prime.hpp\n * @brief Prime Number Utilities\n */\n\n#line 1 \"weilycoder/number-theory/modint.hpp\"\
    \n\n\n\n/**\n * @file modint.hpp\n * @brief Modular Integer Arithmetic Utilities\n\
    \ */\n\n#include <cstdint>\n\nnamespace weilycoder {\n/**\n * @brief Perform modular\
    \ multiplication for 64-bit integers.\n * @tparam bit32 If true, won't use 128-bit\
    \ arithmetic. You should ensure that\n *         all inputs are small enough to\
    \ avoid overflow (i.e. bit-32).\n * @param a The first multiplicand.\n * @param\
    \ b The second multiplicand.\n * @param modulus The modulus.\n * @return (a *\
    \ b) % modulus\n */\ntemplate <bool bit32 = false>\nuint64_t modular_multiply_64(uint64_t\
    \ a, uint64_t b, uint64_t modulus) {\n  if constexpr (bit32)\n    return a * b\
    \ % modulus;\n  else\n    return static_cast<unsigned __int128>(a) * b % modulus;\n\
    }\n\n/**\n * @brief Perform modular exponentiation for 64-bit integers.\n * @tparam\
    \ bit32 If true, won't use 128-bit arithmetic. You should ensure that\n *    \
    \     all inputs are small enough to avoid overflow (i.e. bit-32).\n * @param\
    \ base The base number.\n * @param exponent The exponent.\n * @param modulus The\
    \ modulus.\n * @return (base^exponent) % modulus\n */\ntemplate <bool bit32 =\
    \ false>\nconstexpr uint64_t fast_power_64(uint64_t base, uint64_t exponent, uint64_t\
    \ modulus) {\n  uint64_t result = 1 % modulus;\n  base %= modulus;\n  while (exponent\
    \ > 0) {\n    if (exponent & 1)\n      result = modular_multiply_64<bit32>(result,\
    \ base, modulus);\n    base = modular_multiply_64<bit32>(base, base, modulus);\n\
    \    exponent >>= 1;\n  }\n  return result;\n}\n} // namespace weilycoder\n\n\n\
    #line 11 \"weilycoder/number-theory/prime.hpp\"\n#include <type_traits>\n\nnamespace\
    \ weilycoder {\n/**\n * @brief Miller-Rabin primality test for a given base.\n\
    \ * @tparam bit32 If true, won't use 128-bit arithmetic. You should ensure that\n\
    \ *         all inputs are small enough to avoid overflow (i.e. bit-32).\n * @tparam\
    \ base The base to test.\n * @param n The number to test for primality.\n * @param\
    \ d An odd component of n-1 (n-1 = d * 2^s).\n * @param s The exponent of 2 in\
    \ the factorization of n-1.\n * @return true if n is probably prime for the given\
    \ base, false if composite.\n */\ntemplate <bool bit32, uint64_t base>\nconstexpr\
    \ bool miller_rabin_test(uint64_t n, uint64_t d, uint32_t s) {\n  uint64_t x =\
    \ fast_power_64<bit32>(base, d, n);\n  if (x == 0 || x == 1 || x == n - 1)\n \
    \   return true;\n  for (uint32_t r = 1; r < s; ++r) {\n    x = modular_multiply_64<bit32>(x,\
    \ x, n);\n    if (x == n - 1)\n      return true;\n  }\n  return false;\n}\n\n\
    /**\n * @brief Variadic template to test multiple bases in Miller-Rabin test.\n\
    \ * @tparam bit32 If true, won't use 128-bit arithmetic. You should ensure that\n\
    \ *         all inputs are small enough to avoid overflow (i.e. bit-32).\n * @tparam\
    \ base The first base to test.\n * @tparam Rest The remaining bases to test.\n\
    \ * @param n The number to test for primality.\n * @param d An odd component of\
    \ n-1 (n-1 = d * 2^s).\n * @param s The exponent of 2 in the factorization of\
    \ n-1.\n * @return true if n is probably prime for all given bases, false if composite.\n\
    \ */\ntemplate <bool bit32, uint64_t base, uint64_t... Rest>\nconstexpr std::enable_if_t<(sizeof...(Rest)\
    \ != 0), bool>\nmiller_rabin_test(uint64_t n, uint64_t d, uint32_t s) {\n  return\
    \ miller_rabin_test<bit32, base>(n, d, s) &&\n         miller_rabin_test<bit32,\
    \ Rest...>(n, d, s);\n}\n\n/**\n * @brief Miller-Rabin primality test using multiple\
    \ bases.\n * @tparam bit32 If true, won't use 128-bit arithmetic. You should ensure\
    \ that\n *         all inputs are small enough to avoid overflow (i.e. bit-32).\n\
    \ * @tparam bases The bases to test.\n * @param n The number to test for primality.\n\
    \ * @return true if n is probably prime, false if composite.\n */\ntemplate <bool\
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
    \ n) { return miller_rabin<true, 2, 7, 61>(n); }\n} // namespace weilycoder\n\n\
    \n"
  code: "#ifndef WEILYCODER_PRIME_HPP\n#define WEILYCODER_PRIME_HPP\n\n/**\n * @file\
    \ prime.hpp\n * @brief Prime Number Utilities\n */\n\n#include \"modint.hpp\"\n\
    #include <cstdint>\n#include <type_traits>\n\nnamespace weilycoder {\n/**\n *\
    \ @brief Miller-Rabin primality test for a given base.\n * @tparam bit32 If true,\
    \ won't use 128-bit arithmetic. You should ensure that\n *         all inputs\
    \ are small enough to avoid overflow (i.e. bit-32).\n * @tparam base The base\
    \ to test.\n * @param n The number to test for primality.\n * @param d An odd\
    \ component of n-1 (n-1 = d * 2^s).\n * @param s The exponent of 2 in the factorization\
    \ of n-1.\n * @return true if n is probably prime for the given base, false if\
    \ composite.\n */\ntemplate <bool bit32, uint64_t base>\nconstexpr bool miller_rabin_test(uint64_t\
    \ n, uint64_t d, uint32_t s) {\n  uint64_t x = fast_power_64<bit32>(base, d, n);\n\
    \  if (x == 0 || x == 1 || x == n - 1)\n    return true;\n  for (uint32_t r =\
    \ 1; r < s; ++r) {\n    x = modular_multiply_64<bit32>(x, x, n);\n    if (x ==\
    \ n - 1)\n      return true;\n  }\n  return false;\n}\n\n/**\n * @brief Variadic\
    \ template to test multiple bases in Miller-Rabin test.\n * @tparam bit32 If true,\
    \ won't use 128-bit arithmetic. You should ensure that\n *         all inputs\
    \ are small enough to avoid overflow (i.e. bit-32).\n * @tparam base The first\
    \ base to test.\n * @tparam Rest The remaining bases to test.\n * @param n The\
    \ number to test for primality.\n * @param d An odd component of n-1 (n-1 = d\
    \ * 2^s).\n * @param s The exponent of 2 in the factorization of n-1.\n * @return\
    \ true if n is probably prime for all given bases, false if composite.\n */\n\
    template <bool bit32, uint64_t base, uint64_t... Rest>\nconstexpr std::enable_if_t<(sizeof...(Rest)\
    \ != 0), bool>\nmiller_rabin_test(uint64_t n, uint64_t d, uint32_t s) {\n  return\
    \ miller_rabin_test<bit32, base>(n, d, s) &&\n         miller_rabin_test<bit32,\
    \ Rest...>(n, d, s);\n}\n\n/**\n * @brief Miller-Rabin primality test using multiple\
    \ bases.\n * @tparam bit32 If true, won't use 128-bit arithmetic. You should ensure\
    \ that\n *         all inputs are small enough to avoid overflow (i.e. bit-32).\n\
    \ * @tparam bases The bases to test.\n * @param n The number to test for primality.\n\
    \ * @return true if n is probably prime, false if composite.\n */\ntemplate <bool\
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
    \ n) { return miller_rabin<true, 2, 7, 61>(n); }\n} // namespace weilycoder\n\n\
    #endif\n"
  dependsOn:
  - weilycoder/number-theory/modint.hpp
  isVerificationFile: false
  path: weilycoder/number-theory/prime.hpp
  requiredBy: []
  timestamp: '2025-11-01 13:01:38+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/primality_test.test.cpp
documentation_of: weilycoder/number-theory/prime.hpp
layout: document
redirect_from:
- /library/weilycoder/number-theory/prime.hpp
- /library/weilycoder/number-theory/prime.hpp.html
title: Prime Number Utilities
---
