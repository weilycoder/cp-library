#ifndef WEILYCODER_POLY_ELEMENTARY_FUNC_LOGARITHM_HPP
#define WEILYCODER_POLY_ELEMENTARY_FUNC_LOGARITHM_HPP

#include "../../number_theory/mod_utility.hpp"
#include "../ntt_convolve.hpp"
#include "derivative.hpp"
#include "integrate.hpp"
#include "inverse.hpp"
#include "multiply.hpp"
#include <cstdint>
#include <vector>

namespace weilycoder {
template <typename T, typename PolyMultiplyFunc, typename SubtractFunc,
          typename MultiplyFunc, typename InverseFunc>
std::vector<T> logarithm(const std::vector<T> &poly, size_t n,
                         PolyMultiplyFunc multiply, SubtractFunc number_sub,
                         MultiplyFunc number_mul, InverseFunc number_inv) {
  if (poly.empty() || poly[0] != T(1))
    throw std::invalid_argument(
        "Logarithm is only defined for polynomials with constant term 1.");
  auto inv = poly_inv(poly, n, multiply, number_sub, number_inv);
  auto prod = poly_mul(derivative(poly, number_mul), inv, n - 1, multiply);
  return integrate(prod, number_mul, number_inv);
}

template <uint64_t mod>
std::vector<uint64_t> ntt_logarithm(const std::vector<uint64_t> &poly, size_t n) {
  return logarithm(poly, n, ntt_convolve<mod>, mod_sub<mod>, mod_mul<mod>,
                   mod_inv<mod>);
}
} // namespace weilycoder

#endif
