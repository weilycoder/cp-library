---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: weilycoder/ds/point_add_range_sum.hpp
    title: Point Add Range Sum using Fenwick Tree
  - icon: ':heavy_check_mark:'
    path: weilycoder/ds/static_range_sum.hpp
    title: Static Range Sum using Prefix Sums
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/point_add_range_sum.test.cpp
    title: test/point_add_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/static_range_sum.test.cpp
    title: test/static_range_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Group Definitions
    links: []
  bundledCode: "#line 1 \"weilycoder/ds/group.hpp\"\n\n\n\n/**\n * @file group.hpp\n\
    \ * @brief Group Definitions\n */\n\nnamespace weilycoder {\n/**\n * @brief Additive\
    \ Group\n * @tparam T Type of the elements\n */\ntemplate <typename T> struct\
    \ AddGroup {\n  using value_type = T;\n  static constexpr T operation(const T\
    \ &a, const T &b) { return a + b; }\n  static constexpr T identity() { return\
    \ T{}; }\n  static constexpr T inverse(const T &a) { return -a; }\n};\n} // namespace\
    \ weilycoder\n\n\n"
  code: "#ifndef WEILYCODER_GROUP_HPP\n#define WEILYCODER_GROUP_HPP\n\n/**\n * @file\
    \ group.hpp\n * @brief Group Definitions\n */\n\nnamespace weilycoder {\n/**\n\
    \ * @brief Additive Group\n * @tparam T Type of the elements\n */\ntemplate <typename\
    \ T> struct AddGroup {\n  using value_type = T;\n  static constexpr T operation(const\
    \ T &a, const T &b) { return a + b; }\n  static constexpr T identity() { return\
    \ T{}; }\n  static constexpr T inverse(const T &a) { return -a; }\n};\n} // namespace\
    \ weilycoder\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: weilycoder/ds/group.hpp
  requiredBy:
  - weilycoder/ds/point_add_range_sum.hpp
  - weilycoder/ds/static_range_sum.hpp
  timestamp: '2025-10-30 21:08:13+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/static_range_sum.test.cpp
  - test/point_add_range_sum.test.cpp
documentation_of: weilycoder/ds/group.hpp
layout: document
redirect_from:
- /library/weilycoder/ds/group.hpp
- /library/weilycoder/ds/group.hpp.html
title: Group Definitions
---
