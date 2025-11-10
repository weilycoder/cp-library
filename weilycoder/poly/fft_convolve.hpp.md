---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/fft.hpp
    title: Fast Fourier Transform (FFT) implementation
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/fft_utility.hpp
    title: Utility functions and constants for Fast Fourier Transform (FFT)
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/multiplication_of_big_integers.fft.test.cpp
    title: test/multiplication_of_big_integers.fft.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Multiplying polynomials using Fast Fourier Transform (FFT)
    links: []
  bundledCode: "#line 1 \"weilycoder/poly/fft_convolve.hpp\"\n\n\n\n#line 1 \"weilycoder/poly/fft.hpp\"\
    \n\n\n\n#line 1 \"weilycoder/poly/fft_utility.hpp\"\n\n\n\n#include <complex>\n\
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
    \ a[rev[i]]);\n  }\n}\n} // namespace weilycoder\n\n\n#line 7 \"weilycoder/poly/fft.hpp\"\
    \n#include <stdexcept>\n#line 9 \"weilycoder/poly/fft.hpp\"\n\n/**\n * @file fft.hpp\n\
    \ * @brief Fast Fourier Transform (FFT) implementation\n */\n\nnamespace weilycoder\
    \ {\n/**\n * @brief In-place iterative Cooley\u2013Tukey FFT / inverse FFT on\
    \ a complex vector.\n *        The length of the input vector should be a power\
    \ of two.\n * @tparam on Direction of the transform: 1 for FFT, -1 for inverse\
    \ FFT.\n * @tparam float_t Floating-point type for computations (default: double).\n\
    \ * @param y Vector of complex numbers to be transformed in-place.\n */\ntemplate\
    \ <int32_t on = 1, typename float_t = double>\nvoid fft(std::vector<std::complex<float_t>>\
    \ &y) {\n  static_assert(on == 1 || on == -1, \"on must be 1 or -1\");\n  fft_change(y);\n\
    \  size_t len = y.size();\n  if (len == 0 || (len & (len - 1)) != 0)\n    throw\
    \ std::invalid_argument(\"Length of input vector must be a power of two\");\n\
    \  for (size_t h = 2; h <= len; h <<= 1) {\n    std::complex<float_t> wn(cos(2\
    \ * PI<float_t> / h), sin(on * 2 * PI<float_t> / h));\n    for (size_t j = 0;\
    \ j < len; j += h) {\n      std::complex<float_t> w(1, 0);\n      for (size_t\
    \ k = j; k < j + (h >> 1); ++k, w *= wn) {\n        std::complex<float_t> u =\
    \ y[k], t = w * y[k + (h >> 1)];\n        y[k] = u + t, y[k + (h >> 1)] = u -\
    \ t;\n      }\n    }\n  }\n  if constexpr (on == -1)\n    for (size_t i = 0; i\
    \ < len; ++i)\n      y[i] /= len;\n}\n} // namespace weilycoder\n\n\n#line 8 \"\
    weilycoder/poly/fft_convolve.hpp\"\n\n/**\n * @file fft_convolve.hpp\n * @brief\
    \ Multiplying polynomials using Fast Fourier Transform (FFT)\n */\n\nnamespace\
    \ weilycoder {\n/**\n * @brief Perform convolution of two complex vectors using\
    \ FFT.\n * @tparam float_t Floating-point type for computations (default: double).\n\
    \ * @param a First input vector of complex numbers.\n * @param b Second input\
    \ vector of complex numbers.\n * @return Vector containing the convolution result.\n\
    \ */\ntemplate <typename float_t = double>\nstd::vector<std::complex<float_t>>\
    \ fft_convolve(std::vector<std::complex<float_t>> a,\n                       \
    \                         std::vector<std::complex<float_t>> b) {\n  if (a.empty()\
    \ || b.empty())\n    return {};\n  size_t n = 1, target = a.size() + b.size()\
    \ - 1;\n  while (n < target)\n    n <<= 1;\n  a.resize(n), b.resize(n);\n  fft(a),\
    \ fft(b);\n  for (size_t i = 0; i < n; ++i)\n    a[i] *= b[i];\n  fft<-1>(a),\
    \ a.resize(target);\n  return a;\n}\n\n/**\n * @brief Perform convolution of two\
    \ real-valued vectors using FFT.\n * @tparam float_t Floating-point type for computations\
    \ (default: double).\n * @param a First input vector of real numbers.\n * @param\
    \ b Second input vector of real numbers.\n * @return Vector containing the convolution\
    \ result.\n * @note This function uses a technique that combines two real sequences\
    \ into\n *       a single complex sequence to perform the convolution more efficiently.\n\
    \ */\ntemplate <typename float_t = double>\nstd::vector<float_t> fft_convolve_real(const\
    \ std::vector<float_t> &a,\n                                       const std::vector<float_t>\
    \ &b) {\n  size_t n = 1;\n  while (n < a.size() + b.size() - 1)\n    n <<= 1;\n\
    \  std::vector<std::complex<float_t>> F(n);\n  for (size_t i = 0; i < a.size();\
    \ ++i)\n    F[i].real(a[i]);\n  for (size_t i = 0; i < b.size(); ++i)\n    F[i].imag(b[i]);\n\
    \  fft(F);\n  for (size_t i = 0; i < n; ++i)\n    F[i] *= F[i];\n  fft<-1>(F);\n\
    \  std::vector<float_t> result(a.size() + b.size() - 1);\n  for (size_t i = 0;\
    \ i < result.size(); ++i)\n    result[i] = F[i].imag() / 2;\n  return result;\n\
    }\n} // namespace weilycoder\n\n\n"
  code: "#ifndef WEILYCODER_POLY_FFT_CONVOLVE_HPP\n#define WEILYCODER_POLY_FFT_CONVOLVE_HPP\n\
    \n#include \"fft.hpp\"\n#include <complex>\n#include <cstddef>\n#include <vector>\n\
    \n/**\n * @file fft_convolve.hpp\n * @brief Multiplying polynomials using Fast\
    \ Fourier Transform (FFT)\n */\n\nnamespace weilycoder {\n/**\n * @brief Perform\
    \ convolution of two complex vectors using FFT.\n * @tparam float_t Floating-point\
    \ type for computations (default: double).\n * @param a First input vector of\
    \ complex numbers.\n * @param b Second input vector of complex numbers.\n * @return\
    \ Vector containing the convolution result.\n */\ntemplate <typename float_t =\
    \ double>\nstd::vector<std::complex<float_t>> fft_convolve(std::vector<std::complex<float_t>>\
    \ a,\n                                                std::vector<std::complex<float_t>>\
    \ b) {\n  if (a.empty() || b.empty())\n    return {};\n  size_t n = 1, target\
    \ = a.size() + b.size() - 1;\n  while (n < target)\n    n <<= 1;\n  a.resize(n),\
    \ b.resize(n);\n  fft(a), fft(b);\n  for (size_t i = 0; i < n; ++i)\n    a[i]\
    \ *= b[i];\n  fft<-1>(a), a.resize(target);\n  return a;\n}\n\n/**\n * @brief\
    \ Perform convolution of two real-valued vectors using FFT.\n * @tparam float_t\
    \ Floating-point type for computations (default: double).\n * @param a First input\
    \ vector of real numbers.\n * @param b Second input vector of real numbers.\n\
    \ * @return Vector containing the convolution result.\n * @note This function\
    \ uses a technique that combines two real sequences into\n *       a single complex\
    \ sequence to perform the convolution more efficiently.\n */\ntemplate <typename\
    \ float_t = double>\nstd::vector<float_t> fft_convolve_real(const std::vector<float_t>\
    \ &a,\n                                       const std::vector<float_t> &b) {\n\
    \  size_t n = 1;\n  while (n < a.size() + b.size() - 1)\n    n <<= 1;\n  std::vector<std::complex<float_t>>\
    \ F(n);\n  for (size_t i = 0; i < a.size(); ++i)\n    F[i].real(a[i]);\n  for\
    \ (size_t i = 0; i < b.size(); ++i)\n    F[i].imag(b[i]);\n  fft(F);\n  for (size_t\
    \ i = 0; i < n; ++i)\n    F[i] *= F[i];\n  fft<-1>(F);\n  std::vector<float_t>\
    \ result(a.size() + b.size() - 1);\n  for (size_t i = 0; i < result.size(); ++i)\n\
    \    result[i] = F[i].imag() / 2;\n  return result;\n}\n} // namespace weilycoder\n\
    \n#endif\n"
  dependsOn:
  - weilycoder/poly/fft.hpp
  - weilycoder/poly/fft_utility.hpp
  isVerificationFile: false
  path: weilycoder/poly/fft_convolve.hpp
  requiredBy: []
  timestamp: '2025-11-08 10:59:24+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/multiplication_of_big_integers.fft.test.cpp
documentation_of: weilycoder/poly/fft_convolve.hpp
layout: document
redirect_from:
- /library/weilycoder/poly/fft_convolve.hpp
- /library/weilycoder/poly/fft_convolve.hpp.html
title: Multiplying polynomials using Fast Fourier Transform (FFT)
---
