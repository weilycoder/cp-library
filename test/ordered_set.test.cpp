#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"

#include "../weilycoder/ds/treap.hpp"
#include <iostream>
using namespace std;
using namespace weilycoder;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin.exceptions(cin.failbit | cin.badbit);
  size_t n, q;
  cin >> n >> q;

  Treap<uint32_t> treap;
  treap.reserve(n + q);
  size_t root = Treap<uint32_t>::null;

  for (size_t i = 0; i < n; ++i) {
    uint32_t x;
    cin >> x;
    root = treap.insert(root, x);
  }

  while (q--) {
    uint32_t o, x;
    cin >> o >> x;
    switch (o) {
    case 0:
      root = treap.insert_unique(root, x).first;
      break;
    case 1:
      root = treap.erase_value(root, x);
      break;
    case 2:
      if (x > treap.node_size(root))
        cout << -1 << '\n';
      else {
        size_t node = treap.get_by_size(root, x - 1);
        cout << treap.node_value(node) << '\n';
      }
      break;
    case 3:
      cout << treap.get_rank<std::less_equal<uint32_t>>(root, x) << '\n';
      break;
    case 4: {
      size_t node = treap.get_less(root, x);
      if (node == Treap<uint32_t>::null)
        cout << -1 << '\n';
      else
        cout << treap.node_value(node) << '\n';
      break;
    }
    case 5: {
      size_t node = treap.get_greater(root, x);
      if (node == Treap<uint32_t>::null)
        cout << -1 << '\n';
      else
        cout << treap.node_value(node) << '\n';
      break;
    }
    }
  }
  return 0;
}