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
    links: []
  bundledCode: "#line 1 \"weilycoder/data-struct/static_range_sum.hpp\"\n\n\n\n#include\
    \ <cstddef>\n#include <vector>\n\nnamespace weilycoder {\ntemplate <typename T,\
    \ typename ptr_t = size_t> struct StaticRangeSum {\n  std::vector<T> prefix_sum;\n\
    \n  StaticRangeSum(const std::vector<T> &data) : prefix_sum(data.size() + 1) {\n\
    \    for (ptr_t i = 1; i <= data.size(); ++i)\n      prefix_sum[i] = prefix_sum[i\
    \ - 1] + data[i - 1];\n  }\n\n  T query(ptr_t l, ptr_t r) const { return prefix_sum[r]\
    \ - prefix_sum[l]; }\n};\n} // namespace weilycoder\n\n\n"
  code: "#ifndef WEILYCODER_STATIC_RANGE_SUM_HPP\n#define WEILYCODER_STATIC_RANGE_SUM_HPP\n\
    \n#include <cstddef>\n#include <vector>\n\nnamespace weilycoder {\ntemplate <typename\
    \ T, typename ptr_t = size_t> struct StaticRangeSum {\n  std::vector<T> prefix_sum;\n\
    \n  StaticRangeSum(const std::vector<T> &data) : prefix_sum(data.size() + 1) {\n\
    \    for (ptr_t i = 1; i <= data.size(); ++i)\n      prefix_sum[i] = prefix_sum[i\
    \ - 1] + data[i - 1];\n  }\n\n  T query(ptr_t l, ptr_t r) const { return prefix_sum[r]\
    \ - prefix_sum[l]; }\n};\n} // namespace weilycoder\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: weilycoder/data-struct/static_range_sum.hpp
  requiredBy: []
  timestamp: '2025-10-28 23:07:26+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/static_range_sum.test.cpp
documentation_of: weilycoder/data-struct/static_range_sum.hpp
layout: document
redirect_from:
- /library/weilycoder/data-struct/static_range_sum.hpp
- /library/weilycoder/data-struct/static_range_sum.hpp.html
title: weilycoder/data-struct/static_range_sum.hpp
---
