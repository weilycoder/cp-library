#define PROBLEM "https://judge.yosupo.jp/problem/primitive_root"

#include "../weilycoder/number_theory/primitive_root.hpp"
#include <iostream>
using namespace std;
using namespace weilycoder;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin.exceptions(cin.failbit | cin.badbit);
  size_t t;
  cin >> t;
  while (t--) {
    uint64_t p;
    cin >> p;
    cout << prime_primitive_root<>(p) << '\n';
  }
  return 0;
}