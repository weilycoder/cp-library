---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: weilycoder/graph/tarjan.hpp
    title: weilycoder/graph/tarjan.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/two_edge_connected_components
    links:
    - https://judge.yosupo.jp/problem/two_edge_connected_components
  bundledCode: "#line 1 \"test/two_edge_connected_components.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/two_edge_connected_components\"\n\n#line 1\
    \ \"weilycoder/graph/tarjan.hpp\"\n\n\n\n#include <algorithm>\n#include <cstddef>\n\
    #include <stack>\n#include <utility>\n#include <vector>\n\nnamespace weilycoder\
    \ {\ntemplate <typename ptr_t = size_t> struct TwoEdgeConnectedComponents {\n\
    \  ptr_t dfs_time = 0, edge_time = 1;\n\n  std::vector<bool> in_stack;\n  std::stack<ptr_t>\
    \ stk;\n  std::vector<ptr_t> dfn, low;\n  std::vector<std::vector<std::pair<ptr_t,\
    \ ptr_t>>> graph;\n\n  std::vector<std::vector<ptr_t>> eccs;\n\n  TwoEdgeConnectedComponents(ptr_t\
    \ n)\n      : in_stack(n, false), dfn(n, 0), low(n, 0), graph(n) {}\n\n  void\
    \ add_edge(ptr_t u, ptr_t v) {\n    graph[u].emplace_back(v, edge_time);\n   \
    \ graph[v].emplace_back(u, edge_time);\n    edge_time++;\n  }\n\n  void tarjan(ptr_t\
    \ u, ptr_t parent_edge) {\n    dfn[u] = low[u] = ++dfs_time;\n    stk.push(u);\n\
    \    in_stack[u] = true;\n\n    for (const auto &[v, edge_id] : graph[u]) {\n\
    \      if (edge_id == parent_edge)\n        continue;\n      if (!dfn[v])\n  \
    \      tarjan(v, edge_id), low[u] = std::min(low[u], low[v]);\n      else if (in_stack[v])\n\
    \        low[u] = std::min(low[u], dfn[v]);\n    }\n\n    if (dfn[u] == low[u])\
    \ {\n      eccs.emplace_back();\n      eccs.back().push_back(u);\n      in_stack[u]\
    \ = false;\n      while (stk.top() != u)\n        eccs.back().push_back(stk.top()),\
    \ in_stack[stk.top()] = false, stk.pop();\n      stk.pop();\n    }\n  }\n\n  void\
    \ solve() {\n    for (size_t i = 0; i < graph.size(); ++i)\n      if (!dfn[i])\n\
    \        tarjan(i, 0);\n  }\n};\n\ntemplate <typename ptr_t = size_t> struct StrongConnectedComponents\
    \ {\n  ptr_t dfs_time = 0;\n\n  std::vector<bool> in_stack;\n  std::stack<ptr_t>\
    \ stk;\n  std::vector<ptr_t> dfn, low;\n  std::vector<std::vector<ptr_t>> graph;\n\
    \n  std::vector<std::vector<ptr_t>> sccs;\n\n  StrongConnectedComponents(ptr_t\
    \ n)\n      : in_stack(n, false), dfn(n, 0), low(n, 0), graph(n) {}\n\n  void\
    \ add_edge(ptr_t u, ptr_t v) { graph[u].push_back(v); }\n\n  void tarjan(ptr_t\
    \ u) {\n    dfn[u] = low[u] = ++dfs_time;\n    stk.push(u);\n    in_stack[u] =\
    \ true;\n\n    for (const auto &v : graph[u]) {\n      if (!dfn[v])\n        tarjan(v),\
    \ low[u] = std::min(low[u], low[v]);\n      else if (in_stack[v])\n        low[u]\
    \ = std::min(low[u], dfn[v]);\n    }\n\n    if (dfn[u] == low[u]) {\n      sccs.emplace_back();\n\
    \      sccs.back().push_back(u);\n      in_stack[u] = false;\n      while (stk.top()\
    \ != u)\n        sccs.back().push_back(stk.top()), in_stack[stk.top()] = false,\
    \ stk.pop();\n      stk.pop();\n    }\n  }\n\n  void solve() {\n    for (size_t\
    \ i = 0; i < graph.size(); ++i)\n      if (!dfn[i])\n        tarjan(i);\n    std::reverse(sccs.begin(),\
    \ sccs.end());\n  }\n};\n} // namespace weilycoder\n\n\n#line 4 \"test/two_edge_connected_components.test.cpp\"\
    \n#include <iostream>\nusing namespace std;\nusing namespace weilycoder;\n\nint\
    \ main() {\n  cin.tie(nullptr)->sync_with_stdio(false);\n  cin.exceptions(cin.failbit\
    \ | cin.badbit);\n  size_t n, m;\n  cin >> n >> m;\n\n  TwoEdgeConnectedComponents\
    \ graph(n);\n  for (size_t i = 0; i < m; ++i) {\n    size_t u, v;\n    cin >>\
    \ u >> v;\n    graph.add_edge(u, v);\n  }\n\n  graph.solve();\n\n  cout << graph.eccs.size()\
    \ << '\\n';\n  for (const auto &ecc : graph.eccs) {\n    cout << ecc.size();\n\
    \    for (size_t u : ecc)\n      cout << ' ' << u;\n    cout << '\\n';\n  }\n\
    \  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/two_edge_connected_components\"\
    \n\n#include \"../weilycoder/graph/tarjan.hpp\"\n#include <iostream>\nusing namespace\
    \ std;\nusing namespace weilycoder;\n\nint main() {\n  cin.tie(nullptr)->sync_with_stdio(false);\n\
    \  cin.exceptions(cin.failbit | cin.badbit);\n  size_t n, m;\n  cin >> n >> m;\n\
    \n  TwoEdgeConnectedComponents graph(n);\n  for (size_t i = 0; i < m; ++i) {\n\
    \    size_t u, v;\n    cin >> u >> v;\n    graph.add_edge(u, v);\n  }\n\n  graph.solve();\n\
    \n  cout << graph.eccs.size() << '\\n';\n  for (const auto &ecc : graph.eccs)\
    \ {\n    cout << ecc.size();\n    for (size_t u : ecc)\n      cout << ' ' << u;\n\
    \    cout << '\\n';\n  }\n  return 0;\n}\n"
  dependsOn:
  - weilycoder/graph/tarjan.hpp
  isVerificationFile: true
  path: test/two_edge_connected_components.test.cpp
  requiredBy: []
  timestamp: '2025-10-28 21:05:17+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/two_edge_connected_components.test.cpp
layout: document
redirect_from:
- /verify/test/two_edge_connected_components.test.cpp
- /verify/test/two_edge_connected_components.test.cpp.html
title: test/two_edge_connected_components.test.cpp
---
