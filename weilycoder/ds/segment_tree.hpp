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
template <typename _Monoid, typename _ptr_t = size_t> struct SegmentTreeHeapSon {
protected:
  using T = typename _Monoid::value_type;
  using ptr_t = _ptr_t;
  using Monoid = _Monoid;
  static constexpr ptr_t null = std::numeric_limits<ptr_t>::max();

private:
  ptr_t st, ed;
  std::vector<T> data;

  void init(ptr_t node, ptr_t l, ptr_t r, const std::vector<T> &arr) {
    if (r - l == 1) {
      data[node] = arr[l];
    } else {
      ptr_t mid = l + ((r - l) >> 1);
      init(node * 2 + 1, l, mid, arr), init(node * 2 + 2, mid, r, arr);
      pushup(node);
    }
  }

protected:
  ptr_t get_st() const { return st; }
  ptr_t get_ed() const { return ed; }

  T &get_value(ptr_t node) { return data[node]; }
  const T &get_value(ptr_t node) const { return data[node]; }

  ptr_t get_lc(ptr_t node) const { return node * 2 + 1; }
  ptr_t get_rc(ptr_t node) const { return node * 2 + 2; }

  void pushdown(ptr_t node) const {}
  void pushup(ptr_t node) {
    data[node] = Monoid::operation(data[get_lc(node)], data[get_rc(node)]);
  }

  explicit SegmentTreeHeapSon(ptr_t size) : st(0), ed(size) {
    data.resize(size * 4, Monoid::identity());
  }

  explicit SegmentTreeHeapSon(ptr_t st, ptr_t ed) : st(st), ed(ed) {
    data.resize((ed - st) * 4, Monoid::identity());
  }

  explicit SegmentTreeHeapSon(const std::vector<T> &arr)
      : st(0), ed(static_cast<ptr_t>(arr.size())) {
    data.resize(arr.size() * 4, Monoid::identity());
    init(0, st, ed, arr);
  }
};

/**
 * @brief Segment Tree Base Class that stores child pointers
 * @tparam _Monoid The monoid defining the operation and identity
 * @tparam _ptr_t The pointer type used for indexing nodes (default: size_t)
 */
template <typename _Monoid, typename _ptr_t = size_t> struct SegmentTreeStoreSon {
protected:
  using T = typename _Monoid::value_type;
  using ptr_t = _ptr_t;
  using Monoid = _Monoid;
  static constexpr ptr_t null = std::numeric_limits<ptr_t>::max();

private:
  struct Node {
    T value;
    ptr_t left, right;

    Node() : value(Monoid::identity()), left(null), right(null) {}
  };

  ptr_t st, ed;
  std::vector<Node> data;

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

  ptr_t init(ptr_t l, ptr_t r, const std::vector<T> &arr) {
    ptr_t node = data.size();
    data.emplace_back();
    if (r - l == 1) {
      data[node].value = arr[l];
    } else {
      ptr_t mid = l + ((r - l) >> 1);
      ptr_t left = init(l, mid, arr), right = init(mid, r, arr);
      data[node].left = left, data[node].right = right;
      pushup(node);
    }
    return node;
  }

protected:
  ptr_t get_st() const { return st; }
  ptr_t get_ed() const { return ed; }

  T &get_value(ptr_t node) { return data[node].value; }
  const T &get_value(ptr_t node) const { return data[node].value; }

  ptr_t get_lc(ptr_t node) const { return data[node].left; }
  ptr_t get_rc(ptr_t node) const { return data[node].right; }

  void pushdown(ptr_t node) const {}
  void pushup(ptr_t node) {
    data[node].value =
        Monoid::operation(data[data[node].left].value, data[data[node].right].value);
  }

  explicit SegmentTreeStoreSon(ptr_t size) : st(0), ed(size) {
    data.reserve(size * 2 - 1);
    build(st, ed);
  }

  explicit SegmentTreeStoreSon(ptr_t st, ptr_t ed) : st(st), ed(ed) {
    data.reserve((ed - st) * 2 - 1);
    build(st, ed);
  }

  explicit SegmentTreeStoreSon(const std::vector<T> &arr)
      : st(0), ed(static_cast<ptr_t>(arr.size())) {
    data.reserve(arr.size() * 2 - 1);
    init(0, arr.size(), arr);
  }
};

