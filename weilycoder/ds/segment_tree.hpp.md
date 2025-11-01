---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/point_set_range_composite.test.cpp
    title: test/point_set_range_composite.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Segment Tree Data Structure
    links: []
  bundledCode: "#line 1 \"weilycoder/ds/segment_tree.hpp\"\n\n\n\n/**\n * @file segment_tree.hpp\n\
    \ * @brief Segment Tree Data Structure\n */\n\n#include <cstddef>\n#include <limits>\n\
    #include <stdexcept>\n#include <vector>\n\nnamespace weilycoder {\n/**\n * @brief\
    \ Segment Tree (point update and range query)\n * @tparam Monoid The monoid defining\
    \ the operation and identity\n * @tparam ptr_t The type used for indexing (default:\
    \ size_t)\n */\ntemplate <typename Monoid, typename ptr_t = size_t> struct SegmentTree\
    \ {\n  using T = typename Monoid::value_type;\n  static constexpr ptr_t null =\
    \ std::numeric_limits<ptr_t>::max();\n\n  /**\n   * @brief Node structure for\
    \ the segment tree\n   */\n  struct Node {\n    T value;\n    ptr_t left, right;\n\
    \n    Node() : value(Monoid::identity()), left(null), right(null) {}\n  };\n\n\
    private:\n  ptr_t tl, tr;\n  std::vector<Node> data;\n\n  void pushup(size_t node)\
    \ {\n    data[node].value =\n        Monoid::operation(data[data[node].left].value,\
    \ data[data[node].right].value);\n  }\n\n  ptr_t init(ptr_t l, ptr_t r) {\n  \
    \  ptr_t node = data.size();\n    data.emplace_back();\n\n    if (r - l > 1) {\n\
    \      ptr_t mid = l + ((r - l) >> 1);\n      ptr_t left = init(l, mid), right\
    \ = init(mid, r);\n      data[node].left = left, data[node].right = right;\n \
    \   }\n\n    return node;\n  }\n\n  ptr_t init(ptr_t l, ptr_t r, const std::vector<T>\
    \ &arr) {\n    ptr_t node = data.size();\n    data.emplace_back();\n\n    if (r\
    \ - l == 1)\n      data[node].value = arr[l];\n    else {\n      ptr_t mid = l\
    \ + ((r - l) >> 1);\n      ptr_t left = init(l, mid, arr);\n      ptr_t right\
    \ = init(mid, r, arr);\n      data[node].left = left, data[node].right = right;\n\
    \      pushup(node);\n    }\n\n    return node;\n  }\n\n  void build(ptr_t l,\
    \ ptr_t r) {\n    if (r - l > 0) {\n      data.reserve((r - l) * 2 - 1);\n   \
    \   init(l, r);\n    }\n  }\n\n  void build(const std::vector<T> &arr) {\n   \
    \ if (!arr.empty()) {\n      data.reserve(arr.size() * 2 - 1);\n      init(0,\
    \ arr.size(), arr);\n    }\n  }\n\n  void point_set(ptr_t node, ptr_t l, ptr_t\
    \ r, ptr_t pos, const T &val) {\n    if (r - l == 1)\n      data[node].value =\
    \ val;\n    else {\n      ptr_t mid = l + ((r - l) >> 1);\n      if (pos < mid)\n\
    \        point_set(data[node].left, l, mid, pos, val);\n      else\n        point_set(data[node].right,\
    \ mid, r, pos, val);\n      pushup(node);\n    }\n  }\n\n  void point_update(ptr_t\
    \ node, ptr_t l, ptr_t r, ptr_t pos, const T &val) {\n    if (r - l == 1)\n  \
    \    data[node].value = Monoid::operation(data[node].value, val);\n    else {\n\
    \      ptr_t mid = l + ((r - l) >> 1);\n      if (pos < mid)\n        point_update(data[node].left,\
    \ l, mid, pos, val);\n      else\n        point_update(data[node].right, mid,\
    \ r, pos, val);\n      pushup(node);\n    }\n  }\n\n  T point_query(ptr_t node,\
    \ ptr_t l, ptr_t r, ptr_t pos) const {\n    if (r - l == 1)\n      return data[node].value;\n\
    \    ptr_t mid = l + ((r - l) >> 1);\n    if (pos < mid)\n      return point_query(data[node].left,\
    \ l, mid, pos);\n    else\n      return point_query(data[node].right, mid, r,\
    \ pos);\n  }\n\n  T range_query(ptr_t node, ptr_t l, ptr_t r, ptr_t ql, ptr_t\
    \ qr) const {\n    if (ql >= r || qr <= l)\n      return Monoid::identity();\n\
    \    if (ql <= l && r <= qr)\n      return data[node].value;\n    ptr_t mid =\
    \ l + ((r - l) >> 1);\n    T left_res = range_query(data[node].left, l, mid, ql,\
    \ qr);\n    T right_res = range_query(data[node].right, mid, r, ql, qr);\n   \
    \ return Monoid::operation(left_res, right_res);\n  }\n\npublic:\n  /**\n   *\
    \ @brief Constructs a SegmentTree with given size\n   * @param size The size of\
    \ the array\n   */\n  explicit SegmentTree(ptr_t size) : tl(0), tr(size) { build(tl,\
    \ tr); }\n\n  /**\n   * @brief Constructs a SegmentTree for the range [left, right)\n\
    \   * @param left The left index (inclusive)\n   * @param right The right index\
    \ (exclusive)\n   */\n  explicit SegmentTree(ptr_t left, ptr_t right) : tl(left),\
    \ tr(right) { build(tl, tr); }\n\n  /**\n   * @brief Constructs a SegmentTree\
    \ from an initial array\n   * @param arr Initial array of elements\n   */\n  explicit\
    \ SegmentTree(const std::vector<T> &arr)\n      : tl(0), tr(static_cast<ptr_t>(arr.size()))\
    \ {\n    build(arr);\n  }\n\n  /**\n   * @brief Sets the value at position pos\
    \ to val\n   * @param pos The position to update\n   * @param val The new value\n\
    \   */\n  void point_set(ptr_t pos, const T &val) {\n    if (pos < tl || pos >=\
    \ tr)\n      throw std::out_of_range(\"SegmentTree::point_set: position out of\
    \ range\");\n    point_set(0, tl, tr, pos, val);\n  }\n\n  /**\n   * @brief Updates\
    \ the value at position pos by applying the monoid operation with val\n   * @param\
    \ pos The position to update\n   * @param val The value to combine\n   */\n  void\
    \ point_update(ptr_t pos, const T &val) {\n    if (pos < tl || pos >= tr)\n  \
    \    throw std::out_of_range(\"SegmentTree::point_update: position out of range\"\
    );\n    point_update(0, tl, tr, pos, val);\n  }\n\n  /**\n   * @brief Queries\
    \ the value at position pos\n   * @param pos The position to query\n   * @return\
    \ The value at position pos\n   */\n  T point_query(ptr_t pos) const {\n    if\
    \ (pos < tl || pos >= tr)\n      throw std::out_of_range(\"SegmentTree::point_query:\
    \ position out of range\");\n    return point_query(0, tl, tr, pos);\n  }\n\n\
    \  /**\n   * @brief Queries the range [left, right)\n   * @param left The left\
    \ index (inclusive)\n   * @param right The right index (exclusive)\n   * @return\
    \ The result of the monoid operation over the range\n   */\n  T range_query(ptr_t\
    \ left, ptr_t right) const {\n    if (left < tl || right > tr || left > right)\n\
    \      throw std::out_of_range(\"SegmentTree::range_query: range out of bounds\"\
    );\n    return range_query(0, tl, tr, left, right);\n  }\n\n  ptr_t left() const\
    \ { return tl; }\n  ptr_t right() const { return tr; }\n};\n} // namespace weilycoder\n\
    \n\n"
  code: "#ifndef WEILYCODER_SEGMENT_TREE_HPP\n#define WEILYCODER_SEGMENT_TREE_HPP\n\
    \n/**\n * @file segment_tree.hpp\n * @brief Segment Tree Data Structure\n */\n\
    \n#include <cstddef>\n#include <limits>\n#include <stdexcept>\n#include <vector>\n\
    \nnamespace weilycoder {\n/**\n * @brief Segment Tree (point update and range\
    \ query)\n * @tparam Monoid The monoid defining the operation and identity\n *\
    \ @tparam ptr_t The type used for indexing (default: size_t)\n */\ntemplate <typename\
    \ Monoid, typename ptr_t = size_t> struct SegmentTree {\n  using T = typename\
    \ Monoid::value_type;\n  static constexpr ptr_t null = std::numeric_limits<ptr_t>::max();\n\
    \n  /**\n   * @brief Node structure for the segment tree\n   */\n  struct Node\
    \ {\n    T value;\n    ptr_t left, right;\n\n    Node() : value(Monoid::identity()),\
    \ left(null), right(null) {}\n  };\n\nprivate:\n  ptr_t tl, tr;\n  std::vector<Node>\
    \ data;\n\n  void pushup(size_t node) {\n    data[node].value =\n        Monoid::operation(data[data[node].left].value,\
    \ data[data[node].right].value);\n  }\n\n  ptr_t init(ptr_t l, ptr_t r) {\n  \
    \  ptr_t node = data.size();\n    data.emplace_back();\n\n    if (r - l > 1) {\n\
    \      ptr_t mid = l + ((r - l) >> 1);\n      ptr_t left = init(l, mid), right\
    \ = init(mid, r);\n      data[node].left = left, data[node].right = right;\n \
    \   }\n\n    return node;\n  }\n\n  ptr_t init(ptr_t l, ptr_t r, const std::vector<T>\
    \ &arr) {\n    ptr_t node = data.size();\n    data.emplace_back();\n\n    if (r\
    \ - l == 1)\n      data[node].value = arr[l];\n    else {\n      ptr_t mid = l\
    \ + ((r - l) >> 1);\n      ptr_t left = init(l, mid, arr);\n      ptr_t right\
    \ = init(mid, r, arr);\n      data[node].left = left, data[node].right = right;\n\
    \      pushup(node);\n    }\n\n    return node;\n  }\n\n  void build(ptr_t l,\
    \ ptr_t r) {\n    if (r - l > 0) {\n      data.reserve((r - l) * 2 - 1);\n   \
    \   init(l, r);\n    }\n  }\n\n  void build(const std::vector<T> &arr) {\n   \
    \ if (!arr.empty()) {\n      data.reserve(arr.size() * 2 - 1);\n      init(0,\
    \ arr.size(), arr);\n    }\n  }\n\n  void point_set(ptr_t node, ptr_t l, ptr_t\
    \ r, ptr_t pos, const T &val) {\n    if (r - l == 1)\n      data[node].value =\
    \ val;\n    else {\n      ptr_t mid = l + ((r - l) >> 1);\n      if (pos < mid)\n\
    \        point_set(data[node].left, l, mid, pos, val);\n      else\n        point_set(data[node].right,\
    \ mid, r, pos, val);\n      pushup(node);\n    }\n  }\n\n  void point_update(ptr_t\
    \ node, ptr_t l, ptr_t r, ptr_t pos, const T &val) {\n    if (r - l == 1)\n  \
    \    data[node].value = Monoid::operation(data[node].value, val);\n    else {\n\
    \      ptr_t mid = l + ((r - l) >> 1);\n      if (pos < mid)\n        point_update(data[node].left,\
    \ l, mid, pos, val);\n      else\n        point_update(data[node].right, mid,\
    \ r, pos, val);\n      pushup(node);\n    }\n  }\n\n  T point_query(ptr_t node,\
    \ ptr_t l, ptr_t r, ptr_t pos) const {\n    if (r - l == 1)\n      return data[node].value;\n\
    \    ptr_t mid = l + ((r - l) >> 1);\n    if (pos < mid)\n      return point_query(data[node].left,\
    \ l, mid, pos);\n    else\n      return point_query(data[node].right, mid, r,\
    \ pos);\n  }\n\n  T range_query(ptr_t node, ptr_t l, ptr_t r, ptr_t ql, ptr_t\
    \ qr) const {\n    if (ql >= r || qr <= l)\n      return Monoid::identity();\n\
    \    if (ql <= l && r <= qr)\n      return data[node].value;\n    ptr_t mid =\
    \ l + ((r - l) >> 1);\n    T left_res = range_query(data[node].left, l, mid, ql,\
    \ qr);\n    T right_res = range_query(data[node].right, mid, r, ql, qr);\n   \
    \ return Monoid::operation(left_res, right_res);\n  }\n\npublic:\n  /**\n   *\
    \ @brief Constructs a SegmentTree with given size\n   * @param size The size of\
    \ the array\n   */\n  explicit SegmentTree(ptr_t size) : tl(0), tr(size) { build(tl,\
    \ tr); }\n\n  /**\n   * @brief Constructs a SegmentTree for the range [left, right)\n\
    \   * @param left The left index (inclusive)\n   * @param right The right index\
    \ (exclusive)\n   */\n  explicit SegmentTree(ptr_t left, ptr_t right) : tl(left),\
    \ tr(right) { build(tl, tr); }\n\n  /**\n   * @brief Constructs a SegmentTree\
    \ from an initial array\n   * @param arr Initial array of elements\n   */\n  explicit\
    \ SegmentTree(const std::vector<T> &arr)\n      : tl(0), tr(static_cast<ptr_t>(arr.size()))\
    \ {\n    build(arr);\n  }\n\n  /**\n   * @brief Sets the value at position pos\
    \ to val\n   * @param pos The position to update\n   * @param val The new value\n\
    \   */\n  void point_set(ptr_t pos, const T &val) {\n    if (pos < tl || pos >=\
    \ tr)\n      throw std::out_of_range(\"SegmentTree::point_set: position out of\
    \ range\");\n    point_set(0, tl, tr, pos, val);\n  }\n\n  /**\n   * @brief Updates\
    \ the value at position pos by applying the monoid operation with val\n   * @param\
    \ pos The position to update\n   * @param val The value to combine\n   */\n  void\
    \ point_update(ptr_t pos, const T &val) {\n    if (pos < tl || pos >= tr)\n  \
    \    throw std::out_of_range(\"SegmentTree::point_update: position out of range\"\
    );\n    point_update(0, tl, tr, pos, val);\n  }\n\n  /**\n   * @brief Queries\
    \ the value at position pos\n   * @param pos The position to query\n   * @return\
    \ The value at position pos\n   */\n  T point_query(ptr_t pos) const {\n    if\
    \ (pos < tl || pos >= tr)\n      throw std::out_of_range(\"SegmentTree::point_query:\
    \ position out of range\");\n    return point_query(0, tl, tr, pos);\n  }\n\n\
    \  /**\n   * @brief Queries the range [left, right)\n   * @param left The left\
    \ index (inclusive)\n   * @param right The right index (exclusive)\n   * @return\
    \ The result of the monoid operation over the range\n   */\n  T range_query(ptr_t\
    \ left, ptr_t right) const {\n    if (left < tl || right > tr || left > right)\n\
    \      throw std::out_of_range(\"SegmentTree::range_query: range out of bounds\"\
    );\n    return range_query(0, tl, tr, left, right);\n  }\n\n  ptr_t left() const\
    \ { return tl; }\n  ptr_t right() const { return tr; }\n};\n} // namespace weilycoder\n\
    \n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: weilycoder/ds/segment_tree.hpp
  requiredBy: []
  timestamp: '2025-11-01 07:16:21+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/point_set_range_composite.test.cpp
documentation_of: weilycoder/ds/segment_tree.hpp
layout: document
redirect_from:
- /library/weilycoder/ds/segment_tree.hpp
- /library/weilycoder/ds/segment_tree.hpp.html
title: Segment Tree Data Structure
---
