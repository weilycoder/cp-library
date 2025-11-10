---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: weilycoder/ds/treap.hpp
    title: Treap Data Structure
  - icon: ':heavy_check_mark:'
    path: weilycoder/number_theory/factorize.hpp
    title: Functions for factorizing numbers using Pollard's Rho algorithm
  - icon: ':heavy_check_mark:'
    path: weilycoder/number_theory/primitive_root.hpp
    title: Functions to find primitive roots modulo a prime
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
    path: test/factorize.test.cpp
    title: test/factorize.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/inv_of_formal_power_series.test.cpp
    title: test/inv_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/log_of_formal_power_series.test.cpp
    title: test/log_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/ordered_set.test.cpp
    title: test/ordered_set.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/primitive_root.test.cpp
    title: test/primitive_root.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Lightweight Compile-Time Pseudo-Random Number Generators
    links: []
  bundledCode: "#line 1 \"weilycoder/random.hpp\"\n\n\n\n/**\n * @file random.hpp\n\
    \ * @brief Lightweight Compile-Time Pseudo-Random Number Generators\n */\n\n#include\
    \ <cstdint>\n\nnamespace weilycoder {\n/**\n * @brief Linear Congruential Generator\
    \ (LCG) to produce pseudo-random numbers\n *        at compile-time.\n * @tparam\
    \ a The multiplier.\n * @tparam c The increment.\n * @tparam m The modulus.\n\
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
    }\n} // namespace weilycoder\n\n\n"
  code: "#ifndef WEILYCODER_CONST_RAND_HPP\n#define WEILYCODER_CONST_RAND_HPP\n\n\
    /**\n * @file random.hpp\n * @brief Lightweight Compile-Time Pseudo-Random Number\
    \ Generators\n */\n\n#include <cstdint>\n\nnamespace weilycoder {\n/**\n * @brief\
    \ Linear Congruential Generator (LCG) to produce pseudo-random numbers\n *   \
    \     at compile-time.\n * @tparam a The multiplier.\n * @tparam c The increment.\n\
    \ * @tparam m The modulus.\n * @param state The current state of the generator.\n\
    \ * @return The next state of the generator.\n */\ntemplate <uint32_t a, uint32_t\
    \ c, uint64_t m>\nconstexpr uint32_t &lcg_next(uint32_t &state) {\n  state = (static_cast<uint64_t>(a)\
    \ * state + c) % m;\n  return state;\n}\n\n/**\n * @brief LCG using parameters\
    \ from \"Minimal Standard\" by Park and Miller.\n * @param state The current state\
    \ of the generator.\n * @return The next state of the generator.\n */\nconstexpr\
    \ uint32_t &lcg_minstd(uint32_t &state) {\n  return lcg_next<48271, 0, 2147483647>(state);\n\
    }\n\n/**\n * @brief LCG using parameters from \"minstd_rand0\" by Park and Miller.\n\
    \ * @param state The current state of the generator.\n * @return The next state\
    \ of the generator.\n */\nconstexpr uint32_t &lcg_minstd_rand0(uint32_t &state)\
    \ {\n  return lcg_next<16807, 0, 2147483647>(state);\n}\n\n/**\n * @brief LCG\
    \ using parameters from \"Numerical Recipes\".\n * @param state The current state\
    \ of the generator.\n * @return The next state of the generator.\n */\nconstexpr\
    \ uint32_t &lcg_nr(uint32_t &state) {\n  return lcg_next<1103515245, 12345, 4294967296>(state);\n\
    }\n} // namespace weilycoder\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: weilycoder/random.hpp
  requiredBy:
  - weilycoder/ds/treap.hpp
  - weilycoder/poly/mtt_convolve.hpp
  - weilycoder/poly/elementary_func/multiply.hpp
  - weilycoder/poly/elementary_func/inverse.hpp
  - weilycoder/poly/elementary_func/exponential.hpp
  - weilycoder/poly/elementary_func/logarithm.hpp
  - weilycoder/poly/ntt.hpp
  - weilycoder/poly/ntt_convolve.hpp
  - weilycoder/number_theory/factorize.hpp
  - weilycoder/number_theory/primitive_root.hpp
  timestamp: '2025-11-09 18:18:23+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/exp_of_formal_power_series.test.cpp
  - test/convolution_mod.test.cpp
  - test/log_of_formal_power_series.test.cpp
  - test/primitive_root.test.cpp
  - test/convolution_mod_1000000007.test.cpp
  - test/ordered_set.test.cpp
  - test/inv_of_formal_power_series.test.cpp
  - test/factorize.test.cpp
documentation_of: weilycoder/random.hpp
layout: document
redirect_from:
- /library/weilycoder/random.hpp
- /library/weilycoder/random.hpp.html
title: Lightweight Compile-Time Pseudo-Random Number Generators
---
