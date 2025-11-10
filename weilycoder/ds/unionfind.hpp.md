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
    document_title: Union-Find (Disjoint Set Union) Data Structure
    links: []
  bundledCode: "#line 1 \"weilycoder/ds/unionfind.hpp\"\n\n\n\n/**\n * @file unionfind.hpp\n\
    \ * @brief Union-Find (Disjoint Set Union) Data Structure\n */\n\n#include <algorithm>\n\
    #include <numeric>\n#include <vector>\n\nnamespace weilycoder {\n/**\n * @brief\
    \ Union-Find (Disjoint Set Union) Data Structure\n * @tparam ptr_t Type for representing\
    \ indices (default: size_t)\n */\ntemplate <typename ptr_t = size_t> struct UnionFind\
    \ {\nprivate:\n  std::vector<ptr_t> parent, setSize;\n\npublic:\n  /**\n   * @brief\
    \ Constructs a UnionFind with n elements, each in its own set\n   * @param n Number\
    \ of elements\n   */\n  UnionFind(ptr_t n) : parent(n), setSize(n, 1) {\n    std::iota(parent.begin(),\
    \ parent.end(), 0);\n  }\n\n  /**\n   * @brief Returns the number of elements\n\
    \   * @return Number of elements\n   */\n  size_t size() const { return parent.size();\
    \ }\n\n  /**\n   * @brief Returns the size of the set containing x\n   * @param\
    \ x Element to query\n   * @return Size of the set containing x\n   */\n  size_t\
    \ get_size(ptr_t x) { return setSize[getf(x)]; }\n\n  /**\n   * @brief Finds the\
    \ representative of the set containing x\n   * @param x Element to find\n   *\
    \ @return Representative of the set containing x\n   */\n  ptr_t getf(ptr_t x)\
    \ {\n    while (x != parent[x])\n      x = parent[x] = parent[parent[x]];\n  \
    \  return x;\n  }\n\n  /**\n   * @brief Unites the sets containing x and y\n \
    \  * @param x First element\n   * @param y Second element\n   * @return True if\
    \ the sets were separate and have been united, false if they\n   *         were\
    \ already in the same set\n   */\n  bool unite(ptr_t x, ptr_t y) {\n    x = getf(x),\
    \ y = getf(y);\n    if (x == y)\n      return false;\n    if (setSize[x] < setSize[y])\n\
    \      std::swap(x, y);\n    parent[y] = x, setSize[x] += setSize[y];\n    return\
    \ true;\n  }\n};\n} // namespace weilycoder\n\n\n"
  code: "#ifndef WEILYCODER_UNIONFIND_HPP\n#define WEILYCODER_UNIONFIND_HPP\n\n/**\n\
    \ * @file unionfind.hpp\n * @brief Union-Find (Disjoint Set Union) Data Structure\n\
    \ */\n\n#include <algorithm>\n#include <numeric>\n#include <vector>\n\nnamespace\
    \ weilycoder {\n/**\n * @brief Union-Find (Disjoint Set Union) Data Structure\n\
    \ * @tparam ptr_t Type for representing indices (default: size_t)\n */\ntemplate\
    \ <typename ptr_t = size_t> struct UnionFind {\nprivate:\n  std::vector<ptr_t>\
    \ parent, setSize;\n\npublic:\n  /**\n   * @brief Constructs a UnionFind with\
    \ n elements, each in its own set\n   * @param n Number of elements\n   */\n \
    \ UnionFind(ptr_t n) : parent(n), setSize(n, 1) {\n    std::iota(parent.begin(),\
    \ parent.end(), 0);\n  }\n\n  /**\n   * @brief Returns the number of elements\n\
    \   * @return Number of elements\n   */\n  size_t size() const { return parent.size();\
    \ }\n\n  /**\n   * @brief Returns the size of the set containing x\n   * @param\
    \ x Element to query\n   * @return Size of the set containing x\n   */\n  size_t\
    \ get_size(ptr_t x) { return setSize[getf(x)]; }\n\n  /**\n   * @brief Finds the\
    \ representative of the set containing x\n   * @param x Element to find\n   *\
    \ @return Representative of the set containing x\n   */\n  ptr_t getf(ptr_t x)\
    \ {\n    while (x != parent[x])\n      x = parent[x] = parent[parent[x]];\n  \
    \  return x;\n  }\n\n  /**\n   * @brief Unites the sets containing x and y\n \
    \  * @param x First element\n   * @param y Second element\n   * @return True if\
    \ the sets were separate and have been united, false if they\n   *         were\
    \ already in the same set\n   */\n  bool unite(ptr_t x, ptr_t y) {\n    x = getf(x),\
    \ y = getf(y);\n    if (x == y)\n      return false;\n    if (setSize[x] < setSize[y])\n\
    \      std::swap(x, y);\n    parent[y] = x, setSize[x] += setSize[y];\n    return\
    \ true;\n  }\n};\n} // namespace weilycoder\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: weilycoder/ds/unionfind.hpp
  requiredBy: []
  timestamp: '2025-10-30 21:07:51+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/unionfind.test.cpp
documentation_of: weilycoder/ds/unionfind.hpp
layout: document
redirect_from:
- /library/weilycoder/ds/unionfind.hpp
- /library/weilycoder/ds/unionfind.hpp.html
title: Union-Find (Disjoint Set Union) Data Structure
---
