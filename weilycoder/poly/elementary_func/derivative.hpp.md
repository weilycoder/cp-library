---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: weilycoder/number_theory/mod_utility.hpp
    title: Modular Arithmetic Utilities
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/elementary_func/exponential.hpp
    title: Polynomial Exponential Functions
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/elementary_func/logarithm.hpp
    title: Polynomial Logarithm Functions
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/exp_of_formal_power_series.test.cpp
    title: test/exp_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/log_of_formal_power_series.test.cpp
    title: test/log_of_formal_power_series.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Polynomial Derivative functions.
    links: []
  bundledCode: "#line 1 \"weilycoder/poly/elementary_func/derivative.hpp\"\n\n\n\n\
    /**\n * @file derivative.hpp\n * @brief Polynomial Derivative functions.\n */\n\
    \n#line 1 \"weilycoder/number_theory/mod_utility.hpp\"\n\n\n\n/**\n * @file mod_utility.hpp\n\
    \ * @brief Modular Arithmetic Utilities\n */\n\n#include <cstdint>\n\nnamespace\
    \ weilycoder {\nusing u128 = unsigned __int128;\n\n/**\n * @brief Perform modular\
    \ addition for 64-bit integers.\n * @tparam bit32 If true, won't use 128-bit arithmetic.\
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
    \ weilycoder\n\n\n#line 10 \"weilycoder/poly/elementary_func/derivative.hpp\"\n\
    #include <vector>\n\nnamespace weilycoder {\n/**\n * @brief Compute the derivative\
    \ of a polynomial.\n * @tparam T Coefficient type.\n * @tparam MultiplyFunc Type\
    \ of the multiplication function for coefficients.\n * @param poly Coefficients\
    \ of the polynomial.\n * @param number_mul Function to multiply a coefficient\
    \ by an integer.\n * @return Coefficients of the derivative polynomial.\n */\n\
    template <typename T, typename MultiplyFunc>\nstd::vector<T> derivative(const\
    \ std::vector<T> &poly, MultiplyFunc number_mul) {\n  if (poly.size() <= 1)\n\
    \    return {};\n  std::vector<T> res(poly.size() - 1);\n  for (size_t i = 1;\
    \ i < poly.size(); ++i)\n    res[i - 1] = number_mul(poly[i], T(i));\n  return\
    \ res;\n}\n\n/**\n * @brief Compute the derivative of a polynomial using modular\
    \ arithmetic.\n * @tparam mod Modulus for modular arithmetic.\n * @param poly\
    \ Coefficients of the polynomial.\n * @return Coefficients of the derivative polynomial.\n\
    \ */\ntemplate <uint64_t mod>\nstd::vector<uint64_t> ntt_poly_derivative(const\
    \ std::vector<uint64_t> &poly) {\n  return derivative<>(poly, mod_mul<mod>);\n\
    }\n} // namespace weilycoder\n\n\n"
  code: "#ifndef WEILYCODER_POLY_ELEMENTARY_FUNC_DERIVATIVE_HPP\n#define WEILYCODER_POLY_ELEMENTARY_FUNC_DERIVATIVE_HPP\n\
    \n/**\n * @file derivative.hpp\n * @brief Polynomial Derivative functions.\n */\n\
    \n#include \"../../number_theory/mod_utility.hpp\"\n#include <vector>\n\nnamespace\
    \ weilycoder {\n/**\n * @brief Compute the derivative of a polynomial.\n * @tparam\
    \ T Coefficient type.\n * @tparam MultiplyFunc Type of the multiplication function\
    \ for coefficients.\n * @param poly Coefficients of the polynomial.\n * @param\
    \ number_mul Function to multiply a coefficient by an integer.\n * @return Coefficients\
    \ of the derivative polynomial.\n */\ntemplate <typename T, typename MultiplyFunc>\n\
    std::vector<T> derivative(const std::vector<T> &poly, MultiplyFunc number_mul)\
    \ {\n  if (poly.size() <= 1)\n    return {};\n  std::vector<T> res(poly.size()\
    \ - 1);\n  for (size_t i = 1; i < poly.size(); ++i)\n    res[i - 1] = number_mul(poly[i],\
    \ T(i));\n  return res;\n}\n\n/**\n * @brief Compute the derivative of a polynomial\
    \ using modular arithmetic.\n * @tparam mod Modulus for modular arithmetic.\n\
    \ * @param poly Coefficients of the polynomial.\n * @return Coefficients of the\
    \ derivative polynomial.\n */\ntemplate <uint64_t mod>\nstd::vector<uint64_t>\
    \ ntt_poly_derivative(const std::vector<uint64_t> &poly) {\n  return derivative<>(poly,\
    \ mod_mul<mod>);\n}\n} // namespace weilycoder\n\n#endif\n"
  dependsOn:
  - weilycoder/number_theory/mod_utility.hpp
  isVerificationFile: false
  path: weilycoder/poly/elementary_func/derivative.hpp
  requiredBy:
  - weilycoder/poly/elementary_func/exponential.hpp
  - weilycoder/poly/elementary_func/logarithm.hpp
  timestamp: '2025-11-09 13:04:10+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/exp_of_formal_power_series.test.cpp
  - test/log_of_formal_power_series.test.cpp
documentation_of: weilycoder/poly/elementary_func/derivative.hpp
layout: document
redirect_from:
- /library/weilycoder/poly/elementary_func/derivative.hpp
- /library/weilycoder/poly/elementary_func/derivative.hpp.html
title: Polynomial Derivative functions.
---
