#ifndef WEILYCODER_POLY_NTT_CONVOLVE_HPP
#define WEILYCODER_POLY_NTT_CONVOLVE_HPP

#include "ntt.hpp"
#include <cstdint>

namespace weilycoder {
template <uint64_t mod, uint64_t root = prime_primitive_root<mod>()>
std::vector<uint64_t> ntt_convolve(std::vector<uint64_t> a, std::vector<uint64_t> b) {
  constexpr bool bit32 = (mod < (1ULL << 32));
  size_t n = 1;
  while (n < a.size() + b.size() - 1)
    n <<= 1;
  a.resize(n, 0);
  b.resize(n, 0);
  ntt<mod, false, root>(a);
  ntt<mod, false, root>(b);
  for (size_t i = 0; i < n; ++i)
    a[i] = mod_mul<bit32>(a[i], b[i], mod);
  ntt<mod, true, root>(a);
  a.resize(a.size() + b.size() - 1);
  return a;
}
} // namespace weilycoder

#endif
