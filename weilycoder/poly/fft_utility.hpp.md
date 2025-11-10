---
data:
  _extendedDependsOn: []
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
    path: weilycoder/poly/fft.hpp
    title: Fast Fourier Transform (FFT) implementation
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/fft_convolve.hpp
    title: Multiplying polynomials using Fast Fourier Transform (FFT)
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
    path: test/multiplication_of_big_integers.fft.test.cpp
    title: test/multiplication_of_big_integers.fft.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Utility functions and constants for Fast Fourier Transform (FFT)
    links: []
  bundledCode: "#line 1 \"weilycoder/poly/fft_utility.hpp\"\n\n\n\n#include <complex>\n\
    #include <cstddef>\n#include <vector>\n\n/**\n * @file fft_utility.hpp\n * @brief\
    \ Utility functions and constants for Fast Fourier Transform (FFT)\n */\n\nnamespace\
    \ weilycoder {\n/**\n * @brief Alias for the commonly used complex number type\
    \ with double precision.\n */\nusing complex_t = std::complex<double>;\n\n/**\n\
    \ * @brief Compile-time constant for \u03C0 (pi) parameterized by numeric type.\n\
    \ * @tparam T Numeric type (e.g., float, double, long double).\n */\ntemplate\
    \ <typename T> constexpr T PI = T(3.1415926535897932384626433832795l);\n\n/**\n\
    \ * @brief Perform in-place bit-reversal permutation (index reordering) required\
    \ by\n *        iterative FFT.\n * @tparam T Element type stored in the vector.\
    \ Must be Swappable and efficiently\n *         copyable.\n * @param a Vector\
    \ to be permuted in-place. Its size should typically be a power\n *          of\
    \ two for use with the FFT implementation in this file.\n */\ntemplate <typename\
    \ T> void fft_change(std::vector<T> &a) {\n  size_t n = a.size();\n  std::vector<size_t>\
    \ rev(n);\n  for (size_t i = 0; i < n; ++i) {\n    rev[i] = rev[i >> 1] >> 1;\n\
    \    if (i & 1)\n      rev[i] |= n >> 1;\n    if (i < rev[i])\n      std::swap(a[i],\
    \ a[rev[i]]);\n  }\n}\n} // namespace weilycoder\n\n\n"
  code: "#ifndef WEILYCODER_POLY_FFT_UTILITY_HPP\n#define WEILYCODER_POLY_FFT_UTILITY_HPP\n\
    \n#include <complex>\n#include <cstddef>\n#include <vector>\n\n/**\n * @file fft_utility.hpp\n\
    \ * @brief Utility functions and constants for Fast Fourier Transform (FFT)\n\
    \ */\n\nnamespace weilycoder {\n/**\n * @brief Alias for the commonly used complex\
    \ number type with double precision.\n */\nusing complex_t = std::complex<double>;\n\
    \n/**\n * @brief Compile-time constant for \u03C0 (pi) parameterized by numeric\
    \ type.\n * @tparam T Numeric type (e.g., float, double, long double).\n */\n\
    template <typename T> constexpr T PI = T(3.1415926535897932384626433832795l);\n\
    \n/**\n * @brief Perform in-place bit-reversal permutation (index reordering)\
    \ required by\n *        iterative FFT.\n * @tparam T Element type stored in the\
    \ vector. Must be Swappable and efficiently\n *         copyable.\n * @param a\
    \ Vector to be permuted in-place. Its size should typically be a power\n *   \
    \       of two for use with the FFT implementation in this file.\n */\ntemplate\
    \ <typename T> void fft_change(std::vector<T> &a) {\n  size_t n = a.size();\n\
    \  std::vector<size_t> rev(n);\n  for (size_t i = 0; i < n; ++i) {\n    rev[i]\
    \ = rev[i >> 1] >> 1;\n    if (i & 1)\n      rev[i] |= n >> 1;\n    if (i < rev[i])\n\
    \      std::swap(a[i], a[rev[i]]);\n  }\n}\n} // namespace weilycoder\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: weilycoder/poly/fft_utility.hpp
  requiredBy:
  - weilycoder/poly/fft_convolve.hpp
  - weilycoder/poly/mtt_convolve.hpp
  - weilycoder/poly/elementary_func/multiply.hpp
  - weilycoder/poly/elementary_func/inverse.hpp
  - weilycoder/poly/elementary_func/exponential.hpp
  - weilycoder/poly/elementary_func/logarithm.hpp
  - weilycoder/poly/ntt.hpp
  - weilycoder/poly/ntt_convolve.hpp
  - weilycoder/poly/fft.hpp
  timestamp: '2025-11-07 09:13:56+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/exp_of_formal_power_series.test.cpp
  - test/convolution_mod.test.cpp
  - test/log_of_formal_power_series.test.cpp
  - test/multiplication_of_big_integers.fft.test.cpp
  - test/convolution_mod_1000000007.test.cpp
  - test/inv_of_formal_power_series.test.cpp
documentation_of: weilycoder/poly/fft_utility.hpp
layout: document
redirect_from:
- /library/weilycoder/poly/fft_utility.hpp
- /library/weilycoder/poly/fft_utility.hpp.html
title: Utility functions and constants for Fast Fourier Transform (FFT)
---
