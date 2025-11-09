#ifndef WEILY_CODER_DS_TREAP_HPP
#define WEILY_CODER_DS_TREAP_HPP

#include "../random.hpp"
#include <functional>
#include <limits>
#include <tuple>
#include <utility>
#include <vector>

namespace weilycoder {
struct treap_base {
private:
  static inline uint32_t rand32 = 0;

protected:
  static uint32_t get_rand() { return lcg_nr(rand32); }

public:
  static constexpr size_t null = std::numeric_limits<size_t>::max();
};

template <typename T> struct Treap : public treap_base {
private:
  struct node {
    T value;
    uint32_t priority;
    size_t size, left, right;
    node(const T &value)
        : value(value), priority(get_rand()), size(1u), left(null), right(null) {}
  };

  std::vector<size_t> free_list;
  std::vector<node> nodes;

  void pushup(size_t p) {
    if (p != null)
      nodes[p].size = node_size(nodes[p].left) + node_size(nodes[p].right) + 1;
  }

public:
  Treap() = default;

  /**
   * @brief Reserve space for n nodes in the treap.
   * @param n The number of nodes to reserve space for.
   */
  void reserve(size_t n) { nodes.reserve(n); }

  /**
   * @brief Create a new node with the given value and add it to the treap.
   * @param value The value of the new node.
   * @return The index of the new node.
   */
  size_t new_node(const T &value) {
    if (free_list.empty()) {
      nodes.emplace_back(value);
      return nodes.size() - 1;
    } else {
      size_t p = free_list.back();
      free_list.pop_back();
      nodes[p] = node(value);
      return p;
    }
  }

  /**
   * @brief Get the size of the subtree rooted at node p.
   * @param p The index of the node.
   * @return The size of the subtree.
   */
  size_t node_size(size_t p) const { return p == null ? 0 : nodes[p].size; }

  /**
   * @brief Get the value of node p.
   * @param p The index of the node.
   * @return The value of the node.
   */
  T &node_value(size_t p) { return nodes[p].value; }

  /**
   * @brief Get the value of node p (const version).
   * @param p The index of the node.
   * @return The value of the node.
   */
  const T &node_value(size_t p) const { return nodes[p].value; }

  /**
   * @brief Split the treap into two treaps: left treap with first k elements,
   *        right treap with the rest.
   * @param p The root of the treap to split.
   * @param k The number of elements in the left treap.
   * @return A pair of roots of the left and right treaps.
   */
  std::pair<size_t, size_t> size_split2(size_t p, size_t k) {
    if (p == null)
      return {null, null};
    if (k == 0)
      return {null, p};
    if (node_size(p) <= k)
      return {p, null};
    if (node_size(nodes[p].left) >= k) {
      auto [l, r] = size_split2(nodes[p].left, k);
      nodes[p].left = r, pushup(p);
      return {l, p};
    } else {
      auto [l, r] = size_split2(nodes[p].right, k - node_size(nodes[p].left) - 1);
      nodes[p].right = l, pushup(p);
      return {p, r};
    }
  }

  /**
   * @brief Split the treap into three treaps: left treap with first k - 1 elements,
   *        middle treap with the k-th element, right treap with the rest.
   * @param p The root of the treap to split.
   * @param k The position of the middle element.
   * @return A tuple of roots of the left, middle, and right treaps.
   */
  std::tuple<size_t, size_t, size_t> size_split3(size_t p, size_t k) {
    if (p == null)
      return {null, null, null};
    if (node_size(p) < k)
      return {p, null, null};
    if (node_size(nodes[p].left) == k) {
      size_t left = nodes[p].left;
      size_t right = nodes[p].right;
      nodes[p].size = 1u;
      nodes[p].left = nodes[p].right = null;
      return {left, p, right};
    } else if (node_size(nodes[p].left) > k) {
      auto [l, m, r] = size_split3(nodes[p].left, k);
      nodes[p].left = r, pushup(p);
      return {l, m, p};
    } else {
      auto [l, m, r] = size_split3(nodes[p].right, k - node_size(nodes[p].left) - 1);
      nodes[p].right = l, pushup(p);
      return {p, m, r};
    }
  }

  /**
   * @brief Split the treap into two treaps based on a value:
   *        left treap with values less than the given value,
   *        right treap with values greater than or equal to the given value.
   * @tparam Compare The comparison functor type (default is `std::less<T>`).
   * @param p The root of the treap to split.
   * @param value The value to split the treap by.
   * @return A pair of roots of the left and right treaps.
   */
  template <typename Compare = std::less<T>>
  std::pair<size_t, size_t> lower_split(size_t p, const T &value) {
    constexpr Compare less;
    if (p == null)
      return {null, null};
    if (less(nodes[p].value, value)) {
      // Value at p is less than the given value, go right
      auto [l, r] = lower_split(nodes[p].right, value);
      nodes[p].right = l, pushup(p);
      return {p, r};
    } else {
      // Value at p is greater than or equal to the given value, go left
      auto [l, r] = lower_split(nodes[p].left, value);
      nodes[p].left = r, pushup(p);
      return {l, p};
    }
  }

  /**
   * @brief Split the treap into two treaps based on a value:
   *        left treap with values less than or equal to the given value,
   *        right treap with values greater than the given value.
   * @tparam Compare The comparison functor type (default is `std::less<T>`).
   * @param p The root of the treap to split.
   * @param value The value to split the treap by.
   * @return A pair of roots of the left and right treaps.
   */
  template <typename Compare = std::less<T>>
  std::pair<size_t, size_t> upper_split(size_t p, const T &value) {
    constexpr Compare less;
    if (p == null)
      return {null, null};
    if (less(value, nodes[p].value)) {
      // Value at p is greater than the given value, go left
      auto [l, r] = upper_split(nodes[p].left, value);
      nodes[p].left = r, pushup(p);
      return {l, p};
    } else {
      // Value at p is less than or equal to the given value, go right
      auto [l, r] = upper_split(nodes[p].right, value);
      nodes[p].right = l, pushup(p);
      return {p, r};
    }
  }

  /**
   * @brief Split the treap into three treaps based on a value:
   *        left treap with values less than or equal to the given value,
   *        middle treap with values equal to the given value (at most one node),
   *        right treap with values greater than or equal to the given value.
   * @tparam Compare The comparison functor type (default is `std::less<T>`).
   * @param p The root of the treap to split.
   * @param value The value to split the treap by.
   * @return A tuple of roots of the left, middle, and right treaps.
   * @note If want to split all equal values into the middle treap,
   *       use `lower_split` and `upper_split` instead.
   */
  template <typename Compare = std::less<T>>
  std::tuple<size_t, size_t, size_t> value_split(size_t p, const T &value) {
    constexpr Compare less;
    if (p == null)
      return {null, null, null};
    if (less(nodes[p].value, value)) {
      // Value at p is less than the given value, go right
      auto [l, m, r] = value_split(nodes[p].right, value);
      nodes[p].right = l, pushup(p);
      return {p, m, r};
    } else if (less(value, nodes[p].value)) {
      // Value at p is greater than the given value, go left
      auto [l, m, r] = value_split(nodes[p].left, value);
      nodes[p].left = r, pushup(p);
      return {l, m, p};
    } else {
      size_t left = nodes[p].left;
      size_t right = nodes[p].right;
      nodes[p].size = 1u;
      nodes[p].left = nodes[p].right = null;
      return {left, p, right};
    }
  }

  /**
   * @brief Merge two treaps into one.
   * @param left The root of the left treap.
   * @param right The root of the right treap.
   * @return The root of the merged treap.
   */
  size_t merge(size_t left, size_t right) {
    if (left == null || right == null)
      return left == null ? right : left;
    if (nodes[left].priority > nodes[right].priority) {
      nodes[left].right = merge(nodes[left].right, right);
      return pushup(left), left;
    } else {
      nodes[right].left = merge(left, nodes[right].left);
      return pushup(right), right;
    }
  }

  /**
   * @brief Insert a value at a given position in the treap.
   * @param root The root of the treap.
   * @param pos The position to insert the value at.
   * @param value The value to insert.
   * @return The new root of the treap after insertion.
   */
  size_t insert(size_t root, size_t pos, const T &value) {
    auto [left, right] = size_split2(root, pos);
    size_t newnode = new_node(value);
    return merge(merge(left, newnode), right);
  }

  /**
   * @brief Erase the node at a given position in the treap.
   * @param root The root of the treap.
   * @param pos The position of the node to erase.
   * @return The new root of the treap after erasure.
   */
  size_t erase(size_t root, size_t pos) {
    auto [left, mid, right] = size_split3(root, pos);
    free_list.push_back(mid);
    return merge(left, right);
  }

  /**
   * @brief Apply a function to all nodes in the treap in-order.
   * @tparam Func The function type.
   * @param p The root of the treap.
   * @param func The function to apply to each node index.
   */
  template <typename Func> void work_nodes(size_t p, Func func) const {
    if (p == null)
      return;
    work_nodes(nodes[p].left, func);
    func(p);
    work_nodes(nodes[p].right, func);
  }

  /**
   * @brief Get all node indices in the treap in-order.
   * @param p The root of the treap.
   * @return A vector of node indices in in-order.
   */
  std::vector<size_t> get_nodes(size_t p) const {
    std::vector<size_t> res;
    work_nodes(p, [&](size_t node) { res.push_back(node); });
    return res;
  }
};
} // namespace weilycoder

#endif
