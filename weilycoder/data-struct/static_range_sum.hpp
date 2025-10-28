#ifndef WEILYCODER_STATIC_RANGE_SUM_HPP
#define WEILYCODER_STATIC_RANGE_SUM_HPP

#include <cstddef>
#include <vector>

namespace weilycoder {
template <typename T, typename ptr_t = size_t> struct StaticRangeSum {
  std::vector<T> prefix_sum;

  StaticRangeSum(const std::vector<T> &data) : prefix_sum(data.size() + 1) {
    for (ptr_t i = 1; i <= data.size(); ++i)
      prefix_sum[i] = prefix_sum[i - 1] + data[i - 1];
  }

  T query(ptr_t l, ptr_t r) const { return prefix_sum[r] - prefix_sum[l]; }
};
} // namespace weilycoder

#endif
