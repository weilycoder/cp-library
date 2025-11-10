---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/staticrmq.test.cpp
    title: test/staticrmq.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Offline Static Range Query Data Structure
    links: []
  bundledCode: "#line 1 \"weilycoder/ds/offline_static_range_query.hpp\"\n\n\n\n/**\n\
    \ * @file offline_static_range_query.hpp\n * @brief Offline Static Range Query\
    \ Data Structure\n */\n\n#include <cstddef>\n#include <numeric>\n#include <stdexcept>\n\
    #include <utility>\n#include <vector>\n\nnamespace weilycoder {\n/**\n * @brief\
    \ Offline Static Range Query Data Structure\n * @tparam Monoid The monoid defining\
    \ the operation and identity\n * @tparam ptr_t The type used for indexing (default:\
    \ size_t)\n */\ntemplate <typename Monoid, typename ptr_t = size_t> class OfflineStaticRangeQuery\
    \ {\npublic:\n  using T = typename Monoid::value_type;\n\nprivate:\n  ptr_t query_count,\
    \ data_size;\n\n  std::vector<std::vector<std::pair<ptr_t, ptr_t>>> queries;\n\
    \n  std::vector<T> values;\n  std::vector<ptr_t> parent;\n\n  /**\n   * @brief\
    \ Find with path compression and value aggregation\n   * @param x The index to\
    \ find\n   * @return The root index after path compression\n   */\n  ptr_t find(ptr_t\
    \ x) {\n    ptr_t y = parent[x];\n    if (y == x)\n      return x;\n    parent[x]\
    \ = find(y);\n    if (y != parent[x])\n      values[x] = Monoid::operation(values[x],\
    \ values[y]);\n    return parent[x];\n  }\n\n  /**\n   * @brief Initialize data\
    \ values\n   * @param datas The data values to initialize\n   * @throws std::invalid_argument\
    \ if the size does not match\n   */\n  void init_datas(const std::vector<T> &datas)\
    \ {\n    values = datas;\n    if (datas.size() != data_size)\n      throw std::invalid_argument(\"\
    Data size does not match the initialized size.\");\n    values.resize(datas.size()\
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
    };\n} // namespace weilycoder\n\n\n"
  code: "#ifndef WEILYCODER_OFFLINE_STATIC_RANGE_QUERY_HPP\n#define WEILYCODER_OFFLINE_STATIC_RANGE_QUERY_HPP\n\
    \n/**\n * @file offline_static_range_query.hpp\n * @brief Offline Static Range\
    \ Query Data Structure\n */\n\n#include <cstddef>\n#include <numeric>\n#include\
    \ <stdexcept>\n#include <utility>\n#include <vector>\n\nnamespace weilycoder {\n\
    /**\n * @brief Offline Static Range Query Data Structure\n * @tparam Monoid The\
    \ monoid defining the operation and identity\n * @tparam ptr_t The type used for\
    \ indexing (default: size_t)\n */\ntemplate <typename Monoid, typename ptr_t =\
    \ size_t> class OfflineStaticRangeQuery {\npublic:\n  using T = typename Monoid::value_type;\n\
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
    };\n} // namespace weilycoder\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: weilycoder/ds/offline_static_range_query.hpp
  requiredBy: []
  timestamp: '2025-10-31 23:51:44+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/staticrmq.test.cpp
documentation_of: weilycoder/ds/offline_static_range_query.hpp
layout: document
redirect_from:
- /library/weilycoder/ds/offline_static_range_query.hpp
- /library/weilycoder/ds/offline_static_range_query.hpp.html
title: Offline Static Range Query Data Structure
---
