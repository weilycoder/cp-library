---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/point_add_range_sum.test.cpp
    title: test/point_add_range_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Point Add Range Sum using Fenwick Tree
    links: []
  bundledCode: "#line 1 \"weilycoder/ds/point_add_range_sum.hpp\"\n\n\n\n/**\n * @file\
    \ point_add_range_sum.hpp\n * @brief Point Add Range Sum using Fenwick Tree\n\
    \ */\n\n#include <cstddef>\n#include <stdexcept>\n#include <vector>\n\nnamespace\
    \ weilycoder {\n/**\n * @brief Point Add Range Sum using Fenwick Tree (Binary\
    \ Indexed Tree)\n * @tparam Group A group defining the operation and identity\
    \ element,\n *                must be associative and commutative (i.e. Abelian\
    \ group).\n */\ntemplate <typename Group> struct PointAddRangeSum {\n  using value_type\
    \ = typename Group::value_type;\n  using T = value_type;\n\nprivate:\n  std::vector<T>\
    \ data;\n\npublic:\n  /**\n   * @brief Constructs a PointAddRangeSum for n elements\
    \ initialized to the\n   *        identity element\n   * @param n Number of elements\n\
    \   */\n  explicit PointAddRangeSum(size_t n) : data(n + 1, Group::identity())\
    \ {}\n\n  /**\n   * @brief Constructs a PointAddRangeSum from an initial array\n\
    \   * @param initial Initial array of elements\n   */\n  explicit PointAddRangeSum(const\
    \ std::vector<T> &initial)\n      : data(initial.size() + 1, Group::identity())\
    \ {\n    for (size_t i = 1; i <= initial.size(); ++i) {\n      data[i] = Group::operation(data[i],\
    \ initial[i - 1]);\n      size_t j = i + (i & -i);\n      if (j < data.size())\n\
    \        data[j] = Group::operation(data[j], data[i]);\n    }\n  }\n\n  /**\n\
    \   * @brief Constructs a PointAddRangeSum from an initial range\n   * @tparam\
    \ InputIt Input iterator type\n   * @param first Beginning of the range\n   *\
    \ @param last End of the range\n   */\n  template <typename InputIt>\n  explicit\
    \ PointAddRangeSum(InputIt first, InputIt last)\n      : data(std::distance(first,\
    \ last) + 1, Group::identity()) {\n    size_t i = 1;\n    for (auto it = first;\
    \ it != last; ++it, ++i) {\n      data[i] = Group::operation(data[i], *it);\n\
    \      size_t j = i + (i & -i);\n      if (j < data.size())\n        data[j] =\
    \ Group::operation(data[j], data[i]);\n    }\n  }\n\n  size_t size() const { return\
    \ data.size() - 1; }\n\n  /**\n   * @brief Adds value x to element at index i\n\
    \   * @param i Index to update\n   * @param x Value to add\n   */\n  void point_add(size_t\
    \ i, const T &x) {\n    for (++i; i < data.size(); i += i & -i)\n      data[i]\
    \ = Group::operation(data[i], x);\n  }\n\n  /**\n   * @brief Computes the prefix\
    \ sum [0, i)\n   * @param i Index (exclusive)\n   * @return The sum of elements\
    \ in the range [0, i)\n   */\n  T prefix_sum(size_t i) const {\n    if (i > size())\n\
    \      throw std::out_of_range(\"Index out of range in prefix_sum\");\n    T result\
    \ = Group::identity();\n    for (; i > 0; i -= i & -i)\n      result = Group::operation(result,\
    \ data[i]);\n    return result;\n  }\n\n  /**\n   * @brief Computes the range\
    \ sum [l, r)\n   * @param l Left index (inclusive)\n   * @param r Right index\
    \ (exclusive)\n   * @return The sum of elements in the range [l, r)\n   */\n \
    \ T range_sum(size_t l, size_t r) const {\n    if (l > r || r > size())\n    \
    \  throw std::out_of_range(\"Invalid range for range_sum\");\n    return Group::operation(prefix_sum(r),\
    \ Group::inverse(prefix_sum(l)));\n  }\n};\n} // namespace weilycoder\n\n\n"
  code: "#ifndef WEILYCODER_POINT_ADD_RANGE_SUM_HPP\n#define WEILYCODER_POINT_ADD_RANGE_SUM_HPP\n\
    \n/**\n * @file point_add_range_sum.hpp\n * @brief Point Add Range Sum using Fenwick\
    \ Tree\n */\n\n#include <cstddef>\n#include <stdexcept>\n#include <vector>\n\n\
    namespace weilycoder {\n/**\n * @brief Point Add Range Sum using Fenwick Tree\
    \ (Binary Indexed Tree)\n * @tparam Group A group defining the operation and identity\
    \ element,\n *                must be associative and commutative (i.e. Abelian\
    \ group).\n */\ntemplate <typename Group> struct PointAddRangeSum {\n  using value_type\
    \ = typename Group::value_type;\n  using T = value_type;\n\nprivate:\n  std::vector<T>\
    \ data;\n\npublic:\n  /**\n   * @brief Constructs a PointAddRangeSum for n elements\
    \ initialized to the\n   *        identity element\n   * @param n Number of elements\n\
    \   */\n  explicit PointAddRangeSum(size_t n) : data(n + 1, Group::identity())\
    \ {}\n\n  /**\n   * @brief Constructs a PointAddRangeSum from an initial array\n\
    \   * @param initial Initial array of elements\n   */\n  explicit PointAddRangeSum(const\
    \ std::vector<T> &initial)\n      : data(initial.size() + 1, Group::identity())\
    \ {\n    for (size_t i = 1; i <= initial.size(); ++i) {\n      data[i] = Group::operation(data[i],\
    \ initial[i - 1]);\n      size_t j = i + (i & -i);\n      if (j < data.size())\n\
    \        data[j] = Group::operation(data[j], data[i]);\n    }\n  }\n\n  /**\n\
    \   * @brief Constructs a PointAddRangeSum from an initial range\n   * @tparam\
    \ InputIt Input iterator type\n   * @param first Beginning of the range\n   *\
    \ @param last End of the range\n   */\n  template <typename InputIt>\n  explicit\
    \ PointAddRangeSum(InputIt first, InputIt last)\n      : data(std::distance(first,\
    \ last) + 1, Group::identity()) {\n    size_t i = 1;\n    for (auto it = first;\
    \ it != last; ++it, ++i) {\n      data[i] = Group::operation(data[i], *it);\n\
    \      size_t j = i + (i & -i);\n      if (j < data.size())\n        data[j] =\
    \ Group::operation(data[j], data[i]);\n    }\n  }\n\n  size_t size() const { return\
    \ data.size() - 1; }\n\n  /**\n   * @brief Adds value x to element at index i\n\
    \   * @param i Index to update\n   * @param x Value to add\n   */\n  void point_add(size_t\
    \ i, const T &x) {\n    for (++i; i < data.size(); i += i & -i)\n      data[i]\
    \ = Group::operation(data[i], x);\n  }\n\n  /**\n   * @brief Computes the prefix\
    \ sum [0, i)\n   * @param i Index (exclusive)\n   * @return The sum of elements\
    \ in the range [0, i)\n   */\n  T prefix_sum(size_t i) const {\n    if (i > size())\n\
    \      throw std::out_of_range(\"Index out of range in prefix_sum\");\n    T result\
    \ = Group::identity();\n    for (; i > 0; i -= i & -i)\n      result = Group::operation(result,\
    \ data[i]);\n    return result;\n  }\n\n  /**\n   * @brief Computes the range\
    \ sum [l, r)\n   * @param l Left index (inclusive)\n   * @param r Right index\
    \ (exclusive)\n   * @return The sum of elements in the range [l, r)\n   */\n \
    \ T range_sum(size_t l, size_t r) const {\n    if (l > r || r > size())\n    \
    \  throw std::out_of_range(\"Invalid range for range_sum\");\n    return Group::operation(prefix_sum(r),\
    \ Group::inverse(prefix_sum(l)));\n  }\n};\n} // namespace weilycoder\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: weilycoder/ds/point_add_range_sum.hpp
  requiredBy: []
  timestamp: '2025-10-31 23:51:44+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/point_add_range_sum.test.cpp
documentation_of: weilycoder/ds/point_add_range_sum.hpp
layout: document
redirect_from:
- /library/weilycoder/ds/point_add_range_sum.hpp
- /library/weilycoder/ds/point_add_range_sum.hpp.html
title: Point Add Range Sum using Fenwick Tree
---
