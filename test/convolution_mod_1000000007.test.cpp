#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../weilycoder/poly/mtt_convolve.hpp"
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
  for (auto &x : a)
    cin >> x;
  for (auto &x : b)
    cin >> x;

  auto c = mtt3_convolve<1000000007, 167772161, 469762049, 754974721>(a, b);
  for (size_t i = 0; i < n + m - 1; ++i)
    cout << c[i] << " \n"[i + 1 == n + m - 1];
  return 0;
}
