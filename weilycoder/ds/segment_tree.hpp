#ifndef WEILYCODER_SEGMENT_TREE_HPP
#define WEILYCODER_SEGMENT_TREE_HPP

/**
 * @file segment_tree.hpp
 * @brief Segment Tree Data Structure
 */

#include <cstddef>
#include <limits>
#include <stdexcept>
#include <vector>

namespace weilycoder {
/**
 * @brief Segment Tree (point update and range query)
 * @tparam Monoid The monoid defining the operation and identity
 * @tparam ptr_t The type used for indexing (default: size_t)
 */
template <typename Monoid, typename ptr_t = size_t> struct SegmentTree {
  using T = typename Monoid::value_type;
  static constexpr ptr_t null = std::numeric_limits<ptr_t>::max();

  /**
   * @brief Node structure for the segment tree
   */
  struct Node {
    T value;
    ptr_t left, right;

    Node() : value(Monoid::identity()), left(null), right(null) {}
  };

private:
  ptr_t tl, tr;
  std::vector<Node> data;

  void pushup(size_t node) {
    data[node].value =
        Monoid::operation(data[data[node].left].value, data[data[node].right].value);
  }

  ptr_t build(ptr_t l, ptr_t r) {
    ptr_t node = data.size();
    data.emplace_back();

    if (r - l > 1) {
      ptr_t mid = l + ((r - l) >> 1);
      ptr_t left = build(l, mid), right = build(mid, r);
      data[node].left = left, data[node].right = right;
    }

    return node;
  }

  void init(ptr_t node, ptr_t l, ptr_t r, const std::vector<T> &arr) {
    if (r - l == 1)
      data[node].value = arr[l];
    else {
      ptr_t mid = l + ((r - l) >> 1);
      init(data[node].left, l, mid, arr);
      init(data[node].right, mid, r, arr);
      pushup(node);
    }
  }

  void point_set(ptr_t node, ptr_t l, ptr_t r, ptr_t pos, const T &val) {
    if (r - l == 1)
      data[node].value = val;
    else {
      ptr_t mid = l + ((r - l) >> 1);
      if (pos < mid)
        point_set(data[node].left, l, mid, pos, val);
      else
        point_set(data[node].right, mid, r, pos, val);
      pushup(node);
    }
  }

  void point_update(ptr_t node, ptr_t l, ptr_t r, ptr_t pos, const T &val) {
    if (r - l == 1)
      data[node].value = Monoid::operation(data[node].value, val);
    else {
      ptr_t mid = l + ((r - l) >> 1);
      if (pos < mid)
        point_update(data[node].left, l, mid, pos, val);
      else
        point_update(data[node].right, mid, r, pos, val);
      pushup(node);
    }
  }

  T point_query(ptr_t node, ptr_t l, ptr_t r, ptr_t pos) const {
    if (r - l == 1)
      return data[node].value;
    ptr_t mid = l + ((r - l) >> 1);
    if (pos < mid)
      return point_query(data[node].left, l, mid, pos);
    else
      return point_query(data[node].right, mid, r, pos);
  }

  T range_query(ptr_t node, ptr_t l, ptr_t r, ptr_t ql, ptr_t qr) const {
    if (ql >= r || qr <= l)
      return Monoid::identity();
    if (ql <= l && r <= qr)
      return data[node].value;
    ptr_t mid = l + ((r - l) >> 1);
    T left_res = range_query(data[node].left, l, mid, ql, qr);
    T right_res = range_query(data[node].right, mid, r, ql, qr);
    return Monoid::operation(left_res, right_res);
  }

public:
  /**
   * @brief Constructs a SegmentTree with given size
   * @param size The size of the array
   */
  explicit SegmentTree(ptr_t size) : tl(0), tr(size) { build(tl, tr); }

  /**
   * @brief Constructs a SegmentTree for the range [left, right)
   * @param left The left index (inclusive)
   * @param right The right index (exclusive)
   */
  explicit SegmentTree(ptr_t left, ptr_t right) : tl(left), tr(right) { build(tl, tr); }

  /**
   * @brief Constructs a SegmentTree from an initial array
   * @param arr Initial array of elements
   */
  explicit SegmentTree(const std::vector<T> &arr)
      : tl(0), tr(static_cast<ptr_t>(arr.size())) {
    build(tl, tr), init(0, tl, tr, arr);
  }

  /**
   * @brief Sets the value at position pos to val
   * @param pos The position to update
   * @param val The new value
   */
  void point_set(ptr_t pos, const T &val) {
    if (pos < tl || pos >= tr)
      throw std::out_of_range("SegmentTree::point_set: position out of range");
    point_set(0, tl, tr, pos, val);
  }

  /**
   * @brief Updates the value at position pos by applying the monoid operation with val
   * @param pos The position to update
   * @param val The value to combine
   */
  void point_update(ptr_t pos, const T &val) {
    if (pos < tl || pos >= tr)
      throw std::out_of_range("SegmentTree::point_update: position out of range");
    point_update(0, tl, tr, pos, val);
  }

  /**
   * @brief Queries the value at position pos
   * @param pos The position to query
   * @return The value at position pos
   */
  T point_query(ptr_t pos) const {
    if (pos < tl || pos >= tr)
      throw std::out_of_range("SegmentTree::point_query: position out of range");
    return point_query(0, tl, tr, pos);
  }

  /**
   * @brief Queries the range [left, right)
   * @param left The left index (inclusive)
   * @param right The right index (exclusive)
   * @return The result of the monoid operation over the range
   */
  T range_query(ptr_t left, ptr_t right) const {
    if (left < tl || right > tr || left > right)
      throw std::out_of_range("SegmentTree::range_query: range out of bounds");
    return range_query(0, tl, tr, left, right);
  }
};
} // namespace weilycoder

#endif
