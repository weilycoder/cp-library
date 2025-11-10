---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: weilycoder/ds/segment_tree.hpp
    title: Segment Tree Data Structure
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_set_range_composite
    links:
    - https://judge.yosupo.jp/problem/point_set_range_composite
  bundledCode: "#line 1 \"test/point_set_range_composite2.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/point_set_range_composite\"\n\n#line 1 \"\
    weilycoder/ds/segment_tree.hpp\"\n\n\n\n/**\n * @file segment_tree.hpp\n * @brief\
    \ Segment Tree Data Structure\n */\n\n#include <cstddef>\n#include <limits>\n\
    #include <stdexcept>\n#include <vector>\n\nnamespace weilycoder {\n/**\n * @brief\
    \ Segment Tree Base Class that uses heap indexing for child nodes\n * @tparam\
    \ _Monoid The monoid defining the operation and identity\n * @tparam _ptr_t The\
    \ pointer type used for indexing nodes (default: size_t)\n */\ntemplate <typename\
    \ _Monoid, typename _ptr_t = size_t> struct SegmentTreeHeapSon {\nprotected:\n\
    \  using T = typename _Monoid::value_type;\n  using ptr_t = _ptr_t;\n  using Monoid\
    \ = _Monoid;\n  static constexpr ptr_t null = std::numeric_limits<ptr_t>::max();\n\
    \nprivate:\n  ptr_t st, ed;\n  std::vector<T> data;\n\n  void init(ptr_t node,\
    \ ptr_t l, ptr_t r, const std::vector<T> &arr) {\n    if (r - l == 1) {\n    \
    \  data[node] = arr[l];\n    } else {\n      ptr_t mid = l + ((r - l) >> 1);\n\
    \      init(node * 2 + 1, l, mid, arr), init(node * 2 + 2, mid, r, arr);\n   \
    \   pushup(node);\n    }\n  }\n\nprotected:\n  ptr_t get_st() const { return st;\
    \ }\n  ptr_t get_ed() const { return ed; }\n\n  T &get_value(ptr_t node) { return\
    \ data[node]; }\n  const T &get_value(ptr_t node) const { return data[node]; }\n\
    \n  ptr_t get_lc(ptr_t node) const { return node * 2 + 1; }\n  ptr_t get_rc(ptr_t\
    \ node) const { return node * 2 + 2; }\n\n  void pushdown(ptr_t node) const {}\n\
    \  void pushup(ptr_t node) {\n    data[node] = Monoid::operation(data[get_lc(node)],\
    \ data[get_rc(node)]);\n  }\n\n  explicit SegmentTreeHeapSon(ptr_t size) : st(0),\
    \ ed(size) {\n    data.resize(size * 4, Monoid::identity());\n  }\n\n  explicit\
    \ SegmentTreeHeapSon(ptr_t st, ptr_t ed) : st(st), ed(ed) {\n    data.resize((ed\
    \ - st) * 4, Monoid::identity());\n  }\n\n  explicit SegmentTreeHeapSon(const\
    \ std::vector<T> &arr)\n      : st(0), ed(static_cast<ptr_t>(arr.size())) {\n\
    \    data.resize(arr.size() * 4, Monoid::identity());\n    init(0, st, ed, arr);\n\
    \  }\n};\n\n/**\n * @brief Segment Tree Base Class that stores child pointers\n\
    \ * @tparam _Monoid The monoid defining the operation and identity\n * @tparam\
    \ _ptr_t The pointer type used for indexing nodes (default: size_t)\n */\ntemplate\
    \ <typename _Monoid, typename _ptr_t = size_t> struct SegmentTreeStoreSon {\n\
    protected:\n  using T = typename _Monoid::value_type;\n  using ptr_t = _ptr_t;\n\
    \  using Monoid = _Monoid;\n  static constexpr ptr_t null = std::numeric_limits<ptr_t>::max();\n\
    \nprivate:\n  struct Node {\n    T value;\n    ptr_t left, right;\n\n    Node()\
    \ : value(Monoid::identity()), left(null), right(null) {}\n  };\n\n  ptr_t st,\
    \ ed;\n  std::vector<Node> data;\n\n  ptr_t build(ptr_t l, ptr_t r) {\n    ptr_t\
    \ node = data.size();\n    data.emplace_back();\n    if (r - l > 1) {\n      ptr_t\
    \ mid = l + ((r - l) >> 1);\n      ptr_t left = build(l, mid), right = build(mid,\
    \ r);\n      data[node].left = left, data[node].right = right;\n    }\n    return\
    \ node;\n  }\n\n  ptr_t init(ptr_t l, ptr_t r, const std::vector<T> &arr) {\n\
    \    ptr_t node = data.size();\n    data.emplace_back();\n    if (r - l == 1)\
    \ {\n      data[node].value = arr[l];\n    } else {\n      ptr_t mid = l + ((r\
    \ - l) >> 1);\n      ptr_t left = init(l, mid, arr), right = init(mid, r, arr);\n\
    \      data[node].left = left, data[node].right = right;\n      pushup(node);\n\
    \    }\n    return node;\n  }\n\nprotected:\n  ptr_t get_st() const { return st;\
    \ }\n  ptr_t get_ed() const { return ed; }\n\n  T &get_value(ptr_t node) { return\
    \ data[node].value; }\n  const T &get_value(ptr_t node) const { return data[node].value;\
    \ }\n\n  ptr_t get_lc(ptr_t node) const { return data[node].left; }\n  ptr_t get_rc(ptr_t\
    \ node) const { return data[node].right; }\n\n  void pushdown(ptr_t node) const\
    \ {}\n  void pushup(ptr_t node) {\n    data[node].value =\n        Monoid::operation(data[data[node].left].value,\
    \ data[data[node].right].value);\n  }\n\n  explicit SegmentTreeStoreSon(ptr_t\
    \ size) : st(0), ed(size) {\n    data.reserve(size * 2 - 1);\n    build(st, ed);\n\
    \  }\n\n  explicit SegmentTreeStoreSon(ptr_t st, ptr_t ed) : st(st), ed(ed) {\n\
    \    data.reserve((ed - st) * 2 - 1);\n    build(st, ed);\n  }\n\n  explicit SegmentTreeStoreSon(const\
    \ std::vector<T> &arr)\n      : st(0), ed(static_cast<ptr_t>(arr.size())) {\n\
    \    data.reserve(arr.size() * 2 - 1);\n    init(0, arr.size(), arr);\n  }\n};\n\
    \ntemplate <class SegmentBase> struct SegmentTree : private SegmentBase {\n  using\
    \ Monoid = typename SegmentBase::Monoid;\n  using ptr_t = typename SegmentBase::ptr_t;\n\
    \  using T = typename Monoid::value_type;\n  static constexpr ptr_t null = SegmentBase::null;\n\
    \nprivate:\n  void point_set(ptr_t node, ptr_t l, ptr_t r, ptr_t pos, const T\
    \ &val) {\n    if (r - l == 1)\n      SegmentBase::get_value(node) = val;\n  \
    \  else {\n      ptr_t mid = l + ((r - l) >> 1);\n      if (pos < mid)\n     \
    \   point_set(SegmentBase::get_lc(node), l, mid, pos, val);\n      else\n    \
    \    point_set(SegmentBase::get_rc(node), mid, r, pos, val);\n      SegmentBase::pushup(node);\n\
    \    }\n  }\n\n  void point_update(ptr_t node, ptr_t l, ptr_t r, ptr_t pos, const\
    \ T &val) {\n    if (r - l == 1)\n      SegmentBase::get_value(node) =\n     \
    \     Monoid::operation(SegmentBase::get_value(node), val);\n    else {\n    \
    \  ptr_t mid = l + ((r - l) >> 1);\n      if (pos < mid)\n        point_update(SegmentBase::get_lc(node),\
    \ l, mid, pos, val);\n      else\n        point_update(SegmentBase::get_rc(node),\
    \ mid, r, pos, val);\n      SegmentBase::pushup(node);\n    }\n  }\n\n  T point_query(ptr_t\
    \ node, ptr_t l, ptr_t r, ptr_t pos) const {\n    if (r - l == 1)\n      return\
    \ SegmentBase::get_value(node);\n    ptr_t mid = l + ((r - l) >> 1);\n    if (pos\
    \ < mid)\n      return point_query(SegmentBase::get_lc(node), l, mid, pos);\n\
    \    else\n      return point_query(SegmentBase::get_rc(node), mid, r, pos);\n\
    \  }\n\n  T range_query(ptr_t node, ptr_t l, ptr_t r, ptr_t ql, ptr_t qr) const\
    \ {\n    if (ql >= r || qr <= l)\n      return Monoid::identity();\n    if (ql\
    \ <= l && r <= qr)\n      return SegmentBase::get_value(node);\n    ptr_t mid\
    \ = l + ((r - l) >> 1);\n    T left_res = range_query(SegmentBase::get_lc(node),\
    \ l, mid, ql, qr);\n    T right_res = range_query(SegmentBase::get_rc(node), mid,\
    \ r, ql, qr);\n    return Monoid::operation(left_res, right_res);\n  }\n\npublic:\n\
    \  /**\n   * @brief Constructs a SegmentTree with given size\n   * @param size\
    \ The size of the array\n   */\n  explicit SegmentTree(ptr_t size) : SegmentBase(size)\
    \ {}\n\n  /**\n   * @brief Constructs a SegmentTree for the range [left, right)\n\
    \   * @param left The left index (inclusive)\n   * @param right The right index\
    \ (exclusive)\n   */\n  explicit SegmentTree(ptr_t left, ptr_t right) : SegmentBase(left,\
    \ right) {}\n\n  /**\n   * @brief Constructs a SegmentTree from an initial array\n\
    \   * @param arr Initial array of elements\n   */\n  explicit SegmentTree(const\
    \ std::vector<T> &arr) : SegmentBase(arr) {}\n\n  /**\n   * @brief Sets the value\
    \ at position pos to val\n   * @param pos The position to update\n   * @param\
    \ val The new value\n   */\n  void point_set(ptr_t pos, const T &val) {\n    if\
    \ (pos < get_st() || pos >= get_ed())\n      throw std::out_of_range(\"SegmentTree::point_set:\
    \ position out of range\");\n    point_set(0, get_st(), get_ed(), pos, val);\n\
    \  }\n\n  /**\n   * @brief Updates the value at position pos by applying the monoid\
    \ operation with val\n   * @param pos The position to update\n   * @param val\
    \ The value to combine\n   */\n  void point_update(ptr_t pos, const T &val) {\n\
    \    if (pos < get_st() || pos >= get_ed())\n      throw std::out_of_range(\"\
    SegmentTree::point_update: position out of range\");\n    point_update(0, get_st(),\
    \ get_ed(), pos, val);\n  }\n\n  /**\n   * @brief Queries the value at position\
    \ pos\n   * @param pos The position to query\n   * @return The value at position\
    \ pos\n   */\n  T point_query(ptr_t pos) const {\n    if (pos < get_st() || pos\
    \ >= get_ed())\n      throw std::out_of_range(\"SegmentTree::point_query: position\
    \ out of range\");\n    return point_query(0, get_st(), get_ed(), pos);\n  }\n\
    \n  /**\n   * @brief Queries the range [left, right)\n   * @param left The left\
    \ index (inclusive)\n   * @param right The right index (exclusive)\n   * @return\
    \ The result of the monoid operation over the range\n   */\n  T range_query(ptr_t\
    \ left, ptr_t right) const {\n    if (left < get_st() || right > get_ed() || left\
    \ > right)\n      throw std::out_of_range(\"SegmentTree::range_query: range out\
    \ of bounds\");\n    return range_query(0, get_st(), get_ed(), left, right);\n\
    \  }\n\n  ptr_t get_st() const { return SegmentBase::get_st(); }\n  ptr_t get_ed()\
    \ const { return SegmentBase::get_ed(); }\n};\n} // namespace weilycoder\n\n\n\
    #line 4 \"test/point_set_range_composite2.test.cpp\"\n#include <cstdint>\n#include\
    \ <iostream>\n#line 7 \"test/point_set_range_composite2.test.cpp\"\nusing namespace\
    \ std;\nusing namespace weilycoder;\n\nstatic constexpr uint64_t mod = 998244353;\n\
    \nstruct AffineMonoid {\n  using value_type = pair<uint64_t, uint64_t>; // (a,\
    \ b) represents f(x) = a * x + b\n\n  static value_type identity() { return {1,\
    \ 0}; }\n  static value_type operation(const value_type &f, const value_type &g)\
    \ {\n    return {(g.first * f.first) % mod, (g.first * f.second + g.second) %\
    \ mod};\n  }\n\n  static uint64_t affine(const value_type &f, uint64_t x) {\n\
    \    return (f.first * x + f.second) % mod;\n  }\n};\n\nint main() {\n  cin.tie(nullptr)->sync_with_stdio(false);\n\
    \  cin.exceptions(cin.badbit | cin.failbit);\n  size_t n, q;\n  cin >> n >> q;\n\
    \n  vector<pair<uint64_t, uint64_t>> affines;\n  affines.reserve(n);\n  for (size_t\
    \ i = 0; i < n; ++i) {\n    uint64_t a, b;\n    cin >> a >> b;\n    affines.emplace_back(a,\
    \ b);\n  }\n\n  SegmentTree<SegmentTreeStoreSon<AffineMonoid>> sgt(affines);\n\
    \  while (q--) {\n    size_t op;\n    cin >> op;\n    if (op == 0) {\n      size_t\
    \ p;\n      uint64_t c, d;\n      cin >> p >> c >> d;\n      sgt.point_set(p,\
    \ {c, d});\n    } else {\n      size_t l, r;\n      uint64_t x;\n      cin >>\
    \ l >> r >> x;\n      auto func = sgt.range_query(l, r);\n      cout << AffineMonoid::affine(func,\
    \ x) << '\\n';\n    }\n  }\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\
    \n\n#include \"../weilycoder/ds/segment_tree.hpp\"\n#include <cstdint>\n#include\
    \ <iostream>\n#include <vector>\nusing namespace std;\nusing namespace weilycoder;\n\
    \nstatic constexpr uint64_t mod = 998244353;\n\nstruct AffineMonoid {\n  using\
    \ value_type = pair<uint64_t, uint64_t>; // (a, b) represents f(x) = a * x + b\n\
    \n  static value_type identity() { return {1, 0}; }\n  static value_type operation(const\
    \ value_type &f, const value_type &g) {\n    return {(g.first * f.first) % mod,\
    \ (g.first * f.second + g.second) % mod};\n  }\n\n  static uint64_t affine(const\
    \ value_type &f, uint64_t x) {\n    return (f.first * x + f.second) % mod;\n \
    \ }\n};\n\nint main() {\n  cin.tie(nullptr)->sync_with_stdio(false);\n  cin.exceptions(cin.badbit\
    \ | cin.failbit);\n  size_t n, q;\n  cin >> n >> q;\n\n  vector<pair<uint64_t,\
    \ uint64_t>> affines;\n  affines.reserve(n);\n  for (size_t i = 0; i < n; ++i)\
    \ {\n    uint64_t a, b;\n    cin >> a >> b;\n    affines.emplace_back(a, b);\n\
    \  }\n\n  SegmentTree<SegmentTreeStoreSon<AffineMonoid>> sgt(affines);\n  while\
    \ (q--) {\n    size_t op;\n    cin >> op;\n    if (op == 0) {\n      size_t p;\n\
    \      uint64_t c, d;\n      cin >> p >> c >> d;\n      sgt.point_set(p, {c, d});\n\
    \    } else {\n      size_t l, r;\n      uint64_t x;\n      cin >> l >> r >> x;\n\
    \      auto func = sgt.range_query(l, r);\n      cout << AffineMonoid::affine(func,\
    \ x) << '\\n';\n    }\n  }\n  return 0;\n}"
  dependsOn:
  - weilycoder/ds/segment_tree.hpp
  isVerificationFile: true
  path: test/point_set_range_composite2.test.cpp
  requiredBy: []
  timestamp: '2025-11-02 13:57:52+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/point_set_range_composite2.test.cpp
layout: document
redirect_from:
- /verify/test/point_set_range_composite2.test.cpp
- /verify/test/point_set_range_composite2.test.cpp.html
title: test/point_set_range_composite2.test.cpp
---
