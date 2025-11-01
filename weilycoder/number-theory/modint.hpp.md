---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: weilycoder/number-theory/prime.hpp
    title: Prime Number Utilities
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/primality_test.test.cpp
    title: test/primality_test.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Modular Integer Arithmetic Utilities
    links: []
  bundledCode: "#line 1 \"weilycoder/number-theory/modint.hpp\"\n\n\n\n/**\n * @file\
    \ modint.hpp\n * @brief Modular Integer Arithmetic Utilities\n */\n\n#include\
    \ <cstdint>\n\nnamespace weilycoder {\n/**\n * @brief Perform modular multiplication\
    \ for 64-bit integers.\n * @tparam bit32 If true, won't use 128-bit arithmetic.\
    \ You should ensure that\n *         all inputs are small enough to avoid overflow\
    \ (i.e. bit-32).\n * @param a The first multiplicand.\n * @param b The second\
    \ multiplicand.\n * @param modulus The modulus.\n * @return (a * b) % modulus\n\
    \ */\ntemplate <bool bit32 = false>\nuint64_t modular_multiply_64(uint64_t a,\
    \ uint64_t b, uint64_t modulus) {\n  if constexpr (bit32)\n    return a * b %\
    \ modulus;\n  else\n    return static_cast<unsigned __int128>(a) * b % modulus;\n\
    }\n\n/**\n * @brief Perform modular exponentiation for 64-bit integers.\n * @tparam\
    \ bit32 If true, won't use 128-bit arithmetic. You should ensure that\n *    \
    \     all inputs are small enough to avoid overflow (i.e. bit-32).\n * @param\
    \ base The base number.\n * @param exponent The exponent.\n * @param modulus The\
    \ modulus.\n * @return (base^exponent) % modulus\n */\ntemplate <bool bit32 =\
    \ false>\nconstexpr uint64_t fast_power_64(uint64_t base, uint64_t exponent, uint64_t\
    \ modulus) {\n  uint64_t result = 1 % modulus;\n  base %= modulus;\n  while (exponent\
    \ > 0) {\n    if (exponent & 1)\n      result = modular_multiply_64<bit32>(result,\
    \ base, modulus);\n    base = modular_multiply_64<bit32>(base, base, modulus);\n\
    \    exponent >>= 1;\n  }\n  return result;\n}\n} // namespace weilycoder\n\n\n"
  code: "#ifndef WEILYCODER_MODINT_HPP\n#define WEILYCODER_MODINT_HPP\n\n/**\n * @file\
    \ modint.hpp\n * @brief Modular Integer Arithmetic Utilities\n */\n\n#include\
    \ <cstdint>\n\nnamespace weilycoder {\n/**\n * @brief Perform modular multiplication\
    \ for 64-bit integers.\n * @tparam bit32 If true, won't use 128-bit arithmetic.\
    \ You should ensure that\n *         all inputs are small enough to avoid overflow\
    \ (i.e. bit-32).\n * @param a The first multiplicand.\n * @param b The second\
    \ multiplicand.\n * @param modulus The modulus.\n * @return (a * b) % modulus\n\
    \ */\ntemplate <bool bit32 = false>\nuint64_t modular_multiply_64(uint64_t a,\
    \ uint64_t b, uint64_t modulus) {\n  if constexpr (bit32)\n    return a * b %\
    \ modulus;\n  else\n    return static_cast<unsigned __int128>(a) * b % modulus;\n\
    }\n\n/**\n * @brief Perform modular exponentiation for 64-bit integers.\n * @tparam\
    \ bit32 If true, won't use 128-bit arithmetic. You should ensure that\n *    \
    \     all inputs are small enough to avoid overflow (i.e. bit-32).\n * @param\
    \ base The base number.\n * @param exponent The exponent.\n * @param modulus The\
    \ modulus.\n * @return (base^exponent) % modulus\n */\ntemplate <bool bit32 =\
    \ false>\nconstexpr uint64_t fast_power_64(uint64_t base, uint64_t exponent, uint64_t\
    \ modulus) {\n  uint64_t result = 1 % modulus;\n  base %= modulus;\n  while (exponent\
    \ > 0) {\n    if (exponent & 1)\n      result = modular_multiply_64<bit32>(result,\
    \ base, modulus);\n    base = modular_multiply_64<bit32>(base, base, modulus);\n\
    \    exponent >>= 1;\n  }\n  return result;\n}\n} // namespace weilycoder\n\n\
    #endif\n"
  dependsOn: []
  isVerificationFile: false
  path: weilycoder/number-theory/modint.hpp
  requiredBy:
  - weilycoder/number-theory/prime.hpp
  timestamp: '2025-11-01 07:16:21+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/primality_test.test.cpp
documentation_of: weilycoder/number-theory/modint.hpp
layout: document
redirect_from:
- /library/weilycoder/number-theory/modint.hpp
- /library/weilycoder/number-theory/modint.hpp.html
title: Modular Integer Arithmetic Utilities
---
