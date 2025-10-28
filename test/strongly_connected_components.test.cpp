#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include "../weilycoder/graph/tarjan.hpp"
#include <iostream>
using namespace std;
using namespace weilycoder;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin.exceptions(cin.failbit | cin.badbit);
  size_t n, m;
  cin >> n >> m;

  StrongConnectedComponents graph(n);
  for (size_t i = 0; i < m; ++i) {
    size_t u, v;
    cin >> u >> v;
    graph.add_edge(u, v);
  }

  graph.solve();

  cout << graph.sccs.size() << '\n';
  for (const auto &ecc : graph.sccs) {
    cout << ecc.size();
    for (size_t u : ecc)
      cout << ' ' << u;
    cout << '\n';
  }
  return 0;
}
