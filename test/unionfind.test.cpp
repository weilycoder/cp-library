#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include "weilycoder/unionfind.hpp"
#include <iostream>
using namespace std;
using namespace weilycoder;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin.exceptions(cin.failbit | cin.badbit);
  size_t n, q;
  cin >> n >> q;
  UnionFind uf(n);
  for (size_t _ = 0; _ < q; ++_) {
    size_t op, x, y;
    cin >> op >> x >> y;
    switch (op) {
    case 0:
      uf.unite(x, y);
      break;
    case 1:
      cout << (uf.getf(x) == uf.getf(y) ? "1\n" : "0\n");
      break;
    }
  }
  return 0;
}