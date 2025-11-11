---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: weilycoder/number_theory/mod_utility.hpp
    title: Modular Arithmetic Utilities
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/matrix_product.test.cpp
    title: test/matrix_product.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Modular Integer Class
    links: []
  bundledCode: "#line 1 \"weilycoder/number_theory/modint.hpp\"\n\n\n\n/**\n * @file\
    \ modint.hpp\n * @brief Modular Integer Class\n */\n\n#line 1 \"weilycoder/number_theory/mod_utility.hpp\"\
    \n\n\n\n/**\n * @file mod_utility.hpp\n * @brief Modular Arithmetic Utilities\n\
    \ */\n\n#include <cstdint>\n\nnamespace weilycoder {\nusing u128 = unsigned __int128;\n\
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
    \ Modulus - 2);\n}\n} // namespace weilycoder\n\n\n#line 11 \"weilycoder/number_theory/modint.hpp\"\
    \n#include <istream>\n#include <ostream>\n\nnamespace weilycoder {\n/**\n * @brief\
    \ Modular Integer with compile-time modulus.\n * @tparam Modulus The modulus.\n\
    \ */\ntemplate <uint64_t Modulus> struct modint {\nprivate:\n  uint64_t value;\n\
    \npublic:\n  constexpr modint() : value(0) {}\n  constexpr modint(uint32_t v)\
    \ : value(v % Modulus) {}\n  constexpr modint(int32_t v) { from_i64(v); }\n  constexpr\
    \ modint(uint64_t v) : value(v % Modulus) {}\n  constexpr modint(int64_t v) {\
    \ from_i64(v); }\n\n  constexpr void from_i64(int64_t v) {\n    int64_t x = v\
    \ % static_cast<int64_t>(Modulus);\n    if (x < 0)\n      x += Modulus;\n    value\
    \ = static_cast<uint64_t>(x);\n  }\n\n  explicit operator uint64_t() const { return\
    \ value; }\n\n  friend constexpr modint<Modulus> operator+(const modint<Modulus>\
    \ &lhs,\n                                             const modint<Modulus> &rhs)\
    \ {\n    return modint<Modulus>(mod_add<Modulus>(lhs.value, rhs.value));\n  }\n\
    \n  friend constexpr modint<Modulus> operator-(const modint<Modulus> &lhs,\n \
    \                                            const modint<Modulus> &rhs) {\n \
    \   return modint<Modulus>(mod_sub<Modulus>(lhs.value, rhs.value));\n  }\n\n \
    \ friend constexpr modint<Modulus> operator*(const modint<Modulus> &lhs,\n   \
    \                                          const modint<Modulus> &rhs) {\n   \
    \ return modint<Modulus>(mod_mul<Modulus>(lhs.value, rhs.value));\n  }\n\n  modint\
    \ &operator+=(const modint &other) {\n    value = mod_add<Modulus>(value, other.value);\n\
    \    return *this;\n  }\n\n  modint &operator-=(const modint &other) {\n    value\
    \ = mod_sub<Modulus>(value, other.value);\n    return *this;\n  }\n\n  modint\
    \ &operator*=(const modint &other) {\n    value = mod_mul<Modulus>(value, other.value);\n\
    \    return *this;\n  }\n\n  friend std::ostream &operator<<(std::ostream &os,\
    \ const modint &m) {\n    return os << m.value;\n  }\n\n  friend std::istream\
    \ &operator>>(std::istream &is, modint &m) {\n    int64_t v;\n    is >> v;\n \
    \   m.from_i64(v);\n    return is;\n  }\n};\n} // namespace weilycoder\n\n\n"
  code: "#ifndef WEILYCODER_MODINT_HPP\n#define WEILYCODER_MODINT_HPP\n\n/**\n * @file\
    \ modint.hpp\n * @brief Modular Integer Class\n */\n\n#include \"mod_utility.hpp\"\
    \n#include <cstdint>\n#include <istream>\n#include <ostream>\n\nnamespace weilycoder\
    \ {\n/**\n * @brief Modular Integer with compile-time modulus.\n * @tparam Modulus\
    \ The modulus.\n */\ntemplate <uint64_t Modulus> struct modint {\nprivate:\n \
    \ uint64_t value;\n\npublic:\n  constexpr modint() : value(0) {}\n  constexpr\
    \ modint(uint32_t v) : value(v % Modulus) {}\n  constexpr modint(int32_t v) {\
    \ from_i64(v); }\n  constexpr modint(uint64_t v) : value(v % Modulus) {}\n  constexpr\
    \ modint(int64_t v) { from_i64(v); }\n\n  constexpr void from_i64(int64_t v) {\n\
    \    int64_t x = v % static_cast<int64_t>(Modulus);\n    if (x < 0)\n      x +=\
    \ Modulus;\n    value = static_cast<uint64_t>(x);\n  }\n\n  explicit operator\
    \ uint64_t() const { return value; }\n\n  friend constexpr modint<Modulus> operator+(const\
    \ modint<Modulus> &lhs,\n                                             const modint<Modulus>\
    \ &rhs) {\n    return modint<Modulus>(mod_add<Modulus>(lhs.value, rhs.value));\n\
    \  }\n\n  friend constexpr modint<Modulus> operator-(const modint<Modulus> &lhs,\n\
    \                                             const modint<Modulus> &rhs) {\n\
    \    return modint<Modulus>(mod_sub<Modulus>(lhs.value, rhs.value));\n  }\n\n\
    \  friend constexpr modint<Modulus> operator*(const modint<Modulus> &lhs,\n  \
    \                                           const modint<Modulus> &rhs) {\n  \
    \  return modint<Modulus>(mod_mul<Modulus>(lhs.value, rhs.value));\n  }\n\n  modint\
    \ &operator+=(const modint &other) {\n    value = mod_add<Modulus>(value, other.value);\n\
    \    return *this;\n  }\n\n  modint &operator-=(const modint &other) {\n    value\
    \ = mod_sub<Modulus>(value, other.value);\n    return *this;\n  }\n\n  modint\
    \ &operator*=(const modint &other) {\n    value = mod_mul<Modulus>(value, other.value);\n\
    \    return *this;\n  }\n\n  friend std::ostream &operator<<(std::ostream &os,\
    \ const modint &m) {\n    return os << m.value;\n  }\n\n  friend std::istream\
    \ &operator>>(std::istream &is, modint &m) {\n    int64_t v;\n    is >> v;\n \
    \   m.from_i64(v);\n    return is;\n  }\n};\n} // namespace weilycoder\n\n#endif\n"
  dependsOn:
  - weilycoder/number_theory/mod_utility.hpp
  isVerificationFile: false
  path: weilycoder/number_theory/modint.hpp
  requiredBy: []
  timestamp: '2025-11-11 19:23:37+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/matrix_product.test.cpp
documentation_of: weilycoder/number_theory/modint.hpp
layout: document
redirect_from:
- /library/weilycoder/number_theory/modint.hpp
- /library/weilycoder/number_theory/modint.hpp.html
title: Modular Integer Class
---
