---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: weilycoder/unionfind.hpp
    title: weilycoder/unionfind.hpp
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
    \n\n#line 1 \"weilycoder/unionfind.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <numeric>\n#include <vector>\n\nnamespace weilycoder {\ntemplate <typename ptr_t\
    \ = size_t> struct UnionFind {\n  std::vector<ptr_t> parent, size;\n\n  UnionFind(ptr_t\
    \ n) : parent(n), size(n, 1) {\n    std::iota(parent.begin(), parent.end(), 0);\n\
    \  }\n\n  ptr_t getf(ptr_t x) {\n    while (x != parent[x])\n      x = parent[x]\
    \ = parent[parent[x]];\n    return x;\n  }\n\n  bool unite(ptr_t x, ptr_t y) {\n\
    \    x = getf(x), y = getf(y);\n    if (x == y)\n      return false;\n    if (size[x]\
    \ < size[y])\n      std::swap(x, y);\n    parent[y] = x, size[x] += size[y];\n\
    \    return true;\n  }\n};\n} // namespace weilycoder\n\n\n#line 4 \"test/unionfind.test.cpp\"\
    \n#include <iostream>\nusing namespace std;\nusing namespace weilycoder;\n\nint\
    \ main() {\n  cin.tie(nullptr)->sync_with_stdio(false);\n  cin.exceptions(cin.failbit\
    \ | cin.badbit);\n  size_t n, q;\n  cin >> n >> q;\n  UnionFind uf(n);\n  for\
    \ (size_t _ = 0; _ < q; ++_) {\n    size_t op, x, y;\n    cin >> op >> x >> y;\n\
    \    switch (op) {\n    case 0:\n      uf.unite(x, y);\n      break;\n    case\
    \ 1:\n      cout << (uf.getf(x) == uf.getf(y) ? \"1\\n\" : \"0\\n\");\n      break;\n\
    \    }\n  }\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\n\n#include\
    \ \"../weilycoder/unionfind.hpp\"\n#include <iostream>\nusing namespace std;\n\
    using namespace weilycoder;\n\nint main() {\n  cin.tie(nullptr)->sync_with_stdio(false);\n\
    \  cin.exceptions(cin.failbit | cin.badbit);\n  size_t n, q;\n  cin >> n >> q;\n\
    \  UnionFind uf(n);\n  for (size_t _ = 0; _ < q; ++_) {\n    size_t op, x, y;\n\
    \    cin >> op >> x >> y;\n    switch (op) {\n    case 0:\n      uf.unite(x, y);\n\
    \      break;\n    case 1:\n      cout << (uf.getf(x) == uf.getf(y) ? \"1\\n\"\
    \ : \"0\\n\");\n      break;\n    }\n  }\n  return 0;\n}"
  dependsOn:
  - weilycoder/unionfind.hpp
  isVerificationFile: true
  path: test/unionfind.test.cpp
  requiredBy: []
  timestamp: '2025-10-28 20:19:29+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/unionfind.test.cpp
layout: document
redirect_from:
- /verify/test/unionfind.test.cpp
- /verify/test/unionfind.test.cpp.html
title: test/unionfind.test.cpp
---
