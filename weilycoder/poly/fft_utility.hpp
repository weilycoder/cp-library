#ifndef WEILYCODER_POLY_FFT_UTILITY_HPP
#define WEILYCODER_POLY_FFT_UTILITY_HPP

#include <complex>
#include <cstddef>
#include <vector>

/**
 * @file fft_utility.hpp
 * @brief Utility functions and constants for Fast Fourier Transform (FFT)
 */

namespace weilycoder {
/**
 * @brief Alias for the commonly used complex number type with double precision.
 */
using complex_t = std::complex<double>;

/**
 * @brief Compile-time constant for π (pi) parameterized by numeric type.
 * @tparam T Numeric type (e.g., float, double, long double).
 */
template <typename T> constexpr T PI = T(3.1415926535897932384626433832795l);

/**
 * @brief Perform in-place bit-reversal permutation (index reordering) required by
 *        iterative FFT.
 * @tparam T Element type stored in the vector. Must be Swappable and efficiently
 *         copyable.
 * @param a Vector to be permuted in-place. Its size should typically be a power
 *          of two for use with the FFT implementation in this file.
 */
template <typename T> void fft_change(std::vector<T> &a) {
  size_t n = a.size();
  std::vector<size_t> rev(n);
  for (size_t i = 0; i < n; ++i) {
    rev[i] = rev[i >> 1] >> 1;
    if (i & 1)
      rev[i] |= n >> 1;
    if (i < rev[i])
      swap(a[i], a[rev[i]]);
  }
}
} // namespace weilycoder

#endif
