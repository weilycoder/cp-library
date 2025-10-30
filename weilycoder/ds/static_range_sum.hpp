#ifndef WEILYCODER_STATIC_RANGE_SUM_HPP
#define WEILYCODER_STATIC_RANGE_SUM_HPP

/**
 * @file static_range_sum.hpp
 * @brief Static Range Sum using Prefix Sums
 */

#include "group.hpp"
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace weilycoder {
/**
 * @brief Static Range Sum using Prefix Sums
 * @tparam Group A group defining the operation and identity element,
 *                must be associative and invertible (i.e. Group).
 */
template <typename Group> struct StaticRangeSum {
  using value_type = typename Group::value_type;
  using T = value_type;

private:
  std::vector<T> prefix_sum;

public:
  /**
   * @brief Constructs a StaticRangeSum for n elements initialized to the
   *        identity element
   * @param n Number of elements
   */
  explicit StaticRangeSum(const std::vector<T> &data)
      : prefix_sum(data.size() + 1, Group::identity()) {
    for (size_t i = 1; i <= data.size(); ++i)
      prefix_sum[i] = Group::operation(prefix_sum[i - 1], data[i - 1]);
  }

  /**
   * @brief Constructs a StaticRangeSum from an initial range
   * @tparam InputIt Input iterator type
   * @param first Beginning of the range
   * @param last End of the range
   */
  template <typename InputIt>
  StaticRangeSum(InputIt first, InputIt last)
      : prefix_sum(std::distance(first, last) + 1, Group::identity()) {
    size_t i = 1;
    for (auto it = first; it != last; ++it, ++i)
      prefix_sum[i] = Group::operation(prefix_sum[i - 1], *it);
  }

  /**
   * @brief Returns the number of elements
   * @return Number of elements
   */
  size_t size() const { return prefix_sum.size() - 1; }

  /**
   * @brief Queries the sum in the range [l, r)
   * @param l Left index (inclusive)
   * @param r Right index (exclusive)
   * @return Sum in the range [l, r)
   * @throws std::out_of_range if the range is invalid
   */
  T query(size_t l, size_t r) const {
    if (l > r || r > size())
      throw std::out_of_range("Invalid range for StaticRangeSum query");
    return Group::operation(Group::inverse(prefix_sum[l]), prefix_sum[r]);
  }
};
} // namespace weilycoder

#endif
