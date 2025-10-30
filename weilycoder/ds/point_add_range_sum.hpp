#ifndef WEILYCODER_POINT_ADD_RANGE_SUM_HPP
#define WEILYCODER_POINT_ADD_RANGE_SUM_HPP

#include "group.hpp"
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace weilycoder {
/**
 * @brief Point Add Range Sum using Fenwick Tree (Binary Indexed Tree)
 * @tparam Group A group defining the operation and identity element,
 *                must be associative and commutative (i.e. Abelian group).
 */
template <typename Group> struct PointAddRangeSum {
  using value_type = typename Group::value_type;
  using T = value_type;

private:
  std::vector<T> data;

public:
  /**
   * @brief Constructs a PointAddRangeSum for n elements initialized to the
   *        identity element
   * @param n Number of elements
   */
  explicit PointAddRangeSum(size_t n) : data(n + 1, Group::identity()) {}

  /**
   * @brief Constructs a PointAddRangeSum from an initial array
   * @param initial Initial array of elements
   */
  explicit PointAddRangeSum(const std::vector<T> &initial)
      : data(initial.size() + 1, Group::identity()) {
    for (size_t i = 1; i <= initial.size(); ++i) {
      data[i] = Group::operation(data[i], initial[i - 1]);
      size_t j = i + (i & -i);
      if (j < data.size())
        data[j] = Group::operation(data[j], data[i]);
    }
  }

  /**
   * @brief Constructs a PointAddRangeSum from an initial range
   * @tparam InputIt Input iterator type
   * @param first Beginning of the range
   * @param last End of the range
   */
  template <typename InputIt>
  explicit PointAddRangeSum(InputIt first, InputIt last)
      : data(std::distance(first, last) + 1, Group::identity()) {
    size_t i = 1;
    for (auto it = first; it != last; ++it, ++i) {
      data[i] = Group::operation(data[i], *it);
      size_t j = i + (i & -i);
      if (j < data.size())
        data[j] = Group::operation(data[j], data[i]);
    }
  }

  size_t size() const { return data.size() - 1; }

  /**
   * @brief Adds value x to element at index i
   * @param i Index to update
   * @param x Value to add
   */
  void point_add(size_t i, const T &x) {
    for (++i; i < data.size(); i += i & -i)
      data[i] = Group::operation(data[i], x);
  }

  /**
   * @brief Computes the prefix sum [0, i)
   * @param i Index (exclusive)
   * @return The sum of elements in the range [0, i)
   */
  T prefix_sum(size_t i) const {
    if (i > size())
      throw std::out_of_range("Index out of range in prefix_sum");
    T result = Group::identity();
    for (; i > 0; i -= i & -i)
      result = Group::operation(result, data[i]);
    return result;
  }

  /**
   * @brief Computes the range sum [l, r)
   * @param l Left index (inclusive)
   * @param r Right index (exclusive)
   * @return The sum of elements in the range [l, r)
   */
  T range_sum(size_t l, size_t r) const {
    if (l > r || r > size())
      throw std::out_of_range("Invalid range for range_sum");
    return Group::operation(prefix_sum(r), Group::inverse(prefix_sum(l)));
  }
};
} // namespace weilycoder

#endif
