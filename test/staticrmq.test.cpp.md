---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: weilycoder/ds/group.hpp
    title: Group Definitions
  - icon: ':heavy_check_mark:'
    path: weilycoder/ds/offline_static_range_query.hpp
    title: Offline Static Range Query Data Structure
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/staticrmq
    links:
    - https://judge.yosupo.jp/problem/staticrmq
  bundledCode: "#line 1 \"test/staticrmq.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\
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
    };\n} // namespace weilycoder\n\n\n#line 1 \"weilycoder/ds/offline_static_range_query.hpp\"\
    \n\n\n\n/**\n * @file offline_static_range_query.hpp\n * @brief Offline Static\
    \ Range Query Data Structure\n */\n\n#include <cstddef>\n#include <numeric>\n\
    #include <stdexcept>\n#include <utility>\n#include <vector>\n\nnamespace weilycoder\
    \ {\n/**\n * @brief Offline Static Range Query Data Structure\n * @tparam Monoid\
    \ The monoid defining the operation and identity\n * @tparam ptr_t The type used\
    \ for indexing (default: size_t)\n */\ntemplate <typename Monoid, typename ptr_t\
    \ = size_t> class OfflineStaticRangeQuery {\npublic:\n  using T = typename Monoid::value_type;\n\
    \nprivate:\n  ptr_t query_count, data_size;\n\n  std::vector<std::vector<std::pair<ptr_t,\
    \ ptr_t>>> queries;\n\n  std::vector<T> values;\n  std::vector<ptr_t> parent;\n\
    \n  /**\n   * @brief Find with path compression and value aggregation\n   * @param\
    \ x The index to find\n   * @return The root index after path compression\n  \
    \ */\n  ptr_t find(ptr_t x) {\n    ptr_t y = parent[x];\n    if (y == x)\n   \
    \   return x;\n    parent[x] = find(y);\n    if (y != parent[x])\n      values[x]\
    \ = Monoid::operation(values[x], values[y]);\n    return parent[x];\n  }\n\n \
    \ /**\n   * @brief Initialize data values\n   * @param datas The data values to\
    \ initialize\n   * @throws std::invalid_argument if the size does not match\n\
    \   */\n  void init_datas(const std::vector<T> &datas) {\n    values = datas;\n\
    \    if (datas.size() != data_size)\n      throw std::invalid_argument(\"Data\
    \ size does not match the initialized size.\");\n    values.resize(datas.size()\
    \ + 1, Monoid::identity());\n  }\n\n  /**\n   * @brief Initialize data values\
    \ from iterators\n   * @tparam InputIt The type of the input iterator\n   * @param\
    \ first The beginning iterator\n   * @param last The ending iterator\n   * @throws\
    \ std::invalid_argument if the size does not match\n   */\n  template <typename\
    \ InputIt> void init_datas(InputIt first, InputIt last) {\n    values.assign(first,\
    \ last);\n    if (values.size() != data_size)\n      throw std::invalid_argument(\"\
    Data size does not match the initialized size.\");\n    values.resize(data_size\
    \ + 1, Monoid::identity());\n  }\n\n  /**\n   * @brief Process the queries and\
    \ return results\n   * @param datas The data values\n   * @return A vector of\
    \ results for each query\n   */\n  std::vector<T> work(const std::vector<T> &datas)\
    \ {\n    parent.resize(datas.size() + 1);\n    std::iota(parent.begin(), parent.end(),\
    \ 0);\n\n    std::vector<T> results(query_count, Monoid::identity());\n    for\
    \ (size_t i = 1; i <= datas.size(); ++i) {\n      parent[i - 1] = i;\n      for\
    \ (const auto &[l, idx] : queries[i])\n        if (l < i)\n          find(l),\
    \ results[idx] = values[l];\n    }\n    return results;\n  }\n\npublic:\n  /**\n\
    \   * @brief Constructor\n   * @param n The size of the data\n   */\n  explicit\
    \ OfflineStaticRangeQuery(ptr_t n)\n      : query_count(0), data_size(n), queries(n\
    \ + 1) {}\n\n  /**\n   * @brief Add a query for the range [l, r)\n   * @param\
    \ l The left index (inclusive)\n   * @param r The right index (exclusive)\n  \
    \ */\n  void add_query(ptr_t l, ptr_t r) {\n    queries[std::min(r, data_size)].emplace_back(l,\
    \ query_count++);\n  }\n\n  /**\n   * @brief Process the queries with the given\
    \ data values\n   * @param datas The data values\n   * @return A vector of results\
    \ for each query\n   */\n  std::vector<T> process(const std::vector<T> &datas)\
    \ {\n    init_datas(datas);\n    return work(datas);\n  }\n\n  /**\n   * @brief\
    \ Process the queries with the given data values from iterators\n   * @tparam\
    \ InputIt The type of the input iterator\n   * @param first The beginning iterator\n\
    \   * @param last The ending iterator\n   * @return A vector of results for each\
    \ query\n   */\n  template <typename InputIt> std::vector<T> process(InputIt first,\
    \ InputIt last) {\n    init_datas(first, last);\n    return work(values);\n  }\n\
    };\n} // namespace weilycoder\n\n\n#line 5 \"test/staticrmq.test.cpp\"\n#include\
    \ <cstdint>\n#include <iostream>\n#line 8 \"test/staticrmq.test.cpp\"\nusing namespace\
    \ std;\nusing namespace weilycoder;\n\nint main() {\n  cin.tie(nullptr)->sync_with_stdio(false);\n\
    \  cin.exceptions(cin.failbit | cin.badbit);\n  size_t n, q;\n  cin >> n >> q;\n\
    \n  vector<uint32_t> datas(n);\n  for (auto &x : datas)\n    cin >> x;\n\n  OfflineStaticRangeQuery<NumberMinMonoid<uint32_t>>\
    \ osrq(n);\n  for (size_t i = 0; i < q; ++i) {\n    size_t l, r;\n    cin >> l\
    \ >> r;\n    osrq.add_query(l, r);\n  }\n\n  for (const auto &res : osrq.process(datas))\n\
    \    cout << res << '\\n';\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n\n#include\
    \ \"../weilycoder/ds/group.hpp\"\n#include \"../weilycoder/ds/offline_static_range_query.hpp\"\
    \n#include <cstdint>\n#include <iostream>\n#include <vector>\nusing namespace\
    \ std;\nusing namespace weilycoder;\n\nint main() {\n  cin.tie(nullptr)->sync_with_stdio(false);\n\
    \  cin.exceptions(cin.failbit | cin.badbit);\n  size_t n, q;\n  cin >> n >> q;\n\
    \n  vector<uint32_t> datas(n);\n  for (auto &x : datas)\n    cin >> x;\n\n  OfflineStaticRangeQuery<NumberMinMonoid<uint32_t>>\
    \ osrq(n);\n  for (size_t i = 0; i < q; ++i) {\n    size_t l, r;\n    cin >> l\
    \ >> r;\n    osrq.add_query(l, r);\n  }\n\n  for (const auto &res : osrq.process(datas))\n\
    \    cout << res << '\\n';\n  return 0;\n}"
  dependsOn:
  - weilycoder/ds/group.hpp
  - weilycoder/ds/offline_static_range_query.hpp
  isVerificationFile: true
  path: test/staticrmq.test.cpp
  requiredBy: []
  timestamp: '2025-10-31 23:51:44+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/staticrmq.test.cpp
layout: document
redirect_from:
- /verify/test/staticrmq.test.cpp
- /verify/test/staticrmq.test.cpp.html
title: test/staticrmq.test.cpp
---
