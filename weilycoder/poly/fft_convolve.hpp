#ifndef WEILYCODER_POLY_FFT_CONVOLVE_HPP
#define WEILYCODER_POLY_FFT_CONVOLVE_HPP

#include "fft.hpp"
#include <complex>
#include <cstddef>
#include <vector>

/**
 * @file fft_convolve.hpp
 * @brief Functions for performing convolution using Fast Fourier Transform (FFT).  
 */

namespace weilycoder {
/**
 * @brief Perform convolution of two complex vectors using FFT.
 * @tparam float_t Floating-point type for computations (default: double).
 * @param a First input vector of complex numbers.
 * @param b Second input vector of complex numbers.
 * @return Vector containing the convolution result.
 */
template <typename float_t = double>
std::vector<std::complex<float_t>> fft_convolve(std::vector<std::complex<float_t>> a,
                                                std::vector<std::complex<float_t>> b) {
  size_t n = 1;
  while (n < a.size() + b.size() - 1)
    n <<= 1;
  a.resize(n), b.resize(n);
  fft(a), fft(b);
  for (size_t i = 0; i < n; ++i)
    a[i] *= b[i];
  return fft<-1>(a), a;
}

/**
 * @brief Perform convolution of two real-valued vectors using FFT.
 * @tparam float_t Floating-point type for computations (default: double).
 * @param a First input vector of real numbers.
 * @param b Second input vector of real numbers.
 * @return Vector containing the convolution result.
 * @note This function uses a technique that combines two real sequences into
 *       a single complex sequence to perform the convolution more efficiently.
 */
template <typename float_t = double>
std::vector<float_t> fft_convolve_real(const std::vector<float_t> &a,
                                       const std::vector<float_t> &b) {
  size_t n = 1;
  while (n < a.size() + b.size() - 1)
    n <<= 1;
  std::vector<std::complex<float_t>> F(n);
  for (size_t i = 0; i < a.size(); ++i)
    F[i].real(a[i]);
  for (size_t i = 0; i < b.size(); ++i)
    F[i].imag(b[i]);
  fft(F);
  for (size_t i = 0; i < n; ++i)
    F[i] *= F[i];
  fft<-1>(F);
  std::vector<float_t> result(a.size() + b.size() - 1);
  for (size_t i = 0; i < result.size(); ++i)
    result[i] = F[i].imag() / 2;
  return result;
}
} // namespace weilycoder

#endif
