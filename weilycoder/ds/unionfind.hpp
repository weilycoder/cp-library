#ifndef WEILYCODER_UNIONFIND_HPP
#define WEILYCODER_UNIONFIND_HPP

#include <algorithm>
#include <numeric>
#include <vector>

namespace weilycoder {
template <typename ptr_t = size_t> struct UnionFind {
  std::vector<ptr_t> parent, size;

  UnionFind(ptr_t n) : parent(n), size(n, 1) {
    std::iota(parent.begin(), parent.end(), 0);
  }

  ptr_t getf(ptr_t x) {
    while (x != parent[x])
      x = parent[x] = parent[parent[x]];
    return x;
  }

  bool unite(ptr_t x, ptr_t y) {
    x = getf(x), y = getf(y);
    if (x == y)
      return false;
    if (size[x] < size[y])
      std::swap(x, y);
    parent[y] = x, size[x] += size[y];
    return true;
  }
};
} // namespace weilycoder

#endif
