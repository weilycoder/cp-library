---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: weilycoder/ds/unionfind.hpp
    title: Union-Find (Disjoint Set Union) Data Structure
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/unionfind
    links:
    - https://judge.yosupo.jp/problem/unionfind
  bundledCode: "#line 1 \"test/unionfind.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\
    \n\n#line 1 \"weilycoder/ds/unionfind.hpp\"\n\n\n\n/**\n * @file unionfind.hpp\n\
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
    \ true;\n  }\n};\n} // namespace weilycoder\n\n\n#line 4 \"test/unionfind.test.cpp\"\
    \n#include <iostream>\nusing namespace std;\nusing namespace weilycoder;\n\nint\
    \ main() {\n  cin.tie(nullptr)->sync_with_stdio(false);\n  cin.exceptions(cin.failbit\
    \ | cin.badbit);\n  size_t n, q;\n  cin >> n >> q;\n  UnionFind uf(n);\n  for\
    \ (size_t _ = 0; _ < q; ++_) {\n    size_t op, x, y;\n    cin >> op >> x >> y;\n\
    \    switch (op) {\n    case 0:\n      uf.unite(x, y);\n      break;\n    case\
    \ 1:\n      cout << (uf.getf(x) == uf.getf(y) ? \"1\\n\" : \"0\\n\");\n      break;\n\
    \    }\n  }\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\n\n#include\
    \ \"../weilycoder/ds/unionfind.hpp\"\n#include <iostream>\nusing namespace std;\n\
    using namespace weilycoder;\n\nint main() {\n  cin.tie(nullptr)->sync_with_stdio(false);\n\
    \  cin.exceptions(cin.failbit | cin.badbit);\n  size_t n, q;\n  cin >> n >> q;\n\
    \  UnionFind uf(n);\n  for (size_t _ = 0; _ < q; ++_) {\n    size_t op, x, y;\n\
    \    cin >> op >> x >> y;\n    switch (op) {\n    case 0:\n      uf.unite(x, y);\n\
    \      break;\n    case 1:\n      cout << (uf.getf(x) == uf.getf(y) ? \"1\\n\"\
    \ : \"0\\n\");\n      break;\n    }\n  }\n  return 0;\n}"
  dependsOn:
  - weilycoder/ds/unionfind.hpp
  isVerificationFile: true
  path: test/unionfind.test.cpp
  requiredBy: []
  timestamp: '2025-10-30 21:07:51+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/unionfind.test.cpp
layout: document
redirect_from:
- /verify/test/unionfind.test.cpp
- /verify/test/unionfind.test.cpp.html
title: test/unionfind.test.cpp
---
