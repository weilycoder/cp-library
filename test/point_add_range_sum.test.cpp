#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "../weilycoder/ds/point_add_range_sum.hpp"
#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;
using namespace weilycoder;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin.exceptions(cin.failbit | cin.badbit);
  size_t n, q;
  cin >> n >> q;

  vector<uint64_t> initial(n, 0);
  for (size_t i = 0; i < n; ++i)
    cin >> initial[i];

  PointAddRangeSum<AddGroup<uint64_t>> pasr(initial);
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      size_t i, x;
      cin >> i >> x;
      pasr.point_add(i, x);
    } else {
      size_t l, r;
      cin >> l >> r;
      cout << pasr.range_sum(l, r) << '\n';
    }
  }
  return 0;
}