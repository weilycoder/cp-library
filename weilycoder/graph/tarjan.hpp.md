---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/two_edge_connected_components.test.cpp
    title: test/two_edge_connected_components.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"weilycoder/graph/tarjan.hpp\"\n\n\n\n#include <cstddef>\n\
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
    \        tarjan(i, 0);\n  }\n};\n} // namespace weilycoder\n\n\n"
  code: "#ifndef WEILYCODER_TARJAN_HPP\n#define WEILYCODER_TARJAN_HPP\n\n#include\
    \ <cstddef>\n#include <stack>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ weilycoder {\ntemplate <typename ptr_t = size_t> struct TwoEdgeConnectedComponents\
    \ {\n  ptr_t dfs_time = 0, edge_time = 1;\n\n  std::vector<bool> in_stack;\n \
    \ std::stack<ptr_t> stk;\n  std::vector<ptr_t> dfn, low;\n  std::vector<std::vector<std::pair<ptr_t,\
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
    \        tarjan(i, 0);\n  }\n};\n} // namespace weilycoder\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: weilycoder/graph/tarjan.hpp
  requiredBy: []
  timestamp: '2025-10-28 20:19:29+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/two_edge_connected_components.test.cpp
documentation_of: weilycoder/graph/tarjan.hpp
layout: document
redirect_from:
- /library/weilycoder/graph/tarjan.hpp
- /library/weilycoder/graph/tarjan.hpp.html
title: weilycoder/graph/tarjan.hpp
---
