---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/unionfind.test.cpp
    title: test/unionfind.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"weilycoder/data-struct/unionfind.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <numeric>\n#include <vector>\n\nnamespace weilycoder {\ntemplate <typename\
    \ ptr_t = size_t> struct UnionFind {\n  std::vector<ptr_t> parent, size;\n\n \
    \ UnionFind(ptr_t n) : parent(n), size(n, 1) {\n    std::iota(parent.begin(),\
    \ parent.end(), 0);\n  }\n\n  ptr_t getf(ptr_t x) {\n    while (x != parent[x])\n\
    \      x = parent[x] = parent[parent[x]];\n    return x;\n  }\n\n  bool unite(ptr_t\
    \ x, ptr_t y) {\n    x = getf(x), y = getf(y);\n    if (x == y)\n      return\
    \ false;\n    if (size[x] < size[y])\n      std::swap(x, y);\n    parent[y] =\
    \ x, size[x] += size[y];\n    return true;\n  }\n};\n} // namespace weilycoder\n\
    \n\n"
  code: "#ifndef WEILYCODER_UNIONFIND_HPP\n#define WEILYCODER_UNIONFIND_HPP\n\n#include\
    \ <algorithm>\n#include <numeric>\n#include <vector>\n\nnamespace weilycoder {\n\
    template <typename ptr_t = size_t> struct UnionFind {\n  std::vector<ptr_t> parent,\
    \ size;\n\n  UnionFind(ptr_t n) : parent(n), size(n, 1) {\n    std::iota(parent.begin(),\
    \ parent.end(), 0);\n  }\n\n  ptr_t getf(ptr_t x) {\n    while (x != parent[x])\n\
    \      x = parent[x] = parent[parent[x]];\n    return x;\n  }\n\n  bool unite(ptr_t\
    \ x, ptr_t y) {\n    x = getf(x), y = getf(y);\n    if (x == y)\n      return\
    \ false;\n    if (size[x] < size[y])\n      std::swap(x, y);\n    parent[y] =\
    \ x, size[x] += size[y];\n    return true;\n  }\n};\n} // namespace weilycoder\n\
    \n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: weilycoder/data-struct/unionfind.hpp
  requiredBy: []
  timestamp: '2025-10-28 22:53:17+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/unionfind.test.cpp
documentation_of: weilycoder/data-struct/unionfind.hpp
layout: document
redirect_from:
- /library/weilycoder/data-struct/unionfind.hpp
- /library/weilycoder/data-struct/unionfind.hpp.html
title: weilycoder/data-struct/unionfind.hpp
---
