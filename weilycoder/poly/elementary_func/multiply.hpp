#ifndef WEILYCODER_POLY_ELEMENTARY_FUNC_MULTIPLY_HPP
#define WEILYCODER_POLY_ELEMENTARY_FUNC_MULTIPLY_HPP

/**
 * @file multiply.hpp
 * @brief Polynomial Multiplication Functions
 */

#include "../../number_theory/mod_utility.hpp"
#include "../ntt_convolve.hpp"
#include <vector>

namespace weilycoder {
/**
 * @brief Multiply two polynomials using a provided multiplication function.
 * @tparam T Coefficient type.
 * @tparam MultiplyFunc Type of the multiplication function.
 * @param a Coefficients of the first polynomial.
 * @param b Coefficients of the second polynomial.
 * @param multiply Function to multiply two polynomials.
 * @return Coefficients of the resulting polynomial after multiplication.
 */
template <typename T, typename MultiplyFunc>
std::vector<T> poly_mul(const std::vector<T> &a, const std::vector<T> &b,
                        MultiplyFunc multiply) {
  return multiply(a, b);
}

/**
 * @brief Multiply two polynomials using a provided multiplication function,
 *        limiting the result to degree n-1.
 * @tparam T Coefficient type.
 * @tparam MultiplyFunc Type of the multiplication function.
 * @param a Coefficients of the first polynomial.
 * @param b Coefficients of the second polynomial.
 * @param n Maximum degree of the resulting polynomial (result size will be n).
 * @param multiply Function to multiply two polynomials.
 * @return Coefficients of the resulting polynomial after multiplication,
 *         limited to degree n-1.
 */
template <typename T, typename MultiplyFunc>
std::vector<T> poly_mul(const std::vector<T> &a, const std::vector<T> &b, size_t n,
                        MultiplyFunc multiply) {
  auto res = multiply(std::vector<T>(a.begin(), min(a.begin() + n, a.end())),
                      std::vector<T>(b.begin(), min(b.begin() + n, b.end())));
  res.resize(n);
  return res;
}

/**
 * @brief Multiply two polynomials using NTT under a given modulus,
 *        limiting the result to degree n-1.
 * @tparam mod Modulus for NTT.
 * @param a Coefficients of the first polynomial.
 * @param b Coefficients of the second polynomial.
 * @param n Maximum degree of the resulting polynomial (result size will be n).
 * @return Coefficients of the resulting polynomial after multiplication,
 *         limited to degree n-1.
 */
template <uint64_t mod>
std::vector<uint64_t> ntt_poly_mul(const std::vector<uint64_t> &a,
                                   const std::vector<uint64_t> &b, size_t n) {
  auto res = ntt_convolve<mod>(
      std::vector<uint64_t>(a.begin(), std::min(a.begin() + n, a.end())),
      std::vector<uint64_t>(b.begin(), std::min(b.begin() + n, b.end())));
  res.resize(n);
  return res;
}
} // namespace weilycoder

#endif
