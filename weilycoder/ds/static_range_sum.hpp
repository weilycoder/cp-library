#ifndef WEILYCODER_STATIC_RANGE_SUM_HPP
#define WEILYCODER_STATIC_RANGE_SUM_HPP

#include "group.hpp"
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace weilycoder {
template <typename Group> struct StaticRangeSum {
  using value_type = typename Group::value_type;
  using T = value_type;

private:
  std::vector<T> prefix_sum;

public:
  explicit StaticRangeSum(const std::vector<T> &data)
      : prefix_sum(data.size() + 1, Group::identity()) {
    for (size_t i = 1; i <= data.size(); ++i)
      prefix_sum[i] = Group::operation(prefix_sum[i - 1], data[i - 1]);
  }

  template <typename InputIt>
  StaticRangeSum(InputIt first, InputIt last)
      : prefix_sum(std::distance(first, last) + 1, Group::identity()) {
    size_t i = 1;
    for (auto it = first; it != last; ++it, ++i)
      prefix_sum[i] = Group::operation(prefix_sum[i - 1], *it);
  }

  size_t size() const { return prefix_sum.size() - 1; }

  T query(size_t l, size_t r) const {
    if (l > r || r > size())
      throw std::out_of_range("Invalid range for StaticRangeSum query");
    return Group::operation(Group::inverse(prefix_sum[l]), prefix_sum[r]);
  }
};
} // namespace weilycoder

#endif
