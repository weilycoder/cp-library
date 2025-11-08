#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series"

#include "../weilycoder/number_theory/mod_utility.hpp"
#include "../weilycoder/poly/elementary_func/inverse.hpp"
#include "../weilycoder/poly/ntt_convolve.hpp"
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
  auto r = ntt_poly_inv<998244353>(a, n);
  for (size_t i = 0; i < n; ++i)
    cout << r[i] << " \n"[i + 1 == n];
  return 0;
}