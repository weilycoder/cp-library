#ifndef WEILYCODER_POLY_FFT_HPP
#define WEILYCODER_POLY_FFT_HPP

#include "fft_utility.hpp"
#include <complex>
#include <cstddef>
#include <vector>

/**
 * @file fft.hpp
 * @brief Implementation of Fast Fourier Transform (FFT) and its inverse.
 */

namespace weilycoder {
/**
 * @brief In-place iterative Cooley–Tukey FFT / inverse FFT on a complex vector.
 *        The length of the input vector should be a power of two.
 * @tparam on Direction of the transform: 1 for FFT, -1 for inverse FFT.
 * @tparam float_t Floating-point type for computations (default: double).
 * @param y Vector of complex numbers to be transformed in-place.
 */
template <int32_t on = 1, typename float_t = double>
void fft(std::vector<std::complex<float_t>> &y) {
  static_assert(on == 1 || on == -1, "on must be 1 or -1");
  fft_change(y);
  for (size_t h = 2; h <= y.size(); h <<= 1) {
    std::complex<float_t> wn(cos(2 * PI<float_t> / h), sin(on * 2 * PI<float_t> / h));
    for (size_t j = 0; j < y.size(); j += h) {
      std::complex<float_t> w(1, 0);
      for (size_t k = j; k < j + (h >> 1); ++k, w *= wn) {
        std::complex<float_t> u = y[k], t = w * y[k + (h >> 1)];
        y[k] = u + t, y[k + (h >> 1)] = u - t;
      }
    }
  }
  size_t len = y.size();
  if constexpr (on == -1)
    for (size_t i = 0; i < len; ++i)
      y[i] /= len;
}
} // namespace weilycoder

#endif
