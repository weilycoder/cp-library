#ifndef WEILYCODER_POLY_ELEMENTARY_FUNC_MULTIPLY_HPP
#define WEILYCODER_POLY_ELEMENTARY_FUNC_MULTIPLY_HPP

#include "../../number_theory/mod_utility.hpp"
#include "../ntt_convolve.hpp"
#include <vector>

namespace weilycoder {
template <typename T, typename MultiplyFunc>
std::vector<T> poly_mul(const std::vector<T> &a, const std::vector<T> &b,
                        MultiplyFunc multiply) {
  return multiply(a, b);
}

template <typename T, typename MultiplyFunc>
std::vector<T> poly_mul(const std::vector<T> &a, const std::vector<T> &b, size_t n,
                        MultiplyFunc multiply) {
  auto res = multiply(std::vector<T>(a.begin(), min(a.begin() + n, a.end())),
                      std::vector<T>(b.begin(), min(b.begin() + n, b.end())));
  res.resize(n);
  return res;
}

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
