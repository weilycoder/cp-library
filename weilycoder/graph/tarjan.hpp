#ifndef WEILYCODER_TARJAN_HPP
#define WEILYCODER_TARJAN_HPP

#include <cstddef>
#include <stack>
#include <utility>
#include <vector>

namespace weilycoder {
template <typename ptr_t = size_t> struct TwoEdgeConnectedComponents {
  ptr_t dfs_time = 0, edge_time = 1;

  std::vector<bool> in_stack;
  std::stack<ptr_t> stk;
  std::vector<ptr_t> dfn, low;
  std::vector<std::vector<std::pair<ptr_t, ptr_t>>> graph;

  std::vector<std::vector<ptr_t>> eccs;

  TwoEdgeConnectedComponents(ptr_t n)
      : in_stack(n, false), dfn(n, 0), low(n, 0), graph(n) {}

  void add_edge(ptr_t u, ptr_t v) {
    graph[u].emplace_back(v, edge_time);
    graph[v].emplace_back(u, edge_time);
    edge_time++;
  }

  void tarjan(ptr_t u, ptr_t parent_edge) {
    dfn[u] = low[u] = ++dfs_time;
    stk.push(u);
    in_stack[u] = true;

    for (const auto &[v, edge_id] : graph[u]) {
      if (edge_id == parent_edge)
        continue;
      if (!dfn[v])
        tarjan(v, edge_id), low[u] = std::min(low[u], low[v]);
      else if (in_stack[v])
        low[u] = std::min(low[u], dfn[v]);
    }

    if (dfn[u] == low[u]) {
      eccs.emplace_back();
      eccs.back().push_back(u);
      in_stack[u] = false;
      while (stk.top() != u)
        eccs.back().push_back(stk.top()), in_stack[stk.top()] = false, stk.pop();
      stk.pop();
    }
  }

  void solve() {
    for (size_t i = 0; i < graph.size(); ++i)
      if (!dfn[i])
        tarjan(i, 0);
  }
};
} // namespace weilycoder

#endif
