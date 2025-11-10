---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: weilycoder/ds/group.hpp
    title: Group Definitions
  - icon: ':heavy_check_mark:'
    path: weilycoder/ds/point_add_range_sum.hpp
    title: Point Add Range Sum using Fenwick Tree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_range_sum
  bundledCode: "#line 1 \"test/point_add_range_sum.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/point_add_range_sum\"\n\n#line 1 \"weilycoder/ds/group.hpp\"\
    \n\n\n\n/**\n * @file group.hpp\n * @brief Group Definitions\n */\n\n#include\
    \ <limits>\n\nnamespace weilycoder {\n/**\n * @brief Additive Group\n * @tparam\
    \ T Type of the elements\n */\ntemplate <typename T> struct AddGroup {\n  using\
    \ value_type = T;\n  static constexpr T operation(const T &a, const T &b) { return\
    \ a + b; }\n  static constexpr T identity() { return T{}; }\n  static constexpr\
    \ T inverse(const T &a) { return -a; }\n};\n\n/**\n * @brief Additive Monoid\n\
    \ * @tparam T Type of the elements\n */\ntemplate <typename T> struct AddMonoid\
    \ {\n  using value_type = T;\n  static constexpr T operation(const T &a, const\
    \ T &b) { return a + b; }\n  static constexpr T identity() { return T{}; }\n};\n\
    \n/**\n * @brief Minimum Monoid for numbers\n * @tparam T Type of the elements,\
    \ must support std::numeric_limits\n */\ntemplate <typename T> struct NumberMinMonoid\
    \ {\n  using value_type = T;\n  static constexpr T operation(const T &a, const\
    \ T &b) { return a < b ? a : b; }\n  static constexpr T identity() { return std::numeric_limits<T>::max();\
    \ }\n};\n\n/**\n * @brief Maximum Monoid for numbers\n * @tparam T Type of the\
    \ elements, must support std::numeric_limits\n */\ntemplate <typename T> struct\
    \ NumberMaxMonoid {\n  using value_type = T;\n  static constexpr T operation(const\
    \ T &a, const T &b) { return a > b ? a : b; }\n  static constexpr T identity()\
    \ { return std::numeric_limits<T>::min(); }\n};\n} // namespace weilycoder\n\n\
    \n#line 1 \"weilycoder/ds/point_add_range_sum.hpp\"\n\n\n\n/**\n * @file point_add_range_sum.hpp\n\
    \ * @brief Point Add Range Sum using Fenwick Tree\n */\n\n#include <cstddef>\n\
    #include <stdexcept>\n#include <vector>\n\nnamespace weilycoder {\n/**\n * @brief\
    \ Point Add Range Sum using Fenwick Tree (Binary Indexed Tree)\n * @tparam Group\
    \ A group defining the operation and identity element,\n *                must\
    \ be associative and commutative (i.e. Abelian group).\n */\ntemplate <typename\
    \ Group> struct PointAddRangeSum {\n  using value_type = typename Group::value_type;\n\
    \  using T = value_type;\n\nprivate:\n  std::vector<T> data;\n\npublic:\n  /**\n\
    \   * @brief Constructs a PointAddRangeSum for n elements initialized to the\n\
    \   *        identity element\n   * @param n Number of elements\n   */\n  explicit\
    \ PointAddRangeSum(size_t n) : data(n + 1, Group::identity()) {}\n\n  /**\n  \
    \ * @brief Constructs a PointAddRangeSum from an initial array\n   * @param initial\
    \ Initial array of elements\n   */\n  explicit PointAddRangeSum(const std::vector<T>\
    \ &initial)\n      : data(initial.size() + 1, Group::identity()) {\n    for (size_t\
    \ i = 1; i <= initial.size(); ++i) {\n      data[i] = Group::operation(data[i],\
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
    \ Group::inverse(prefix_sum(l)));\n  }\n};\n} // namespace weilycoder\n\n\n#line\
    \ 5 \"test/point_add_range_sum.test.cpp\"\n#include <cstdint>\n#include <iostream>\n\
    #line 8 \"test/point_add_range_sum.test.cpp\"\nusing namespace std;\nusing namespace\
    \ weilycoder;\n\nint main() {\n  cin.tie(nullptr)->sync_with_stdio(false);\n \
    \ cin.exceptions(cin.failbit | cin.badbit);\n  size_t n, q;\n  cin >> n >> q;\n\
    \n  vector<uint64_t> initial(n, 0);\n  for (size_t i = 0; i < n; ++i)\n    cin\
    \ >> initial[i];\n\n  PointAddRangeSum<AddGroup<uint64_t>> pasr(initial);\n  while\
    \ (q--) {\n    int type;\n    cin >> type;\n    if (type == 0) {\n      size_t\
    \ i, x;\n      cin >> i >> x;\n      pasr.point_add(i, x);\n    } else {\n   \
    \   size_t l, r;\n      cin >> l >> r;\n      cout << pasr.range_sum(l, r) <<\
    \ '\\n';\n    }\n  }\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\
    \n#include \"../weilycoder/ds/group.hpp\"\n#include \"../weilycoder/ds/point_add_range_sum.hpp\"\
    \n#include <cstdint>\n#include <iostream>\n#include <vector>\nusing namespace\
    \ std;\nusing namespace weilycoder;\n\nint main() {\n  cin.tie(nullptr)->sync_with_stdio(false);\n\
    \  cin.exceptions(cin.failbit | cin.badbit);\n  size_t n, q;\n  cin >> n >> q;\n\
    \n  vector<uint64_t> initial(n, 0);\n  for (size_t i = 0; i < n; ++i)\n    cin\
    \ >> initial[i];\n\n  PointAddRangeSum<AddGroup<uint64_t>> pasr(initial);\n  while\
    \ (q--) {\n    int type;\n    cin >> type;\n    if (type == 0) {\n      size_t\
    \ i, x;\n      cin >> i >> x;\n      pasr.point_add(i, x);\n    } else {\n   \
    \   size_t l, r;\n      cin >> l >> r;\n      cout << pasr.range_sum(l, r) <<\
    \ '\\n';\n    }\n  }\n  return 0;\n}"
  dependsOn:
  - weilycoder/ds/group.hpp
  - weilycoder/ds/point_add_range_sum.hpp
  isVerificationFile: true
  path: test/point_add_range_sum.test.cpp
  requiredBy: []
  timestamp: '2025-10-31 23:51:44+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/point_add_range_sum.test.cpp
layout: document
redirect_from:
- /verify/test/point_add_range_sum.test.cpp
- /verify/test/point_add_range_sum.test.cpp.html
title: test/point_add_range_sum.test.cpp
---
