#ifndef WEILYCODER_POLY_ELEMENTARY_FUNC_INVERSE_HPP
#define WEILYCODER_POLY_ELEMENTARY_FUNC_INVERSE_HPP

#include "../../number_theory/mod_utility.hpp"
#include "../ntt_convolve.hpp"
#include "multiply.hpp"
#include <stdexcept>
#include <vector>

namespace weilycoder {
template <typename T, typename MultiplyFunc, typename SubtractFunc,
          typename InverseFunc>
std::vector<T> poly_inv(const std::vector<T> &a, size_t n, MultiplyFunc multiply,
                        SubtractFunc number_sub, InverseFunc number_inv) {
  if (a.empty() || a[0] == T(0))
    throw std::invalid_argument("Constant term must be non-zero for inversion.");
  std::vector<T> res(1, number_inv(a[0]));
  while (res.size() < n) {
    size_t m = std::min(n, res.size() * 2);
    auto temp = poly_mul(a, res, m, multiply);
    temp.front() = number_sub(T(2), temp.front());
    for (size_t i = 1; i < temp.size(); ++i)
      temp[i] = number_sub(T(0), temp[i]);
    res = poly_mul(res, temp, m, multiply);
  }
  return res;
}

template <uint64_t mod>
std::vector<uint64_t> ntt_poly_inv(const std::vector<uint64_t> &a, size_t n) {
  return poly_inv<>(a, n, ntt_convolve<mod>, mod_sub<mod>, mod_inv<mod>);
}
} // namespace weilycoder

#endif