template <class SegmentBase> struct SegmentTree : private SegmentBase {
  using Monoid = typename SegmentBase::Monoid;
  using ptr_t = typename SegmentBase::ptr_t;
  using T = typename Monoid::value_type;
  static constexpr ptr_t null = SegmentBase::null;

private:
  void point_set(ptr_t node, ptr_t l, ptr_t r, ptr_t pos, const T &val) {
    if (r - l == 1)
      SegmentBase::get_value(node) = val;
    else {
      ptr_t mid = l + ((r - l) >> 1);
      if (pos < mid)
        point_set(SegmentBase::get_lc(node), l, mid, pos, val);
      else
        point_set(SegmentBase::get_rc(node), mid, r, pos, val);
      SegmentBase::pushup(node);
    }
  }

  void point_update(ptr_t node, ptr_t l, ptr_t r, ptr_t pos, const T &val) {
    if (r - l == 1)
      SegmentBase::get_value(node) =
          Monoid::operation(SegmentBase::get_value(node), val);
    else {
      ptr_t mid = l + ((r - l) >> 1);
      if (pos < mid)
        point_update(SegmentBase::get_lc(node), l, mid, pos, val);
      else
        point_update(SegmentBase::get_rc(node), mid, r, pos, val);
      SegmentBase::pushup(node);
    }
  }

  T point_query(ptr_t node, ptr_t l, ptr_t r, ptr_t pos) const {
    if (r - l == 1)
      return SegmentBase::get_value(node);
    ptr_t mid = l + ((r - l) >> 1);
    if (pos < mid)
      return point_query(SegmentBase::get_lc(node), l, mid, pos);
    else
      return point_query(SegmentBase::get_rc(node), mid, r, pos);
  }

  T range_query(ptr_t node, ptr_t l, ptr_t r, ptr_t ql, ptr_t qr) const {
    if (ql >= r || qr <= l)
      return Monoid::identity();
    if (ql <= l && r <= qr)
      return SegmentBase::get_value(node);
    ptr_t mid = l + ((r - l) >> 1);
    T left_res = range_query(SegmentBase::get_lc(node), l, mid, ql, qr);
    T right_res = range_query(SegmentBase::get_rc(node), mid, r, ql, qr);
    return Monoid::operation(left_res, right_res);
  }

public:
  /**
   * @brief Constructs a SegmentTree with given size
   * @param size The size of the array
   */
  explicit SegmentTree(ptr_t size) : SegmentBase(size) {}

  /**
   * @brief Constructs a SegmentTree for the range [left, right)
   * @param left The left index (inclusive)
   * @param right The right index (exclusive)
   */
  explicit SegmentTree(ptr_t left, ptr_t right) : SegmentBase(left, right) {}

  /**
   * @brief Constructs a SegmentTree from an initial array
   * @param arr Initial array of elements
   */
  explicit SegmentTree(const std::vector<T> &arr) : SegmentBase(arr) {}

  /**
   * @brief Sets the value at position pos to val
   * @param pos The position to update
   * @param val The new value
   */
  void point_set(ptr_t pos, const T &val) {
    if (pos < get_st() || pos >= get_ed())
      throw std::out_of_range("SegmentTree::point_set: position out of range");
    point_set(0, get_st(), get_ed(), pos, val);
  }

  /**
   * @brief Updates the value at position pos by applying the monoid operation with val
   * @param pos The position to update
   * @param val The value to combine
   */
  void point_update(ptr_t pos, const T &val) {
    if (pos < get_st() || pos >= get_ed())
      throw std::out_of_range("SegmentTree::point_update: position out of range");
    point_update(0, get_st(), get_ed(), pos, val);
  }

  /**
   * @brief Queries the value at position pos
   * @param pos The position to query
   * @return The value at position pos
   */
  T point_query(ptr_t pos) const {
    if (pos < get_st() || pos >= get_ed())
      throw std::out_of_range("SegmentTree::point_query: position out of range");
    return point_query(0, get_st(), get_ed(), pos);
  }

  /**
   * @brief Queries the range [left, right)
   * @param left The left index (inclusive)
   * @param right The right index (exclusive)
   * @return The result of the monoid operation over the range
   */
  T range_query(ptr_t left, ptr_t right) const {
    if (left < get_st() || right > get_ed() || left > right)
      throw std::out_of_range("SegmentTree::range_query: range out of bounds");
    return range_query(0, get_st(), get_ed(), left, right);
  }

  ptr_t get_st() const { return SegmentBase::get_st(); }
  ptr_t get_ed() const { return SegmentBase::get_ed(); }
};
} // namespace weilycoder

#endif
