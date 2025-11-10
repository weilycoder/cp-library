---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: weilycoder/ds/group.hpp
    title: Group Definitions
  - icon: ':heavy_check_mark:'
    path: weilycoder/ds/static_range_sum.hpp
    title: Static Range Sum using Prefix Sums
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/static_range_sum
    links:
    - https://judge.yosupo.jp/problem/static_range_sum
  bundledCode: "#line 1 \"test/static_range_sum.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_sum\"\
    \n\n#line 1 \"weilycoder/ds/group.hpp\"\n\n\n\n/**\n * @file group.hpp\n * @brief\
    \ Group Definitions\n */\n\n#include <limits>\n\nnamespace weilycoder {\n/**\n\
    \ * @brief Additive Group\n * @tparam T Type of the elements\n */\ntemplate <typename\
    \ T> struct AddGroup {\n  using value_type = T;\n  static constexpr T operation(const\
    \ T &a, const T &b) { return a + b; }\n  static constexpr T identity() { return\
    \ T{}; }\n  static constexpr T inverse(const T &a) { return -a; }\n};\n\n/**\n\
    \ * @brief Additive Monoid\n * @tparam T Type of the elements\n */\ntemplate <typename\
    \ T> struct AddMonoid {\n  using value_type = T;\n  static constexpr T operation(const\
    \ T &a, const T &b) { return a + b; }\n  static constexpr T identity() { return\
    \ T{}; }\n};\n\n/**\n * @brief Minimum Monoid for numbers\n * @tparam T Type of\
    \ the elements, must support std::numeric_limits\n */\ntemplate <typename T> struct\
    \ NumberMinMonoid {\n  using value_type = T;\n  static constexpr T operation(const\
    \ T &a, const T &b) { return a < b ? a : b; }\n  static constexpr T identity()\
    \ { return std::numeric_limits<T>::max(); }\n};\n\n/**\n * @brief Maximum Monoid\
    \ for numbers\n * @tparam T Type of the elements, must support std::numeric_limits\n\
    \ */\ntemplate <typename T> struct NumberMaxMonoid {\n  using value_type = T;\n\
    \  static constexpr T operation(const T &a, const T &b) { return a > b ? a : b;\
    \ }\n  static constexpr T identity() { return std::numeric_limits<T>::min(); }\n\
    };\n} // namespace weilycoder\n\n\n#line 1 \"weilycoder/ds/static_range_sum.hpp\"\
    \n\n\n\n/**\n * @file static_range_sum.hpp\n * @brief Static Range Sum using Prefix\
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
    \ prefix_sum[r]);\n  }\n};\n} // namespace weilycoder\n\n\n#line 5 \"test/static_range_sum.test.cpp\"\
    \n#include <cstdint>\n#include <iostream>\n#line 8 \"test/static_range_sum.test.cpp\"\
    \nusing namespace std;\nusing namespace weilycoder;\n\nint main() {\n  cin.tie(nullptr)->sync_with_stdio(false);\n\
    \  cin.exceptions(cin.failbit | cin.badbit);\n  size_t n, q;\n  cin >> n >> q;\n\
    \n  vector<uint64_t> arr(n);\n  for (size_t i = 0; i < n; ++i)\n    cin >> arr[i];\n\
    \n  StaticRangeSum<AddGroup<uint64_t>> sum(arr);\n  while (q--) {\n    size_t\
    \ l, r;\n    cin >> l >> r;\n    cout << sum.query(l, r) << '\\n';\n  }\n  return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_sum\"\n\n\
    #include \"../weilycoder/ds/group.hpp\"\n#include \"../weilycoder/ds/static_range_sum.hpp\"\
    \n#include <cstdint>\n#include <iostream>\n#include <vector>\nusing namespace\
    \ std;\nusing namespace weilycoder;\n\nint main() {\n  cin.tie(nullptr)->sync_with_stdio(false);\n\
    \  cin.exceptions(cin.failbit | cin.badbit);\n  size_t n, q;\n  cin >> n >> q;\n\
    \n  vector<uint64_t> arr(n);\n  for (size_t i = 0; i < n; ++i)\n    cin >> arr[i];\n\
    \n  StaticRangeSum<AddGroup<uint64_t>> sum(arr);\n  while (q--) {\n    size_t\
    \ l, r;\n    cin >> l >> r;\n    cout << sum.query(l, r) << '\\n';\n  }\n  return\
    \ 0;\n}"
  dependsOn:
  - weilycoder/ds/group.hpp
  - weilycoder/ds/static_range_sum.hpp
  isVerificationFile: true
  path: test/static_range_sum.test.cpp
  requiredBy: []
  timestamp: '2025-10-31 23:51:44+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/static_range_sum.test.cpp
layout: document
redirect_from:
- /verify/test/static_range_sum.test.cpp
- /verify/test/static_range_sum.test.cpp.html
title: test/static_range_sum.test.cpp
---
