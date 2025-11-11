---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: weilycoder/number_theory/factorize.hpp
    title: Functions for factorizing numbers using Pollard's Rho algorithm
  - icon: ':heavy_check_mark:'
    path: weilycoder/number_theory/modint.hpp
    title: Modular Integer Class
  - icon: ':heavy_check_mark:'
    path: weilycoder/number_theory/prime.hpp
    title: Prime Number Utilities
  - icon: ':heavy_check_mark:'
    path: weilycoder/number_theory/primitive_root.hpp
    title: Functions to find primitive roots modulo a prime
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/elementary_func/derivative.hpp
    title: Polynomial Derivative functions.
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/elementary_func/exponential.hpp
    title: Polynomial Exponential Functions
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/elementary_func/exponential.hpp
    title: Polynomial Exponential Functions
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/elementary_func/exponential.hpp
    title: Polynomial Exponential Functions
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/elementary_func/integrate.hpp
    title: Polynomial Integration functions.
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/elementary_func/inverse.hpp
    title: Polynomial Inversion functions using Newton's method and NTT.
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/elementary_func/inverse.hpp
    title: Polynomial Inversion functions using Newton's method and NTT.
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/elementary_func/inverse.hpp
    title: Polynomial Inversion functions using Newton's method and NTT.
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/elementary_func/logarithm.hpp
    title: Polynomial Logarithm Functions
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/elementary_func/logarithm.hpp
    title: Polynomial Logarithm Functions
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/elementary_func/logarithm.hpp
    title: Polynomial Logarithm Functions
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/elementary_func/multiply.hpp
    title: Polynomial Multiplication Functions
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/elementary_func/multiply.hpp
    title: Polynomial Multiplication Functions
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/elementary_func/multiply.hpp
    title: Polynomial Multiplication Functions
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/mtt_convolve.hpp
    title: Multiply two polynomials under modulo using MTT with 3 NTT-friendly moduli.
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/mtt_convolve.hpp
    title: Multiply two polynomials under modulo using MTT with 3 NTT-friendly moduli.
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/ntt.hpp
    title: Number Theoretic Transform (NTT) implementation
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/ntt.hpp
    title: Number Theoretic Transform (NTT) implementation
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/ntt_convolve.hpp
    title: Multiplying polynomials using Number Theoretic Transform (NTT)
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/ntt_convolve.hpp
    title: Multiplying polynomials using Number Theoretic Transform (NTT)
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/convolution_mod.test.cpp
    title: test/convolution_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/convolution_mod.test.cpp
    title: test/convolution_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/convolution_mod_1000000007.test.cpp
    title: test/convolution_mod_1000000007.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/convolution_mod_1000000007.test.cpp
    title: test/convolution_mod_1000000007.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/exp_of_formal_power_series.test.cpp
    title: test/exp_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/exp_of_formal_power_series.test.cpp
    title: test/exp_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/exp_of_formal_power_series.test.cpp
    title: test/exp_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/factorize.test.cpp
    title: test/factorize.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/inv_of_formal_power_series.test.cpp
    title: test/inv_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/inv_of_formal_power_series.test.cpp
    title: test/inv_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/inv_of_formal_power_series.test.cpp
    title: test/inv_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/inv_of_formal_power_series.test.cpp
    title: test/inv_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/log_of_formal_power_series.test.cpp
    title: test/log_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/log_of_formal_power_series.test.cpp
    title: test/log_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/log_of_formal_power_series.test.cpp
    title: test/log_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/matrix_product.test.cpp
    title: test/matrix_product.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/primality_test.test.cpp
    title: test/primality_test.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/primitive_root.test.cpp
    title: test/primitive_root.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Modular Arithmetic Utilities
    links: []
  bundledCode: "#line 1 \"weilycoder/number_theory/mod_utility.hpp\"\n\n\n\n/**\n\
    \ * @file mod_utility.hpp\n * @brief Modular Arithmetic Utilities\n */\n\n#include\
    \ <cstdint>\n\nnamespace weilycoder {\nusing u128 = unsigned __int128;\n\n/**\n\
    \ * @brief Perform modular addition for 64-bit integers.\n * @tparam bit32 If\
    \ true, won't use 128-bit arithmetic. You should ensure that\n *         all inputs\
    \ are small enough to avoid overflow (i.e. bit-32).\n * @param a The first addend.\n\
    \ * @param b The second addend.\n * @param modulus The modulus.\n * @return (a\
    \ + b) % modulus\n */\ntemplate <bool bit32 = false>\nconstexpr uint64_t mod_add(uint64_t\
    \ a, uint64_t b, uint64_t modulus) {\n  if constexpr (bit32) {\n    uint64_t res\
    \ = a + b;\n    if (res >= modulus)\n      res -= modulus;\n    return res;\n\
    \  } else {\n    u128 res = static_cast<u128>(a) + b;\n    if (res >= modulus)\n\
    \      res -= modulus;\n    return res;\n  }\n}\n\n/**\n * @brief Perform modular\
    \ addition for 64-bit integers with a compile-time\n *        modulus.\n * @tparam\
    \ Modulus The modulus.\n * @param a The first addend.\n * @param b The second\
    \ addend.\n * @return (a + b) % Modulus\n */\ntemplate <uint64_t Modulus> constexpr\
    \ uint64_t mod_add(uint64_t a, uint64_t b) {\n  if constexpr (Modulus <= UINT32_MAX)\
    \ {\n    uint64_t res = a + b;\n    if (res >= Modulus)\n      res -= Modulus;\n\
    \    return res;\n  } else {\n    u128 res = static_cast<u128>(a) + b;\n    if\
    \ (res >= Modulus)\n      res -= Modulus;\n    return res;\n  }\n}\n\n/**\n *\
    \ @brief Perform modular subtraction for 64-bit integers.\n * @tparam bit32 If\
    \ true, won't use 128-bit arithmetic. You should ensure that\n *         all inputs\
    \ are small enough to avoid overflow (i.e. bit-32).\n * @param a The minuend.\n\
    \ * @param b The subtrahend.\n * @param modulus The modulus.\n * @return (a -\
    \ b) % modulus\n */\ntemplate <bool bit32 = false>\nconstexpr uint64_t mod_sub(uint64_t\
    \ a, uint64_t b, uint64_t modulus) {\n  if constexpr (bit32) {\n    uint64_t res\
    \ = (a >= b) ? (a - b) : (modulus + a - b);\n    return res;\n  } else {\n   \
    \ u128 res = (a >= b) ? (a - b) : (static_cast<u128>(modulus) + a - b);\n    return\
    \ res;\n  }\n}\n\n/**\n * @brief Perform modular subtraction for 64-bit integers\
    \ with a compile-time\n *        modulus.\n * @tparam Modulus The modulus.\n *\
    \ @param a The minuend.\n * @param b The subtrahend.\n * @return (a - b) % Modulus\n\
    \ */\ntemplate <uint64_t Modulus> constexpr uint64_t mod_sub(uint64_t a, uint64_t\
    \ b) {\n  if constexpr (Modulus <= UINT32_MAX) {\n    uint64_t res = (a >= b)\
    \ ? (a - b) : (Modulus + a - b);\n    return res;\n  } else {\n    u128 res =\
    \ (a >= b) ? (a - b) : (static_cast<u128>(Modulus) + a - b);\n    return res;\n\
    \  }\n}\n\n/**\n * @brief Perform modular multiplication for 64-bit integers.\n\
    \ * @tparam bit32 If true, won't use 128-bit arithmetic. You should ensure that\n\
    \ *         all inputs are small enough to avoid overflow (i.e. bit-32).\n * @param\
    \ a The first multiplicand.\n * @param b The second multiplicand.\n * @param modulus\
    \ The modulus.\n * @return (a * b) % modulus\n */\ntemplate <bool bit32 = false>\n\
    constexpr uint64_t mod_mul(uint64_t a, uint64_t b, uint64_t modulus) {\n  if constexpr\
    \ (bit32)\n    return a * b % modulus;\n  else\n    return static_cast<u128>(a)\
    \ * b % modulus;\n}\n\n/**\n * @brief Perform modular multiplication for 64-bit\
    \ integers with a compile-time\n *        modulus.\n * @tparam Modulus The modulus.\n\
    \ * @param a The first multiplicand.\n * @param b The second multiplicand.\n *\
    \ @return (a * b) % Modulus\n */\ntemplate <uint64_t Modulus> constexpr uint64_t\
    \ mod_mul(uint64_t a, uint64_t b) {\n  if constexpr (Modulus <= UINT32_MAX)\n\
    \    return a * b % Modulus;\n  else\n    return static_cast<u128>(a) * b % Modulus;\n\
    }\n\n/**\n * @brief Perform modular exponentiation for 64-bit integers.\n * @tparam\
    \ bit32 If true, won't use 128-bit arithmetic. You should ensure that\n *    \
    \     all inputs are small enough to avoid overflow (i.e. bit-32).\n * @param\
    \ base The base number.\n * @param exponent The exponent.\n * @param modulus The\
    \ modulus.\n * @return (base^exponent) % modulus\n */\ntemplate <bool bit32 =\
    \ false>\nconstexpr uint64_t mod_pow(uint64_t base, uint64_t exponent, uint64_t\
    \ modulus) {\n  uint64_t result = 1 % modulus;\n  base %= modulus;\n  while (exponent\
    \ > 0) {\n    if (exponent & 1)\n      result = mod_mul<bit32>(result, base, modulus);\n\
    \    base = mod_mul<bit32>(base, base, modulus);\n    exponent >>= 1;\n  }\n \
    \ return result;\n}\n\n/**\n * @brief Perform modular exponentiation for 64-bit\
    \ integers with a compile-time\n *        modulus.\n * @tparam Modulus The modulus.\n\
    \ * @param base The base number.\n * @param exponent The exponent.\n * @return\
    \ (base^exponent) % Modulus\n */\ntemplate <uint64_t Modulus>\nconstexpr uint64_t\
    \ mod_pow(uint64_t base, uint64_t exponent) {\n  uint64_t result = 1 % Modulus;\n\
    \  base %= Modulus;\n  while (exponent > 0) {\n    if (exponent & 1)\n      result\
    \ = mod_mul<Modulus>(result, base);\n    base = mod_mul<Modulus>(base, base);\n\
    \    exponent >>= 1;\n  }\n  return result;\n}\n\n/**\n * @brief Compute the modular\
    \ inverse of a 64-bit integer using Fermat's Little\n *        Theorem.\n * @tparam\
    \ Modulus The modulus (must be prime).\n * @param a The number to find the modular\
    \ inverse of.\n * @return The modular inverse of a modulo Modulus.\n */\ntemplate\
    \ <uint64_t Modulus> constexpr uint64_t mod_inv(uint64_t a) {\n  return mod_pow<Modulus>(a,\
    \ Modulus - 2);\n}\n\n/**\n * @brief Compute the modular inverse of a compile-time\
    \ 64-bit integer using\n *        Fermat's Little Theorem.\n * @tparam Modulus\
    \ The modulus (must be prime).\n * @tparam a The number to find the modular inverse\
    \ of.\n * @return The modular inverse of a modulo Modulus.\n */\ntemplate <uint64_t\
    \ Modulus, uint64_t a> constexpr uint64_t mod_inv() {\n  return mod_pow<Modulus>(a,\
    \ Modulus - 2);\n}\n} // namespace weilycoder\n\n\n"
  code: "#ifndef WEILYCODER_MOD_UTILITY_HPP\n#define WEILYCODER_MOD_UTILITY_HPP\n\n\
    /**\n * @file mod_utility.hpp\n * @brief Modular Arithmetic Utilities\n */\n\n\
    #include <cstdint>\n\nnamespace weilycoder {\nusing u128 = unsigned __int128;\n\
    \n/**\n * @brief Perform modular addition for 64-bit integers.\n * @tparam bit32\
    \ If true, won't use 128-bit arithmetic. You should ensure that\n *         all\
    \ inputs are small enough to avoid overflow (i.e. bit-32).\n * @param a The first\
    \ addend.\n * @param b The second addend.\n * @param modulus The modulus.\n *\
    \ @return (a + b) % modulus\n */\ntemplate <bool bit32 = false>\nconstexpr uint64_t\
    \ mod_add(uint64_t a, uint64_t b, uint64_t modulus) {\n  if constexpr (bit32)\
    \ {\n    uint64_t res = a + b;\n    if (res >= modulus)\n      res -= modulus;\n\
    \    return res;\n  } else {\n    u128 res = static_cast<u128>(a) + b;\n    if\
    \ (res >= modulus)\n      res -= modulus;\n    return res;\n  }\n}\n\n/**\n *\
    \ @brief Perform modular addition for 64-bit integers with a compile-time\n *\
    \        modulus.\n * @tparam Modulus The modulus.\n * @param a The first addend.\n\
    \ * @param b The second addend.\n * @return (a + b) % Modulus\n */\ntemplate <uint64_t\
    \ Modulus> constexpr uint64_t mod_add(uint64_t a, uint64_t b) {\n  if constexpr\
    \ (Modulus <= UINT32_MAX) {\n    uint64_t res = a + b;\n    if (res >= Modulus)\n\
    \      res -= Modulus;\n    return res;\n  } else {\n    u128 res = static_cast<u128>(a)\
    \ + b;\n    if (res >= Modulus)\n      res -= Modulus;\n    return res;\n  }\n\
    }\n\n/**\n * @brief Perform modular subtraction for 64-bit integers.\n * @tparam\
    \ bit32 If true, won't use 128-bit arithmetic. You should ensure that\n *    \
    \     all inputs are small enough to avoid overflow (i.e. bit-32).\n * @param\
    \ a The minuend.\n * @param b The subtrahend.\n * @param modulus The modulus.\n\
    \ * @return (a - b) % modulus\n */\ntemplate <bool bit32 = false>\nconstexpr uint64_t\
    \ mod_sub(uint64_t a, uint64_t b, uint64_t modulus) {\n  if constexpr (bit32)\
    \ {\n    uint64_t res = (a >= b) ? (a - b) : (modulus + a - b);\n    return res;\n\
    \  } else {\n    u128 res = (a >= b) ? (a - b) : (static_cast<u128>(modulus) +\
    \ a - b);\n    return res;\n  }\n}\n\n/**\n * @brief Perform modular subtraction\
    \ for 64-bit integers with a compile-time\n *        modulus.\n * @tparam Modulus\
    \ The modulus.\n * @param a The minuend.\n * @param b The subtrahend.\n * @return\
    \ (a - b) % Modulus\n */\ntemplate <uint64_t Modulus> constexpr uint64_t mod_sub(uint64_t\
    \ a, uint64_t b) {\n  if constexpr (Modulus <= UINT32_MAX) {\n    uint64_t res\
    \ = (a >= b) ? (a - b) : (Modulus + a - b);\n    return res;\n  } else {\n   \
    \ u128 res = (a >= b) ? (a - b) : (static_cast<u128>(Modulus) + a - b);\n    return\
    \ res;\n  }\n}\n\n/**\n * @brief Perform modular multiplication for 64-bit integers.\n\
    \ * @tparam bit32 If true, won't use 128-bit arithmetic. You should ensure that\n\
    \ *         all inputs are small enough to avoid overflow (i.e. bit-32).\n * @param\
    \ a The first multiplicand.\n * @param b The second multiplicand.\n * @param modulus\
    \ The modulus.\n * @return (a * b) % modulus\n */\ntemplate <bool bit32 = false>\n\
    constexpr uint64_t mod_mul(uint64_t a, uint64_t b, uint64_t modulus) {\n  if constexpr\
    \ (bit32)\n    return a * b % modulus;\n  else\n    return static_cast<u128>(a)\
    \ * b % modulus;\n}\n\n/**\n * @brief Perform modular multiplication for 64-bit\
    \ integers with a compile-time\n *        modulus.\n * @tparam Modulus The modulus.\n\
    \ * @param a The first multiplicand.\n * @param b The second multiplicand.\n *\
    \ @return (a * b) % Modulus\n */\ntemplate <uint64_t Modulus> constexpr uint64_t\
    \ mod_mul(uint64_t a, uint64_t b) {\n  if constexpr (Modulus <= UINT32_MAX)\n\
    \    return a * b % Modulus;\n  else\n    return static_cast<u128>(a) * b % Modulus;\n\
    }\n\n/**\n * @brief Perform modular exponentiation for 64-bit integers.\n * @tparam\
    \ bit32 If true, won't use 128-bit arithmetic. You should ensure that\n *    \
    \     all inputs are small enough to avoid overflow (i.e. bit-32).\n * @param\
    \ base The base number.\n * @param exponent The exponent.\n * @param modulus The\
    \ modulus.\n * @return (base^exponent) % modulus\n */\ntemplate <bool bit32 =\
    \ false>\nconstexpr uint64_t mod_pow(uint64_t base, uint64_t exponent, uint64_t\
    \ modulus) {\n  uint64_t result = 1 % modulus;\n  base %= modulus;\n  while (exponent\
    \ > 0) {\n    if (exponent & 1)\n      result = mod_mul<bit32>(result, base, modulus);\n\
    \    base = mod_mul<bit32>(base, base, modulus);\n    exponent >>= 1;\n  }\n \
    \ return result;\n}\n\n/**\n * @brief Perform modular exponentiation for 64-bit\
    \ integers with a compile-time\n *        modulus.\n * @tparam Modulus The modulus.\n\
    \ * @param base The base number.\n * @param exponent The exponent.\n * @return\
    \ (base^exponent) % Modulus\n */\ntemplate <uint64_t Modulus>\nconstexpr uint64_t\
    \ mod_pow(uint64_t base, uint64_t exponent) {\n  uint64_t result = 1 % Modulus;\n\
    \  base %= Modulus;\n  while (exponent > 0) {\n    if (exponent & 1)\n      result\
    \ = mod_mul<Modulus>(result, base);\n    base = mod_mul<Modulus>(base, base);\n\
    \    exponent >>= 1;\n  }\n  return result;\n}\n\n/**\n * @brief Compute the modular\
    \ inverse of a 64-bit integer using Fermat's Little\n *        Theorem.\n * @tparam\
    \ Modulus The modulus (must be prime).\n * @param a The number to find the modular\
    \ inverse of.\n * @return The modular inverse of a modulo Modulus.\n */\ntemplate\
    \ <uint64_t Modulus> constexpr uint64_t mod_inv(uint64_t a) {\n  return mod_pow<Modulus>(a,\
    \ Modulus - 2);\n}\n\n/**\n * @brief Compute the modular inverse of a compile-time\
    \ 64-bit integer using\n *        Fermat's Little Theorem.\n * @tparam Modulus\
    \ The modulus (must be prime).\n * @tparam a The number to find the modular inverse\
    \ of.\n * @return The modular inverse of a modulo Modulus.\n */\ntemplate <uint64_t\
    \ Modulus, uint64_t a> constexpr uint64_t mod_inv() {\n  return mod_pow<Modulus>(a,\
    \ Modulus - 2);\n}\n} // namespace weilycoder\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: weilycoder/number_theory/mod_utility.hpp
  requiredBy:
  - weilycoder/poly/mtt_convolve.hpp
  - weilycoder/poly/mtt_convolve.hpp
  - weilycoder/poly/elementary_func/multiply.hpp
  - weilycoder/poly/elementary_func/multiply.hpp
  - weilycoder/poly/elementary_func/multiply.hpp
  - weilycoder/poly/elementary_func/inverse.hpp
  - weilycoder/poly/elementary_func/inverse.hpp
  - weilycoder/poly/elementary_func/inverse.hpp
  - weilycoder/poly/elementary_func/exponential.hpp
  - weilycoder/poly/elementary_func/exponential.hpp
  - weilycoder/poly/elementary_func/exponential.hpp
  - weilycoder/poly/elementary_func/integrate.hpp
  - weilycoder/poly/elementary_func/derivative.hpp
  - weilycoder/poly/elementary_func/logarithm.hpp
  - weilycoder/poly/elementary_func/logarithm.hpp
  - weilycoder/poly/elementary_func/logarithm.hpp
  - weilycoder/poly/ntt.hpp
  - weilycoder/poly/ntt.hpp
  - weilycoder/poly/ntt_convolve.hpp
  - weilycoder/poly/ntt_convolve.hpp
  - weilycoder/number_theory/factorize.hpp
  - weilycoder/number_theory/primitive_root.hpp
  - weilycoder/number_theory/prime.hpp
  - weilycoder/number_theory/modint.hpp
  timestamp: '2025-11-08 07:03:41+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/primality_test.test.cpp
  - test/exp_of_formal_power_series.test.cpp
  - test/exp_of_formal_power_series.test.cpp
  - test/exp_of_formal_power_series.test.cpp
  - test/convolution_mod.test.cpp
  - test/convolution_mod.test.cpp
  - test/log_of_formal_power_series.test.cpp
  - test/log_of_formal_power_series.test.cpp
  - test/log_of_formal_power_series.test.cpp
  - test/primitive_root.test.cpp
  - test/convolution_mod_1000000007.test.cpp
  - test/convolution_mod_1000000007.test.cpp
  - test/inv_of_formal_power_series.test.cpp
  - test/inv_of_formal_power_series.test.cpp
  - test/inv_of_formal_power_series.test.cpp
  - test/inv_of_formal_power_series.test.cpp
  - test/matrix_product.test.cpp
  - test/factorize.test.cpp
documentation_of: weilycoder/number_theory/mod_utility.hpp
layout: document
redirect_from:
- /library/weilycoder/number_theory/mod_utility.hpp
- /library/weilycoder/number_theory/mod_utility.hpp.html
title: Modular Arithmetic Utilities
---
