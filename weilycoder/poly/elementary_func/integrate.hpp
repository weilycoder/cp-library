#ifndef WEILYCODER_POLY_ELEMENTARY_FUNC_INTEGRATE_HPP
#define WEILYCODER_POLY_ELEMENTARY_FUNC_INTEGRATE_HPP

/**
 * @file integrate.hpp
 * @brief Polynomial Integration functions.
 */

#include "../../number_theory/mod_utility.hpp"
#include <vector>

namespace weilycoder {
/**
 * @brief Compute the integral of a polynomial.
 * @tparam T Coefficient type.
 * @tparam MultiplyFunc Type of the multiplication function for coefficients.
 * @tparam InverseFunc Type of the inversion function for coefficients.
 * @param poly Coefficients of the polynomial.
 * @param number_mul Function to multiply two coefficients.
 * @param number_inv Function to compute the multiplicative inverse of a coefficient.
 * @return Coefficients of the integral polynomial.
 */
template <typename T, typename MultiplyFunc, typename InverseFunc>
std::vector<T> integrate(const std::vector<T> &poly, MultiplyFunc number_mul,
                         InverseFunc number_inv) {
  std::vector<T> res(poly.size() + 1);
  for (size_t i = 0; i < poly.size(); ++i)
    res[i + 1] = number_mul(poly[i], number_inv(T(i + 1)));
  return res;
}

/**
 * @brief Compute the integral of a polynomial using modular arithmetic.
 * @tparam mod Modulus for modular arithmetic.
 * @param poly Coefficients of the polynomial.
 * @return Coefficients of the integral polynomial.
 */
template <uint64_t mod>
std::vector<uint64_t> ntt_poly_integrate(const std::vector<uint64_t> &poly) {
  return integrate<>(poly, mod_mul<mod>, mod_inv<mod>);
}
} // namespace weilycoder

#endif
