#ifndef WEILYCODER_GROUP_HPP
#define WEILYCODER_GROUP_HPP

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

#endif
