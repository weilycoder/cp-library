---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/point_add_range_sum.test.cpp
    title: test/point_add_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/static_range_sum.test.cpp
    title: test/static_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/staticrmq.test.cpp
    title: test/staticrmq.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Group Definitions
    links: []
  bundledCode: "#line 1 \"weilycoder/ds/group.hpp\"\n\n\n\n/**\n * @file group.hpp\n\
    \ * @brief Group Definitions\n */\n\n#include <limits>\n\nnamespace weilycoder\
    \ {\n/**\n * @brief Additive Group\n * @tparam T Type of the elements\n */\ntemplate\
    \ <typename T> struct AddGroup {\n  using value_type = T;\n  static constexpr\
    \ T operation(const T &a, const T &b) { return a + b; }\n  static constexpr T\
    \ identity() { return T{}; }\n  static constexpr T inverse(const T &a) { return\
    \ -a; }\n};\n\n/**\n * @brief Additive Monoid\n * @tparam T Type of the elements\n\
    \ */\ntemplate <typename T> struct AddMonoid {\n  using value_type = T;\n  static\
    \ constexpr T operation(const T &a, const T &b) { return a + b; }\n  static constexpr\
    \ T identity() { return T{}; }\n};\n\n/**\n * @brief Minimum Monoid for numbers\n\
    \ * @tparam T Type of the elements, must support std::numeric_limits\n */\ntemplate\
    \ <typename T> struct NumberMinMonoid {\n  using value_type = T;\n  static constexpr\
    \ T operation(const T &a, const T &b) { return a < b ? a : b; }\n  static constexpr\
    \ T identity() { return std::numeric_limits<T>::max(); }\n};\n\n/**\n * @brief\
    \ Maximum Monoid for numbers\n * @tparam T Type of the elements, must support\
    \ std::numeric_limits\n */\ntemplate <typename T> struct NumberMaxMonoid {\n \
    \ using value_type = T;\n  static constexpr T operation(const T &a, const T &b)\
    \ { return a > b ? a : b; }\n  static constexpr T identity() { return std::numeric_limits<T>::min();\
    \ }\n};\n} // namespace weilycoder\n\n\n"
  code: "#ifndef WEILYCODER_GROUP_HPP\n#define WEILYCODER_GROUP_HPP\n\n/**\n * @file\
    \ group.hpp\n * @brief Group Definitions\n */\n\n#include <limits>\n\nnamespace\
    \ weilycoder {\n/**\n * @brief Additive Group\n * @tparam T Type of the elements\n\
    \ */\ntemplate <typename T> struct AddGroup {\n  using value_type = T;\n  static\
    \ constexpr T operation(const T &a, const T &b) { return a + b; }\n  static constexpr\
    \ T identity() { return T{}; }\n  static constexpr T inverse(const T &a) { return\
    \ -a; }\n};\n\n/**\n * @brief Additive Monoid\n * @tparam T Type of the elements\n\
    \ */\ntemplate <typename T> struct AddMonoid {\n  using value_type = T;\n  static\
    \ constexpr T operation(const T &a, const T &b) { return a + b; }\n  static constexpr\
    \ T identity() { return T{}; }\n};\n\n/**\n * @brief Minimum Monoid for numbers\n\
    \ * @tparam T Type of the elements, must support std::numeric_limits\n */\ntemplate\
    \ <typename T> struct NumberMinMonoid {\n  using value_type = T;\n  static constexpr\
    \ T operation(const T &a, const T &b) { return a < b ? a : b; }\n  static constexpr\
    \ T identity() { return std::numeric_limits<T>::max(); }\n};\n\n/**\n * @brief\
    \ Maximum Monoid for numbers\n * @tparam T Type of the elements, must support\
    \ std::numeric_limits\n */\ntemplate <typename T> struct NumberMaxMonoid {\n \
    \ using value_type = T;\n  static constexpr T operation(const T &a, const T &b)\
    \ { return a > b ? a : b; }\n  static constexpr T identity() { return std::numeric_limits<T>::min();\
    \ }\n};\n} // namespace weilycoder\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: weilycoder/ds/group.hpp
  requiredBy: []
  timestamp: '2025-10-31 09:52:58+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/static_range_sum.test.cpp
  - test/staticrmq.test.cpp
  - test/point_add_range_sum.test.cpp
documentation_of: weilycoder/ds/group.hpp
layout: document
redirect_from:
- /library/weilycoder/ds/group.hpp
- /library/weilycoder/ds/group.hpp.html
title: Group Definitions
---
