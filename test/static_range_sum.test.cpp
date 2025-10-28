#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"

#include "../weilycoder/data-struct/static_range_sum.hpp"
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

  vector<uint64_t> arr(n);
  for (size_t i = 0; i < n; ++i)
    cin >> arr[i];

  StaticRangeSum<uint64_t> sum(arr);
  while (q--) {
    size_t l, r;
    cin >> l >> r;
    cout << sum.query(l, r) << '\n';
  }
  return 0;
}