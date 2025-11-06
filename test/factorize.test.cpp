#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

#include "../weilycoder/number-theory/factorize.hpp"
#include <iostream>
using namespace std;
using namespace weilycoder;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin.exceptions(cin.failbit | cin.badbit);
  size_t t;
  cin >> t;
  while (t--) {
    uint64_t x;
    cin >> x;
    auto primes = factorize<>(x);
    cout << primes.size();
    for (auto p : primes)
      cout << ' ' << p;
    cout << '\n';
  }
  return 0;
}