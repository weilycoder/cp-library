#ifndef WEILYCODER_UNIONFIND_HPP
#define WEILYCODER_UNIONFIND_HPP

#include <algorithm>
#include <numeric>
#include <vector>

namespace weilycoder {
/**
 * @brief Union-Find (Disjoint Set Union) Data Structure
 * @tparam ptr_t Type for representing indices (default: size_t)
 */
template <typename ptr_t = size_t> struct UnionFind {
private:
  std::vector<ptr_t> parent, setSize;

public:
  /**
   * @brief Constructs a UnionFind with n elements, each in its own set
   * @param n Number of elements
   */
  UnionFind(ptr_t n) : parent(n), setSize(n, 1) {
    std::iota(parent.begin(), parent.end(), 0);
  }

  /**
   * @brief Returns the number of elements
   * @return Number of elements
   */
  size_t size() const { return parent.size(); }

  /**
   * @brief Returns the size of the set containing x
   * @param x Element to query
   * @return Size of the set containing x
   */
  size_t get_size(ptr_t x) { return setSize[getf(x)]; }

  /**
   * @brief Finds the representative of the set containing x
   * @param x Element to find
   * @return Representative of the set containing x
   */
  ptr_t getf(ptr_t x) {
    while (x != parent[x])
      x = parent[x] = parent[parent[x]];
    return x;
  }

  /**
   * @brief Unites the sets containing x and y
   * @param x First element
   * @param y Second element
   * @return True if the sets were separate and have been united, false if they
   *         were already in the same set
   */
  bool unite(ptr_t x, ptr_t y) {
    x = getf(x), y = getf(y);
    if (x == y)
      return false;
    if (setSize[x] < setSize[y])
      std::swap(x, y);
    parent[y] = x, setSize[x] += setSize[y];
    return true;
  }
};
} // namespace weilycoder

#endif
