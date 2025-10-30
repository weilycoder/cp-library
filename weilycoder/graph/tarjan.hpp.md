---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/biconnected_components.test.cpp
    title: test/biconnected_components.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/strongly_connected_components.test.cpp
    title: test/strongly_connected_components.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/two_edge_connected_components.test.cpp
    title: test/two_edge_connected_components.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Tarjan's Algorithm for Graph Connected Problems
    links: []
  bundledCode: "#line 1 \"weilycoder/graph/tarjan.hpp\"\n\n\n\n/**\n * @file tarjan.hpp\n\
    \ * @brief Tarjan's Algorithm for Graph Connected Problems\n */\n\n#include <algorithm>\n\
    #include <cstddef>\n#include <stack>\n#include <utility>\n#include <vector>\n\n\
    namespace weilycoder {\n/**\n * @brief Strongly Connected Components using Tarjan's\
    \ Algorithm\n * @tparam ptr_t Type for representing indices (default: size_t)\n\
    \ */\ntemplate <typename ptr_t = size_t> struct StrongConnectedComponents {\n\
    \  ptr_t dfs_time = 0;\n\n  std::vector<bool> in_stack;\n  std::stack<ptr_t> stk;\n\
    \  std::vector<ptr_t> dfn, low;\n  std::vector<std::vector<ptr_t>> graph;\n\n\
    \  std::vector<std::vector<ptr_t>> sccs;\n\n  /**\n   * @brief Constructs a StrongConnectedComponents\
    \ for n nodes\n   * @param n Number of nodes\n   */\n  StrongConnectedComponents(ptr_t\
    \ n)\n      : in_stack(n, false), dfn(n, 0), low(n, 0), graph(n) {}\n\n  /**\n\
    \   * @brief Adds a directed edge from u to v\n   * @param u Source node\n   *\
    \ @param v Destination node\n   */\n  void add_edge(ptr_t u, ptr_t v) { graph[u].push_back(v);\
    \ }\n\n  /**\n   * @brief Tarjan's DFS to find SCCs\n   * @param u Current node\n\
    \   */\n  void tarjan(ptr_t u) {\n    dfn[u] = low[u] = ++dfs_time;\n    stk.push(u),\
    \ in_stack[u] = true;\n\n    for (const auto &v : graph[u]) {\n      if (!dfn[v])\n\
    \        tarjan(v), low[u] = std::min(low[u], low[v]);\n      else if (in_stack[v])\n\
    \        low[u] = std::min(low[u], dfn[v]);\n    }\n\n    if (dfn[u] == low[u])\
    \ {\n      sccs.emplace_back();\n      sccs.back().push_back(u);\n      in_stack[u]\
    \ = false;\n      while (stk.top() != u)\n        sccs.back().push_back(stk.top()),\
    \ in_stack[stk.top()] = false,\n                                          stk.pop();\n\
    \      stk.pop();\n    }\n  }\n\n  /**\n   * @brief Solves for all SCCs in the\
    \ graph, sorting them in DFS order,\n   *      i.e., if there is an edge from\
    \ SCC A to SCC B, then A appears before B\n   */\n  void solve() {\n    for (size_t\
    \ i = 0; i < graph.size(); ++i)\n      if (!dfn[i])\n        tarjan(i);\n    std::reverse(sccs.begin(),\
    \ sccs.end());\n  }\n};\n\n/**\n * @brief Two-Edge Connected Components using\
    \ Tarjan's Algorithm\n * @tparam ptr_t Type for representing indices (default:\
    \ size_t)\n */\ntemplate <typename ptr_t = size_t> struct TwoEdgeConnectedComponents\
    \ {\n  ptr_t dfs_time = 0, edge_time = 1;\n\n  std::vector<bool> in_stack;\n \
    \ std::stack<ptr_t> stk;\n  std::vector<ptr_t> dfn, low;\n  std::vector<std::vector<std::pair<ptr_t,\
    \ ptr_t>>> graph;\n\n  std::vector<std::vector<ptr_t>> eccs;\n\n  /**\n   * @brief\
    \ Constructs a TwoEdgeConnectedComponents for n nodes\n   * @param n Number of\
    \ nodes\n   */\n  TwoEdgeConnectedComponents(ptr_t n)\n      : in_stack(n, false),\
    \ dfn(n, 0), low(n, 0), graph(n) {}\n\n  /**\n   * @brief Adds an undirected edge\
    \ between u and v\n   * @param u One endpoint\n   * @param v Other endpoint\n\
    \   */\n  void add_edge(ptr_t u, ptr_t v) {\n    graph[u].emplace_back(v, edge_time);\n\
    \    graph[v].emplace_back(u, edge_time);\n    edge_time++;\n  }\n\n  /**\n  \
    \ * @brief Tarjan's DFS to find 2-edge connected components\n   * @param u Current\
    \ node\n   * @param parent_edge Edge ID of the edge leading to u\n   */\n  void\
    \ tarjan(ptr_t u, ptr_t parent_edge) {\n    dfn[u] = low[u] = ++dfs_time;\n  \
    \  stk.push(u), in_stack[u] = true;\n\n    for (const auto &[v, edge_id] : graph[u])\
    \ {\n      if (edge_id == parent_edge)\n        continue;\n      if (!dfn[v])\n\
    \        tarjan(v, edge_id), low[u] = std::min(low[u], low[v]);\n      else if\
    \ (in_stack[v])\n        low[u] = std::min(low[u], dfn[v]);\n    }\n\n    if (dfn[u]\
    \ == low[u]) {\n      eccs.emplace_back();\n      eccs.back().push_back(u);\n\
    \      in_stack[u] = false;\n      while (stk.top() != u)\n        eccs.back().push_back(stk.top()),\
    \ in_stack[stk.top()] = false,\n                                          stk.pop();\n\
    \      stk.pop();\n    }\n  }\n\n  /**\n   * @brief Solves for all 2-edge connected\
    \ components in the graph\n   */\n  void solve() {\n    for (size_t i = 0; i <\
    \ graph.size(); ++i)\n      if (!dfn[i])\n        tarjan(i, 0);\n  }\n};\n\n/**\n\
    \ * @brief Biconnected Components using Tarjan's Algorithm\n * @tparam ptr_t Type\
    \ for representing indices (default: size_t)\n */\ntemplate <typename ptr_t =\
    \ size_t> struct BiconnectedComponents {\n  ptr_t dfs_time = 0;\n\n  std::stack<ptr_t>\
    \ stk;\n  std::vector<ptr_t> dfn, low;\n  std::vector<std::vector<ptr_t>> graph;\n\
    \n  std::vector<bool> is_cut;\n  std::vector<std::vector<ptr_t>> dccs;\n\n  /**\n\
    \   * @brief Constructs a BiconnectedComponents for n nodes\n   * @param n Number\
    \ of nodes\n   */\n  BiconnectedComponents(ptr_t n)\n      : dfn(n, 0), low(n,\
    \ 0), graph(n), is_cut(n, false) {}\n\n  /**\n   * @brief Adds an undirected edge\
    \ between u and v\n   * @param u One endpoint\n   * @param v Other endpoint\n\
    \   */\n  void add_edge(ptr_t u, ptr_t v) {\n    graph[u].push_back(v);\n    graph[v].push_back(u);\n\
    \  }\n\n  /**\n   * @brief Tarjan's DFS to find biconnected components\n   * @param\
    \ u Current node\n   * @param is_root Whether u is the root of the DFS tree\n\
    \   */\n  void tarjan(ptr_t u, bool is_root) {\n    dfn[u] = low[u] = ++dfs_time,\
    \ stk.push(u);\n\n    if (is_root && graph[u].empty()) {\n      dccs.emplace_back();\n\
    \      dccs.back().push_back(u);\n      return;\n    }\n\n    ptr_t child = 0;\n\
    \    for (const auto &v : graph[u]) {\n      if (!dfn[v]) {\n        tarjan(v,\
    \ false), low[u] = std::min(low[u], low[v]);\n        if (low[v] >= dfn[u]) {\n\
    \          if (++child > 1 || !is_root)\n            is_cut[u] = true;\n     \
    \     dccs.emplace_back();\n          do\n            dccs.back().push_back(stk.top()),\
    \ stk.pop();\n          while (dccs.back().back() != v);\n          dccs.back().push_back(u);\n\
    \        }\n      } else\n        low[u] = std::min(low[u], dfn[v]);\n    }\n\
    \  }\n\n  /**\n   * @brief Solves for all biconnected components in the graph\n\
    \   */\n  void solve() {\n    for (size_t i = 0; i < graph.size(); ++i)\n    \
    \  if (!dfn[i])\n        tarjan(i, true);\n  }\n};\n} // namespace weilycoder\n\
    \n\n"
  code: "#ifndef WEILYCODER_TARJAN_HPP\n#define WEILYCODER_TARJAN_HPP\n\n/**\n * @file\
    \ tarjan.hpp\n * @brief Tarjan's Algorithm for Graph Connected Problems\n */\n\
    \n#include <algorithm>\n#include <cstddef>\n#include <stack>\n#include <utility>\n\
    #include <vector>\n\nnamespace weilycoder {\n/**\n * @brief Strongly Connected\
    \ Components using Tarjan's Algorithm\n * @tparam ptr_t Type for representing\
    \ indices (default: size_t)\n */\ntemplate <typename ptr_t = size_t> struct StrongConnectedComponents\
    \ {\n  ptr_t dfs_time = 0;\n\n  std::vector<bool> in_stack;\n  std::stack<ptr_t>\
    \ stk;\n  std::vector<ptr_t> dfn, low;\n  std::vector<std::vector<ptr_t>> graph;\n\
    \n  std::vector<std::vector<ptr_t>> sccs;\n\n  /**\n   * @brief Constructs a StrongConnectedComponents\
    \ for n nodes\n   * @param n Number of nodes\n   */\n  StrongConnectedComponents(ptr_t\
    \ n)\n      : in_stack(n, false), dfn(n, 0), low(n, 0), graph(n) {}\n\n  /**\n\
    \   * @brief Adds a directed edge from u to v\n   * @param u Source node\n   *\
    \ @param v Destination node\n   */\n  void add_edge(ptr_t u, ptr_t v) { graph[u].push_back(v);\
    \ }\n\n  /**\n   * @brief Tarjan's DFS to find SCCs\n   * @param u Current node\n\
    \   */\n  void tarjan(ptr_t u) {\n    dfn[u] = low[u] = ++dfs_time;\n    stk.push(u),\
    \ in_stack[u] = true;\n\n    for (const auto &v : graph[u]) {\n      if (!dfn[v])\n\
    \        tarjan(v), low[u] = std::min(low[u], low[v]);\n      else if (in_stack[v])\n\
    \        low[u] = std::min(low[u], dfn[v]);\n    }\n\n    if (dfn[u] == low[u])\
    \ {\n      sccs.emplace_back();\n      sccs.back().push_back(u);\n      in_stack[u]\
    \ = false;\n      while (stk.top() != u)\n        sccs.back().push_back(stk.top()),\
    \ in_stack[stk.top()] = false,\n                                          stk.pop();\n\
    \      stk.pop();\n    }\n  }\n\n  /**\n   * @brief Solves for all SCCs in the\
    \ graph, sorting them in DFS order,\n   *      i.e., if there is an edge from\
    \ SCC A to SCC B, then A appears before B\n   */\n  void solve() {\n    for (size_t\
    \ i = 0; i < graph.size(); ++i)\n      if (!dfn[i])\n        tarjan(i);\n    std::reverse(sccs.begin(),\
    \ sccs.end());\n  }\n};\n\n/**\n * @brief Two-Edge Connected Components using\
    \ Tarjan's Algorithm\n * @tparam ptr_t Type for representing indices (default:\
    \ size_t)\n */\ntemplate <typename ptr_t = size_t> struct TwoEdgeConnectedComponents\
    \ {\n  ptr_t dfs_time = 0, edge_time = 1;\n\n  std::vector<bool> in_stack;\n \
    \ std::stack<ptr_t> stk;\n  std::vector<ptr_t> dfn, low;\n  std::vector<std::vector<std::pair<ptr_t,\
    \ ptr_t>>> graph;\n\n  std::vector<std::vector<ptr_t>> eccs;\n\n  /**\n   * @brief\
    \ Constructs a TwoEdgeConnectedComponents for n nodes\n   * @param n Number of\
    \ nodes\n   */\n  TwoEdgeConnectedComponents(ptr_t n)\n      : in_stack(n, false),\
    \ dfn(n, 0), low(n, 0), graph(n) {}\n\n  /**\n   * @brief Adds an undirected edge\
    \ between u and v\n   * @param u One endpoint\n   * @param v Other endpoint\n\
    \   */\n  void add_edge(ptr_t u, ptr_t v) {\n    graph[u].emplace_back(v, edge_time);\n\
    \    graph[v].emplace_back(u, edge_time);\n    edge_time++;\n  }\n\n  /**\n  \
    \ * @brief Tarjan's DFS to find 2-edge connected components\n   * @param u Current\
    \ node\n   * @param parent_edge Edge ID of the edge leading to u\n   */\n  void\
    \ tarjan(ptr_t u, ptr_t parent_edge) {\n    dfn[u] = low[u] = ++dfs_time;\n  \
    \  stk.push(u), in_stack[u] = true;\n\n    for (const auto &[v, edge_id] : graph[u])\
    \ {\n      if (edge_id == parent_edge)\n        continue;\n      if (!dfn[v])\n\
    \        tarjan(v, edge_id), low[u] = std::min(low[u], low[v]);\n      else if\
    \ (in_stack[v])\n        low[u] = std::min(low[u], dfn[v]);\n    }\n\n    if (dfn[u]\
    \ == low[u]) {\n      eccs.emplace_back();\n      eccs.back().push_back(u);\n\
    \      in_stack[u] = false;\n      while (stk.top() != u)\n        eccs.back().push_back(stk.top()),\
    \ in_stack[stk.top()] = false,\n                                          stk.pop();\n\
    \      stk.pop();\n    }\n  }\n\n  /**\n   * @brief Solves for all 2-edge connected\
    \ components in the graph\n   */\n  void solve() {\n    for (size_t i = 0; i <\
    \ graph.size(); ++i)\n      if (!dfn[i])\n        tarjan(i, 0);\n  }\n};\n\n/**\n\
    \ * @brief Biconnected Components using Tarjan's Algorithm\n * @tparam ptr_t Type\
    \ for representing indices (default: size_t)\n */\ntemplate <typename ptr_t =\
    \ size_t> struct BiconnectedComponents {\n  ptr_t dfs_time = 0;\n\n  std::stack<ptr_t>\
    \ stk;\n  std::vector<ptr_t> dfn, low;\n  std::vector<std::vector<ptr_t>> graph;\n\
    \n  std::vector<bool> is_cut;\n  std::vector<std::vector<ptr_t>> dccs;\n\n  /**\n\
    \   * @brief Constructs a BiconnectedComponents for n nodes\n   * @param n Number\
    \ of nodes\n   */\n  BiconnectedComponents(ptr_t n)\n      : dfn(n, 0), low(n,\
    \ 0), graph(n), is_cut(n, false) {}\n\n  /**\n   * @brief Adds an undirected edge\
    \ between u and v\n   * @param u One endpoint\n   * @param v Other endpoint\n\
    \   */\n  void add_edge(ptr_t u, ptr_t v) {\n    graph[u].push_back(v);\n    graph[v].push_back(u);\n\
    \  }\n\n  /**\n   * @brief Tarjan's DFS to find biconnected components\n   * @param\
    \ u Current node\n   * @param is_root Whether u is the root of the DFS tree\n\
    \   */\n  void tarjan(ptr_t u, bool is_root) {\n    dfn[u] = low[u] = ++dfs_time,\
    \ stk.push(u);\n\n    if (is_root && graph[u].empty()) {\n      dccs.emplace_back();\n\
    \      dccs.back().push_back(u);\n      return;\n    }\n\n    ptr_t child = 0;\n\
    \    for (const auto &v : graph[u]) {\n      if (!dfn[v]) {\n        tarjan(v,\
    \ false), low[u] = std::min(low[u], low[v]);\n        if (low[v] >= dfn[u]) {\n\
    \          if (++child > 1 || !is_root)\n            is_cut[u] = true;\n     \
    \     dccs.emplace_back();\n          do\n            dccs.back().push_back(stk.top()),\
    \ stk.pop();\n          while (dccs.back().back() != v);\n          dccs.back().push_back(u);\n\
    \        }\n      } else\n        low[u] = std::min(low[u], dfn[v]);\n    }\n\
    \  }\n\n  /**\n   * @brief Solves for all biconnected components in the graph\n\
    \   */\n  void solve() {\n    for (size_t i = 0; i < graph.size(); ++i)\n    \
    \  if (!dfn[i])\n        tarjan(i, true);\n  }\n};\n} // namespace weilycoder\n\
    \n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: weilycoder/graph/tarjan.hpp
  requiredBy: []
  timestamp: '2025-10-30 21:08:13+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/two_edge_connected_components.test.cpp
  - test/biconnected_components.test.cpp
  - test/strongly_connected_components.test.cpp
documentation_of: weilycoder/graph/tarjan.hpp
layout: document
redirect_from:
- /library/weilycoder/graph/tarjan.hpp
- /library/weilycoder/graph/tarjan.hpp.html
title: Tarjan's Algorithm for Graph Connected Problems
---
