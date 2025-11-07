#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../weilycoder/poly/ntt_convolve.hpp"
#include <iostream>
#include <vector>
using namespace std;
using namespace weilycoder;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin.exceptions(cin.failbit | cin.badbit);
  size_t n, m;
  cin >> n >> m;
  vector<uint64_t> a(n), b(m);
  for (size_t i = 0; i < n; ++i)
    cin >> a[i];
  for (size_t i = 0; i < m; ++i)
    cin >> b[i];
  auto c = ntt_convolve<998244353>(a, b);
  for (size_t i = 0; i < n + m - 1; ++i)
    cout << c[i] << " \n"[i + 1 == n + m - 1];
  return 0;
}