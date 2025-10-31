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
    if (n <= UINT32_MAX)
      cout << (miller_rabin32(n) ? "Yes\n" : "No\n");
    else
      cout << (miller_rabin64(n) ? "Yes\n" : "No\n");
  }
  return 0;
}