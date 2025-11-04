#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_2_64"

#include "../weilycoder/poly/karatsuba.hpp"
#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;
using namespace weilycoder;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin.exceptions(cin.badbit | cin.failbit);
  size_t n, m;
  cin >> n >> m;

  vector<uint64_t> a(n), b(m);
  for (size_t i = 0; i < n; ++i)
    cin >> a[i];
  for (size_t j = 0; j < m; ++j)
    cin >> b[j];

  auto c = karatsuba_multiply(a, b);
  for (size_t k = 0; k < n + m - 1; ++k)
    cout << c[k] << (k + 1 == n + m - 1 ? '\n' : ' ');
  return 0;
}