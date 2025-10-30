#ifndef WEILYCODER_TARJAN_HPP
#define WEILYCODER_TARJAN_HPP

/**
 * @file tarjan.hpp
 * @brief Tarjan's Algorithm for Graph Connected Problems
 */

#include <algorithm>
#include <cstddef>
#include <stack>
#include <utility>
#include <vector>

namespace weilycoder {
/**
 * @brief Strongly Connected Components using Tarjan's Algorithm
 * @tparam ptr_t Type for representing indices (default: size_t)
 */
template <typename ptr_t = size_t> struct StrongConnectedComponents {
  ptr_t dfs_time = 0;

  std::vector<bool> in_stack;
  std::stack<ptr_t> stk;
  std::vector<ptr_t> dfn, low;
  std::vector<std::vector<ptr_t>> graph;

  std::vector<std::vector<ptr_t>> sccs;

  /**
   * @brief Constructs a StrongConnectedComponents for n nodes
   * @param n Number of nodes
   */
  StrongConnectedComponents(ptr_t n)
      : in_stack(n, false), dfn(n, 0), low(n, 0), graph(n) {}

  /**
   * @brief Adds a directed edge from u to v
   * @param u Source node
   * @param v Destination node
   */
  void add_edge(ptr_t u, ptr_t v) { graph[u].push_back(v); }

  /**
   * @brief Tarjan's DFS to find SCCs
   * @param u Current node
   */
  void tarjan(ptr_t u) {
    dfn[u] = low[u] = ++dfs_time;
    stk.push(u), in_stack[u] = true;

    for (const auto &v : graph[u]) {
      if (!dfn[v])
        tarjan(v), low[u] = std::min(low[u], low[v]);
      else if (in_stack[v])
        low[u] = std::min(low[u], dfn[v]);
    }

    if (dfn[u] == low[u]) {
      sccs.emplace_back();
      sccs.back().push_back(u);
      in_stack[u] = false;
      while (stk.top() != u)
        sccs.back().push_back(stk.top()), in_stack[stk.top()] = false,
                                          stk.pop();
      stk.pop();
    }
  }

  /**
   * @brief Solves for all SCCs in the graph, sorting them in DFS order,
   *      i.e., if there is an edge from SCC A to SCC B, then A appears before B
   */
  void solve() {
    for (size_t i = 0; i < graph.size(); ++i)
      if (!dfn[i])
        tarjan(i);
    std::reverse(sccs.begin(), sccs.end());
  }
};

/**
 * @brief Two-Edge Connected Components using Tarjan's Algorithm
 * @tparam ptr_t Type for representing indices (default: size_t)
 */
template <typename ptr_t = size_t> struct TwoEdgeConnectedComponents {
  ptr_t dfs_time = 0, edge_time = 1;

  std::vector<bool> in_stack;
  std::stack<ptr_t> stk;
  std::vector<ptr_t> dfn, low;
  std::vector<std::vector<std::pair<ptr_t, ptr_t>>> graph;

  std::vector<std::vector<ptr_t>> eccs;

  /**
   * @brief Constructs a TwoEdgeConnectedComponents for n nodes
   * @param n Number of nodes
   */
  TwoEdgeConnectedComponents(ptr_t n)
      : in_stack(n, false), dfn(n, 0), low(n, 0), graph(n) {}

  /**
   * @brief Adds an undirected edge between u and v
   * @param u One endpoint
   * @param v Other endpoint
   */
  void add_edge(ptr_t u, ptr_t v) {
    graph[u].emplace_back(v, edge_time);
    graph[v].emplace_back(u, edge_time);
    edge_time++;
  }

  /**
   * @brief Tarjan's DFS to find 2-edge connected components
   * @param u Current node
   * @param parent_edge Edge ID of the edge leading to u
   */
  void tarjan(ptr_t u, ptr_t parent_edge) {
    dfn[u] = low[u] = ++dfs_time;
    stk.push(u), in_stack[u] = true;

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
        eccs.back().push_back(stk.top()), in_stack[stk.top()] = false,
                                          stk.pop();
      stk.pop();
    }
  }

  /**
   * @brief Solves for all 2-edge connected components in the graph
   */
  void solve() {
    for (size_t i = 0; i < graph.size(); ++i)
      if (!dfn[i])
        tarjan(i, 0);
  }
};

/**
 * @brief Biconnected Components using Tarjan's Algorithm
 * @tparam ptr_t Type for representing indices (default: size_t)
 */
template <typename ptr_t = size_t> struct BiconnectedComponents {
  ptr_t dfs_time = 0;

  std::stack<ptr_t> stk;
  std::vector<ptr_t> dfn, low;
  std::vector<std::vector<ptr_t>> graph;

  std::vector<bool> is_cut;
  std::vector<std::vector<ptr_t>> dccs;

  /**
   * @brief Constructs a BiconnectedComponents for n nodes
   * @param n Number of nodes
   */
  BiconnectedComponents(ptr_t n)
      : dfn(n, 0), low(n, 0), graph(n), is_cut(n, false) {}

  /**
   * @brief Adds an undirected edge between u and v
   * @param u One endpoint
   * @param v Other endpoint
   */
  void add_edge(ptr_t u, ptr_t v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  /**
   * @brief Tarjan's DFS to find biconnected components
   * @param u Current node
   * @param is_root Whether u is the root of the DFS tree
   */
  void tarjan(ptr_t u, bool is_root) {
    dfn[u] = low[u] = ++dfs_time, stk.push(u);

    if (is_root && graph[u].empty()) {
      dccs.emplace_back();
      dccs.back().push_back(u);
      return;
    }

    ptr_t child = 0;
    for (const auto &v : graph[u]) {
      if (!dfn[v]) {
        tarjan(v, false), low[u] = std::min(low[u], low[v]);
        if (low[v] >= dfn[u]) {
          if (++child > 1 || !is_root)
            is_cut[u] = true;
          dccs.emplace_back();
          do
            dccs.back().push_back(stk.top()), stk.pop();
          while (dccs.back().back() != v);
          dccs.back().push_back(u);
        }
      } else
        low[u] = std::min(low[u], dfn[v]);
    }
  }

  /**
   * @brief Solves for all biconnected components in the graph
   */
  void solve() {
    for (size_t i = 0; i < graph.size(); ++i)
      if (!dfn[i])
        tarjan(i, true);
  }
};
} // namespace weilycoder

#endif
