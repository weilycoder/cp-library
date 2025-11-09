#ifndef WEILYCODER_POLY_ELEMENTARY_FUNC_EXPONENTIAL_HPP
#define WEILYCODER_POLY_ELEMENTARY_FUNC_EXPONENTIAL_HPP

/**
 * @file exponential.hpp
 * @brief Polynomial Exponential Functions
 */

#include "../../number_theory/mod_utility.hpp"
#include "logarithm.hpp"
#include <vector>

namespace weilycoder {
/**
 * @brief Compute the exponential of a polynomial modulo x^n.
 * @tparam T Coefficient type.
 * @tparam PolyMultiplyFunc Type of the multiplication function.
 * @tparam AddFunc Type of the addition function for coefficients.
 * @tparam SubtractFunc Type of the subtraction function for coefficients.
 * @tparam MultiplyFunc Type of the multiplication function for coefficients.
 * @tparam InverseFunc Type of the inversion function for coefficients.
 * @param poly Coefficients of the polynomial.
 * @param n Degree up to which the exponential is computed (result size will be n).
 * @param multiply Function to multiply two polynomials.
 * @param number_add Function to add two coefficients.
 * @param number_sub Function to subtract two coefficients.
 * @param number_mul Function to multiply two coefficients.
 * @param number_inv Function to compute the multiplicative inverse of a coefficient.
 * @return Coefficients of the exponential polynomial.
 */
template <typename T, typename PolyMultiplyFunc, typename AddFunc,
          typename SubtractFunc, typename MultiplyFunc, typename InverseFunc>
std::vector<T> exponential(const std::vector<T> &poly, size_t n,
                           PolyMultiplyFunc multiply, AddFunc number_add,
                           SubtractFunc number_sub, MultiplyFunc number_mul,
                           InverseFunc number_inv) {
  if (!poly.empty() && poly[0] != T(0))
    throw std::invalid_argument(
        "Exponential is only defined for polynomials with constant term 0.");
  std::vector<T> result = {T(1)};
  for (size_t len = 1; len < n; len <<= 1) {
    size_t m = std::min(n, len << 1);
    auto temp = logarithm(result, m, multiply, number_sub, number_mul, number_inv);
    temp.front() = number_sub(T(1), temp.front());
    for (size_t i = 1; i < temp.size(); ++i)
      temp[i] = number_sub(T(0), temp[i]);
    for (size_t i = 0; i < std::min(poly.size(), m); ++i)
      temp[i] = number_add(temp[i], poly[i]);
    result = poly_mul(result, temp, m, multiply);
  }
  return result;
}

/**
 * @brief Compute the exponential of a polynomial modulo x^n using NTT
 *        under a given modulus.
 * @tparam mod Modulus for NTT.
 * @param poly Coefficients of the polynomial.
 * @param n Degree up to which the exponential is computed (result size will be n).
 * @return Coefficients of the exponential polynomial.
 */
template <uint64_t mod>
std::vector<uint64_t> ntt_exponential(const std::vector<uint64_t> &poly, size_t n) {
  return exponential<uint64_t>(poly, n, ntt_convolve<mod>, mod_add<mod>, mod_sub<mod>,
                               mod_mul<mod>, mod_inv<mod>);
}
} // namespace weilycoder

#endif
