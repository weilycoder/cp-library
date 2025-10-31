#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include "../weilycoder/ds/segment_tree.hpp"
#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;
using namespace weilycoder;

static constexpr uint64_t mod = 998244353;

struct AffineMonoid {
  using value_type = pair<uint64_t, uint64_t>; // (a, b) represents f(x) = a * x + b

  static value_type identity() { return {1, 0}; }
  static value_type operation(const value_type &f, const value_type &g) {
    return {(g.first * f.first) % mod, (g.first * f.second + g.second) % mod};
  }

  static uint64_t affine(const value_type &f, uint64_t x) {
    return (f.first * x + f.second) % mod;
  }
};

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin.exceptions(cin.badbit | cin.failbit);
  size_t n, q;
  cin >> n >> q;

  vector<pair<uint64_t, uint64_t>> affines;
  affines.reserve(n);
  for (size_t i = 0; i < n; ++i) {
    uint64_t a, b;
    cin >> a >> b;
    affines.emplace_back(a, b);
  }

  SegmentTree<AffineMonoid> sgt(affines);
  while (q--) {
    size_t op;
    cin >> op;
    if (op == 0) {
      size_t p;
      uint64_t c, d;
      cin >> p >> c >> d;
      sgt.point_set(p, {c, d});
    } else {
      size_t l, r;
      uint64_t x;
      cin >> l >> r >> x;
      auto func = sgt.range_query(l, r);
      cout << AffineMonoid::affine(func, x) << '\n';
    }
  }
  return 0;
}