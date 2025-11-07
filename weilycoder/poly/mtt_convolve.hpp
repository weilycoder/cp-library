#ifndef WEILYCODER_POLY_MTT_CONVOLVE_HPP
#define WEILYCODER_POLY_MTT_CONVOLVE_HPP

#include "ntt_convolve.hpp"
#include <cstdint>

namespace weilycoder {
/**
 * @brief Multiply two polynomials under modulo using MTT with 3 NTT-friendly moduli.
 * @tparam mod Target modulo.
 * @tparam mod1 First NTT-friendly modulo.
 * @tparam mod2 Second NTT-friendly modulo.
 * @tparam mod3 Third NTT-friendly modulo.
 * @tparam root1 Primitive root of mod1.
 * @tparam root2 Primitive root of mod2.
 * @tparam root3 Primitive root of mod3.
 * @param a Coefficients of the first polynomial.
 * @param b Coefficients of the second polynomial.
 * @return Coefficients of the resulting polynomial after multiplication under modulo
 *         `mod`.
 */
template <uint32_t mod, uint32_t mod1, uint32_t mod2, uint32_t mod3,
          uint32_t root1 = prime_primitive_root<mod1>(),
          uint32_t root2 = prime_primitive_root<mod2>(),
          uint32_t root3 = prime_primitive_root<mod3>()>
std::vector<uint32_t> mtt3_convolve(std::vector<uint64_t> a, std::vector<uint64_t> b) {
  auto c1 = ntt_convolve_32<mod1, root1>(a, b);
  auto c2 = ntt_convolve_32<mod2, root2>(a, b);
  auto c3 = ntt_convolve_32<mod3, root3>(a, b);

  size_t n = c1.size();
  std::vector<uint32_t> c(n);

  constexpr uint64_t MOD = static_cast<uint64_t>(mod1) * mod2;
  constexpr uint64_t inv1 = mod_inv<mod2>(mod1);
  constexpr uint64_t inv2 = mod_inv<mod3>(mod_mul<mod3>(mod1, mod2));

  auto excrt = [&](uint64_t c1, uint64_t c2, uint64_t c3) -> uint32_t {
    uint64_t R = mod_sub<mod2>(c2, c1 % mod2);
    R = mod_mul<mod2>(R, inv1);
    R = mod_mul<MOD>(R, mod1);
    R = mod_add<MOD>(c1, R);
    uint64_t x = mod_sub<mod3>(c3, R % mod3);
    x = mod_mul<mod3>(x, inv2);
    x = mod_mul<mod>(x, MOD % mod);
    return mod_add<mod>(R % mod, x);
  };

  for (size_t i = 0; i < n; ++i)
    c[i] = excrt(c1[i], c2[i], c3[i]);

  return c;
}
} // namespace weilycoder

#endif
