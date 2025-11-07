#ifndef WEILYCODER_POLY_NTT_CONVOLVE_HPP
#define WEILYCODER_POLY_NTT_CONVOLVE_HPP

#include "ntt.hpp"
#include <cstdint>

namespace weilycoder {
template <uint64_t mod, bool bit32 = false, uint64_t root = prime_primitive_root<mod>()>
std::vector<uint64_t> ntt_convolve(std::vector<uint64_t> a, std::vector<uint64_t> b) {
  size_t n = 1;
  while (n < a.size() + b.size() - 1)
    n <<= 1;
  a.resize(n, 0);
  b.resize(n, 0);
  ntt<mod, false, bit32, root>(a);
  ntt<mod, false, bit32, root>(b);
  for (size_t i = 0; i < n; ++i)
    a[i] = mod_mul<bit32>(a[i], b[i], mod);
  ntt<mod, true, bit32, root>(a);
  a.resize(a.size() + b.size() - 1);
  return a;
}

template <uint64_t mod, uint64_t root = prime_primitive_root<mod>()>
std::vector<uint64_t> ntt_convolve_32(std::vector<uint64_t> a,
                                      std::vector<uint64_t> b) {
  return ntt_convolve<mod, true, root>(a, b);
}
} // namespace weilycoder

#endif
