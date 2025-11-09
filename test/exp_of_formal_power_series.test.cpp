#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series"

#include "../weilycoder/poly/elementary_func/exponential.hpp"
#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;
using namespace weilycoder;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin.exceptions(cin.failbit | cin.badbit);
  size_t n;
  cin >> n;

  vector<uint64_t> a(n);
  for (size_t i = 0; i < n; ++i)
    cin >> a[i];

  auto res = ntt_exponential<998244353>(a, n);
  for (size_t i = 0; i < n; ++i)
    cout << res[i] << " \n"[i + 1 == n];
  return 0;
}