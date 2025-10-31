#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include "../weilycoder/ds/offline_static_range_query.hpp"
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

  vector<uint32_t> datas(n);
  for (auto &x : datas)
    cin >> x;

  OfflineStaticRangeQuery<NumberMinMonoid<uint32_t>> osrq(n);
  for (size_t i = 0; i < q; ++i) {
    size_t l, r;
    cin >> l >> r;
    osrq.add_query(l, r);
  }

  for (const auto &res : osrq.process(datas))
    cout << res << '\n';
  return 0;
}