#ifndef WEILYCODER_MODINT_HPP
#define WEILYCODER_MODINT_HPP

/**
 * @file modint.hpp
 * @brief Modular Integer Class
 */

#include "mod_utility.hpp"
#include <cstdint>
#include <istream>
#include <ostream>

namespace weilycoder {
/**
 * @brief Modular Integer with compile-time modulus.
 * @tparam Modulus The modulus.
 */
template <uint64_t Modulus> struct modint {
private:
  uint64_t value;

public:
  constexpr modint() : value(0) {}
  constexpr modint(uint32_t v) : value(v % Modulus) {}
  constexpr modint(int32_t v) { from_i64(v); }
  constexpr modint(uint64_t v) : value(v % Modulus) {}
  constexpr modint(int64_t v) { from_i64(v); }

  constexpr void from_i64(int64_t v) {
    int64_t x = v % static_cast<int64_t>(Modulus);
    if (x < 0)
      x += Modulus;
    value = static_cast<uint64_t>(x);
  }

  explicit operator uint64_t() const { return value; }

  friend constexpr modint<Modulus> operator+(const modint<Modulus> &lhs,
                                             const modint<Modulus> &rhs) {
    return modint<Modulus>(mod_add<Modulus>(lhs.value, rhs.value));
  }

  friend constexpr modint<Modulus> operator-(const modint<Modulus> &lhs,
                                             const modint<Modulus> &rhs) {
    return modint<Modulus>(mod_sub<Modulus>(lhs.value, rhs.value));
  }

  friend constexpr modint<Modulus> operator*(const modint<Modulus> &lhs,
                                             const modint<Modulus> &rhs) {
    return modint<Modulus>(mod_mul<Modulus>(lhs.value, rhs.value));
  }

  modint &operator+=(const modint &other) {
    value = mod_add<Modulus>(value, other.value);
    return *this;
  }

  modint &operator-=(const modint &other) {
    value = mod_sub<Modulus>(value, other.value);
    return *this;
  }

  modint &operator*=(const modint &other) {
    value = mod_mul<Modulus>(value, other.value);
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &os, const modint &m) {
    return os << m.value;
  }

  friend std::istream &operator>>(std::istream &is, modint &m) {
    int64_t v;
    is >> v;
    m.from_i64(v);
    return is;
  }
};
} // namespace weilycoder

#endif
