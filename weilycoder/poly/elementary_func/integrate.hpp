#ifndef WEILYCODER_POLY_ELEMENTARY_FUNC_INTEGRATE_HPP
#define WEILYCODER_POLY_ELEMENTARY_FUNC_INTEGRATE_HPP

#include "../../number_theory/mod_utility.hpp"
#include <vector>

namespace weilycoder {
template <typename T, typename MultiplyFunc, typename InverseFunc>
std::vector<T> integrate(const std::vector<T> &poly, MultiplyFunc number_mul,
                         InverseFunc number_inv) {
  std::vector<T> res(poly.size() + 1);
  for (size_t i = 0; i < poly.size(); ++i)
    res[i + 1] = number_mul(poly[i], number_inv(T(i + 1)));
  return res;
}

template <uint64_t mod>
std::vector<uint64_t> ntt_poly_integrate(const std::vector<uint64_t> &poly) {
  return integrate<>(poly, mod_inv<mod>);
}
} // namespace weilycoder

#endif
