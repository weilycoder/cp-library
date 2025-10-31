#ifndef WEILYCODER_GROUP_HPP
#define WEILYCODER_GROUP_HPP

/**
 * @file group.hpp
 * @brief Group Definitions
 */

#include <limits>

namespace weilycoder {
/**
 * @brief Additive Group
 * @tparam T Type of the elements
 */
template <typename T> struct AddGroup {
  using value_type = T;
  static constexpr T operation(const T &a, const T &b) { return a + b; }
  static constexpr T identity() { return T{}; }
  static constexpr T inverse(const T &a) { return -a; }
};

/**
 * @brief Additive Monoid
 * @tparam T Type of the elements
 */
template <typename T> struct AddMonoid {
  using value_type = T;
  static constexpr T operation(const T &a, const T &b) { return a + b; }
  static constexpr T identity() { return T{}; }
};

/**
 * @brief Minimum Monoid for numbers
 * @tparam T Type of the elements, must support std::numeric_limits
 */
template <typename T> struct NumberMinMonoid {
  using value_type = T;
  static constexpr T operation(const T &a, const T &b) { return a < b ? a : b; }
  static constexpr T identity() { return std::numeric_limits<T>::max(); }
};

/**
 * @brief Maximum Monoid for numbers
 * @tparam T Type of the elements, must support std::numeric_limits
 */
template <typename T> struct NumberMaxMonoid {
  using value_type = T;
  static constexpr T operation(const T &a, const T &b) { return a > b ? a : b; }
  static constexpr T identity() { return std::numeric_limits<T>::min(); }
};
} // namespace weilycoder

#endif
