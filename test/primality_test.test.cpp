#define PROBLEM "https://judge.yosupo.jp/problem/primality_test"

#include "../weilycoder/number-theory/prime.hpp"
#include <cstdint>
#include <iostream>
using namespace std;
using namespace weilycoder;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin.exceptions(cin.failbit | cin.badbit);
  size_t q;
  cin >> q;
  while (q--) {
    uint64_t n;
    cin >> n;
    cout << (is_prime(n) ? "Yes\n" : "No\n");
  }
  return 0;
}