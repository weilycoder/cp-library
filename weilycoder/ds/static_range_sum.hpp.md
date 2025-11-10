---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/static_range_sum.test.cpp
    title: test/static_range_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Static Range Sum using Prefix Sums
    links: []
  bundledCode: "#line 1 \"weilycoder/ds/static_range_sum.hpp\"\n\n\n\n/**\n * @file\
    \ static_range_sum.hpp\n * @brief Static Range Sum using Prefix Sums\n */\n\n\
    #include <cstddef>\n#include <stdexcept>\n#include <vector>\n\nnamespace weilycoder\
    \ {\n/**\n * @brief Static Range Sum using Prefix Sums\n * @tparam Group A group\
    \ defining the operation and identity element,\n *                must be associative\
    \ and invertible (i.e. Group).\n */\ntemplate <typename Group> struct StaticRangeSum\
    \ {\n  using value_type = typename Group::value_type;\n  using T = value_type;\n\
    \nprivate:\n  std::vector<T> prefix_sum;\n\npublic:\n  /**\n   * @brief Constructs\
    \ a StaticRangeSum for n elements initialized to the\n   *        identity element\n\
    \   * @param n Number of elements\n   */\n  explicit StaticRangeSum(const std::vector<T>\
    \ &data)\n      : prefix_sum(data.size() + 1, Group::identity()) {\n    for (size_t\
    \ i = 1; i <= data.size(); ++i)\n      prefix_sum[i] = Group::operation(prefix_sum[i\
    \ - 1], data[i - 1]);\n  }\n\n  /**\n   * @brief Constructs a StaticRangeSum from\
    \ an initial range\n   * @tparam InputIt Input iterator type\n   * @param first\
    \ Beginning of the range\n   * @param last End of the range\n   */\n  template\
    \ <typename InputIt>\n  StaticRangeSum(InputIt first, InputIt last)\n      : prefix_sum(std::distance(first,\
    \ last) + 1, Group::identity()) {\n    size_t i = 1;\n    for (auto it = first;\
    \ it != last; ++it, ++i)\n      prefix_sum[i] = Group::operation(prefix_sum[i\
    \ - 1], *it);\n  }\n\n  /**\n   * @brief Returns the number of elements\n   *\
    \ @return Number of elements\n   */\n  size_t size() const { return prefix_sum.size()\
    \ - 1; }\n\n  /**\n   * @brief Queries the sum in the range [l, r)\n   * @param\
    \ l Left index (inclusive)\n   * @param r Right index (exclusive)\n   * @return\
    \ Sum in the range [l, r)\n   * @throws std::out_of_range if the range is invalid\n\
    \   */\n  T query(size_t l, size_t r) const {\n    if (l > r || r > size())\n\
    \      throw std::out_of_range(\"Invalid range for StaticRangeSum query\");\n\
    \    return Group::operation(Group::inverse(prefix_sum[l]), prefix_sum[r]);\n\
    \  }\n};\n} // namespace weilycoder\n\n\n"
  code: "#ifndef WEILYCODER_STATIC_RANGE_SUM_HPP\n#define WEILYCODER_STATIC_RANGE_SUM_HPP\n\
    \n/**\n * @file static_range_sum.hpp\n * @brief Static Range Sum using Prefix\
    \ Sums\n */\n\n#include <cstddef>\n#include <stdexcept>\n#include <vector>\n\n\
    namespace weilycoder {\n/**\n * @brief Static Range Sum using Prefix Sums\n *\
    \ @tparam Group A group defining the operation and identity element,\n *     \
    \           must be associative and invertible (i.e. Group).\n */\ntemplate <typename\
    \ Group> struct StaticRangeSum {\n  using value_type = typename Group::value_type;\n\
    \  using T = value_type;\n\nprivate:\n  std::vector<T> prefix_sum;\n\npublic:\n\
    \  /**\n   * @brief Constructs a StaticRangeSum for n elements initialized to\
    \ the\n   *        identity element\n   * @param n Number of elements\n   */\n\
    \  explicit StaticRangeSum(const std::vector<T> &data)\n      : prefix_sum(data.size()\
    \ + 1, Group::identity()) {\n    for (size_t i = 1; i <= data.size(); ++i)\n \
    \     prefix_sum[i] = Group::operation(prefix_sum[i - 1], data[i - 1]);\n  }\n\
    \n  /**\n   * @brief Constructs a StaticRangeSum from an initial range\n   * @tparam\
    \ InputIt Input iterator type\n   * @param first Beginning of the range\n   *\
    \ @param last End of the range\n   */\n  template <typename InputIt>\n  StaticRangeSum(InputIt\
    \ first, InputIt last)\n      : prefix_sum(std::distance(first, last) + 1, Group::identity())\
    \ {\n    size_t i = 1;\n    for (auto it = first; it != last; ++it, ++i)\n   \
    \   prefix_sum[i] = Group::operation(prefix_sum[i - 1], *it);\n  }\n\n  /**\n\
    \   * @brief Returns the number of elements\n   * @return Number of elements\n\
    \   */\n  size_t size() const { return prefix_sum.size() - 1; }\n\n  /**\n   *\
    \ @brief Queries the sum in the range [l, r)\n   * @param l Left index (inclusive)\n\
    \   * @param r Right index (exclusive)\n   * @return Sum in the range [l, r)\n\
    \   * @throws std::out_of_range if the range is invalid\n   */\n  T query(size_t\
    \ l, size_t r) const {\n    if (l > r || r > size())\n      throw std::out_of_range(\"\
    Invalid range for StaticRangeSum query\");\n    return Group::operation(Group::inverse(prefix_sum[l]),\
    \ prefix_sum[r]);\n  }\n};\n} // namespace weilycoder\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: weilycoder/ds/static_range_sum.hpp
  requiredBy: []
  timestamp: '2025-10-31 23:51:44+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/static_range_sum.test.cpp
documentation_of: weilycoder/ds/static_range_sum.hpp
layout: document
redirect_from:
- /library/weilycoder/ds/static_range_sum.hpp
- /library/weilycoder/ds/static_range_sum.hpp.html
title: Static Range Sum using Prefix Sums
---
