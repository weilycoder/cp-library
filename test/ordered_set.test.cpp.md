---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: weilycoder/ds/treap.hpp
    title: Treap Data Structure
  - icon: ':heavy_check_mark:'
    path: weilycoder/random.hpp
    title: Lightweight Compile-Time Pseudo-Random Number Generators
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/ordered_set
    links:
    - https://judge.yosupo.jp/problem/ordered_set
  bundledCode: "#line 1 \"test/ordered_set.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/ordered_set\"\
    \n\n#line 1 \"weilycoder/ds/treap.hpp\"\n\n\n\n/**\n * @file treap.hpp\n * @brief\
    \ Treap Data Structure\n */\n\n#line 1 \"weilycoder/random.hpp\"\n\n\n\n/**\n\
    \ * @file random.hpp\n * @brief Lightweight Compile-Time Pseudo-Random Number\
    \ Generators\n */\n\n#include <cstdint>\n\nnamespace weilycoder {\n/**\n * @brief\
    \ Linear Congruential Generator (LCG) to produce pseudo-random numbers\n *   \
    \     at compile-time.\n * @tparam a The multiplier.\n * @tparam c The increment.\n\
    \ * @tparam m The modulus.\n * @param state The current state of the generator.\n\
    \ * @return The next state of the generator.\n */\ntemplate <uint32_t a, uint32_t\
    \ c, uint64_t m>\nconstexpr uint32_t &lcg_next(uint32_t &state) {\n  state = (static_cast<uint64_t>(a)\
    \ * state + c) % m;\n  return state;\n}\n\n/**\n * @brief LCG using parameters\
    \ from \"Minimal Standard\" by Park and Miller.\n * @param state The current state\
    \ of the generator.\n * @return The next state of the generator.\n */\nconstexpr\
    \ uint32_t &lcg_minstd(uint32_t &state) {\n  return lcg_next<48271, 0, 2147483647>(state);\n\
    }\n\n/**\n * @brief LCG using parameters from \"minstd_rand0\" by Park and Miller.\n\
    \ * @param state The current state of the generator.\n * @return The next state\
    \ of the generator.\n */\nconstexpr uint32_t &lcg_minstd_rand0(uint32_t &state)\
    \ {\n  return lcg_next<16807, 0, 2147483647>(state);\n}\n\n/**\n * @brief LCG\
    \ using parameters from \"Numerical Recipes\".\n * @param state The current state\
    \ of the generator.\n * @return The next state of the generator.\n */\nconstexpr\
    \ uint32_t &lcg_nr(uint32_t &state) {\n  return lcg_next<1103515245, 12345, 4294967296>(state);\n\
    }\n} // namespace weilycoder\n\n\n#line 10 \"weilycoder/ds/treap.hpp\"\n#include\
    \ <functional>\n#include <limits>\n#include <tuple>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace weilycoder {\n/**\n * @brief Base class for Treap data\
    \ structure, providing random priority generation.\n */\nstruct treap_base {\n\
    private:\n  static inline uint32_t rand32 = 0;\n\nprotected:\n  static uint32_t\
    \ get_rand() { return lcg_nr(rand32); }\n\npublic:\n  static constexpr size_t\
    \ null = std::numeric_limits<size_t>::max();\n};\n\ntemplate <typename T> struct\
    \ Treap : public treap_base {\nprivate:\n  struct node {\n    T value;\n    uint32_t\
    \ priority;\n    size_t size, left, right;\n    node(const T &value) : value(value),\
    \ priority(get_rand()), size(1u), left(null), right(null) {}\n  };\n\n  std::vector<size_t>\
    \ free_list;\n  std::vector<node> nodes;\n\n  void pushup(size_t p) {\n    if\
    \ (p != null)\n      nodes[p].size = node_size(nodes[p].left) + node_size(nodes[p].right)\
    \ + 1;\n  }\n\npublic:\n  Treap() = default;\n\n  /**\n   * @brief Reserve space\
    \ for n nodes in the treap.\n   * @param n The number of nodes to reserve space\
    \ for.\n   */\n  void reserve(size_t n) { nodes.reserve(n); }\n\n  /**\n   * @brief\
    \ Create a new node with the given value and add it to the treap.\n   * @param\
    \ value The value of the new node.\n   * @return The index of the new node.\n\
    \   */\n  size_t new_node(const T &value) {\n    if (free_list.empty()) {\n  \
    \    nodes.emplace_back(value);\n      return nodes.size() - 1;\n    } else {\n\
    \      size_t p = free_list.back();\n      free_list.pop_back();\n      nodes[p]\
    \ = node(value);\n      return p;\n    }\n  }\n\n  /**\n   * @brief Get the size\
    \ of the subtree rooted at node p.\n   * @param p The index of the node.\n   *\
    \ @return The size of the subtree.\n   */\n  size_t node_size(size_t p) const\
    \ { return p == null ? 0 : nodes[p].size; }\n\n  /**\n   * @brief Get the value\
    \ of node p.\n   * @param p The index of the node.\n   * @return The value of\
    \ the node.\n   */\n  T &node_value(size_t p) { return nodes[p].value; }\n\n \
    \ /**\n   * @brief Get the value of node p (const version).\n   * @param p The\
    \ index of the node.\n   * @return The value of the node.\n   */\n  const T &node_value(size_t\
    \ p) const { return nodes[p].value; }\n\n  /**\n   * @brief Split the treap into\
    \ two treaps: left treap with first k elements,\n   *        right treap with\
    \ the rest.\n   * @param p The root of the treap to split.\n   * @param k The\
    \ number of elements in the left treap.\n   * @return A pair of roots of the left\
    \ and right treaps.\n   */\n  std::pair<size_t, size_t> size_split2(size_t p,\
    \ size_t k) {\n    if (p == null)\n      return {null, null};\n    if (k == 0)\n\
    \      return {null, p};\n    if (node_size(p) <= k)\n      return {p, null};\n\
    \    if (node_size(nodes[p].left) >= k) {\n      auto [l, r] = size_split2(nodes[p].left,\
    \ k);\n      nodes[p].left = r, pushup(p);\n      return {l, p};\n    } else {\n\
    \      auto [l, r] = size_split2(nodes[p].right, k - node_size(nodes[p].left)\
    \ - 1);\n      nodes[p].right = l, pushup(p);\n      return {p, r};\n    }\n \
    \ }\n\n  /**\n   * @brief Split the treap into three treaps: left treap with first\
    \ k - 1 elements,\n   *        middle treap with the k-th element, right treap\
    \ with the rest.\n   * @param p The root of the treap to split.\n   * @param k\
    \ The position of the middle element.\n   * @return A tuple of roots of the left,\
    \ middle, and right treaps.\n   */\n  std::tuple<size_t, size_t, size_t> size_split3(size_t\
    \ p, size_t k) {\n    if (p == null)\n      return {null, null, null};\n    if\
    \ (node_size(p) < k)\n      return {p, null, null};\n    if (node_size(nodes[p].left)\
    \ == k) {\n      size_t left = nodes[p].left;\n      size_t right = nodes[p].right;\n\
    \      nodes[p].size = 1u;\n      nodes[p].left = nodes[p].right = null;\n   \
    \   return {left, p, right};\n    } else if (node_size(nodes[p].left) > k) {\n\
    \      auto [l, m, r] = size_split3(nodes[p].left, k);\n      nodes[p].left =\
    \ r, pushup(p);\n      return {l, m, p};\n    } else {\n      auto [l, m, r] =\
    \ size_split3(nodes[p].right, k - node_size(nodes[p].left) - 1);\n      nodes[p].right\
    \ = l, pushup(p);\n      return {p, m, r};\n    }\n  }\n\n  /**\n   * @brief Split\
    \ the treap into two treaps based on a value:\n   *        left treap with values\
    \ less than the given value,\n   *        right treap with values greater than\
    \ or equal to the given value.\n   * @tparam Compare The comparison functor type\
    \ (default is `std::less<T>`).\n   * @param p The root of the treap to split.\n\
    \   * @param value The value to split the treap by.\n   * @return A pair of roots\
    \ of the left and right treaps.\n   * @note If the treap has not maintained sorted\
    \ order, the result is undefined.\n   */\n  template <typename Compare = std::less<T>>\
    \ std::pair<size_t, size_t> lower_split(size_t p, const T &value) {\n    constexpr\
    \ Compare less;\n    if (p == null)\n      return {null, null};\n    if (less(nodes[p].value,\
    \ value)) {\n      // Value at p is less than the given value, go right\n    \
    \  auto [l, r] = lower_split(nodes[p].right, value);\n      nodes[p].right = l,\
    \ pushup(p);\n      return {p, r};\n    } else {\n      // Value at p is greater\
    \ than or equal to the given value, go left\n      auto [l, r] = lower_split(nodes[p].left,\
    \ value);\n      nodes[p].left = r, pushup(p);\n      return {l, p};\n    }\n\
    \  }\n\n  /**\n   * @brief Split the treap into two treaps based on a value:\n\
    \   *        left treap with values less than or equal to the given value,\n \
    \  *        right treap with values greater than the given value.\n   * @tparam\
    \ Compare The comparison functor type (default is `std::less<T>`).\n   * @param\
    \ p The root of the treap to split.\n   * @param value The value to split the\
    \ treap by.\n   * @return A pair of roots of the left and right treaps.\n   *\
    \ @note If the treap has not maintained sorted order, the result is undefined.\n\
    \   */\n  template <typename Compare = std::less<T>> std::pair<size_t, size_t>\
    \ upper_split(size_t p, const T &value) {\n    constexpr Compare less;\n    if\
    \ (p == null)\n      return {null, null};\n    if (less(value, nodes[p].value))\
    \ {\n      // Value at p is greater than the given value, go left\n      auto\
    \ [l, r] = upper_split(nodes[p].left, value);\n      nodes[p].left = r, pushup(p);\n\
    \      return {l, p};\n    } else {\n      // Value at p is less than or equal\
    \ to the given value, go right\n      auto [l, r] = upper_split(nodes[p].right,\
    \ value);\n      nodes[p].right = l, pushup(p);\n      return {p, r};\n    }\n\
    \  }\n\n  /**\n   * @brief Split the treap into three treaps based on a value:\n\
    \   *        left treap with values less than or equal to the given value,\n \
    \  *        middle treap with values equal to the given value (at most one node),\n\
    \   *        right treap with values greater than or equal to the given value.\n\
    \   * @tparam Compare The comparison functor type (default is `std::less<T>`).\n\
    \   * @param p The root of the treap to split.\n   * @param value The value to\
    \ split the treap by.\n   * @return A tuple of roots of the left, middle, and\
    \ right treaps.\n   * @note If the treap has not maintained sorted order, the\
    \ result is undefined.\n   * @note If want to split all equal values into the\
    \ middle treap,\n   *       use `lower_split` and `upper_split` instead.\n   */\n\
    \  template <typename Compare = std::less<T>> std::tuple<size_t, size_t, size_t>\
    \ value_split(size_t p, const T &value) {\n    constexpr Compare less;\n    if\
    \ (p == null)\n      return {null, null, null};\n    if (less(nodes[p].value,\
    \ value)) {\n      // Value at p is less than the given value, go right\n    \
    \  auto [l, m, r] = value_split(nodes[p].right, value);\n      nodes[p].right\
    \ = l, pushup(p);\n      return {p, m, r};\n    } else if (less(value, nodes[p].value))\
    \ {\n      // Value at p is greater than the given value, go left\n      auto\
    \ [l, m, r] = value_split(nodes[p].left, value);\n      nodes[p].left = r, pushup(p);\n\
    \      return {l, m, p};\n    } else {\n      size_t left = nodes[p].left;\n \
    \     size_t right = nodes[p].right;\n      nodes[p].size = 1u;\n      nodes[p].left\
    \ = nodes[p].right = null;\n      return {left, p, right};\n    }\n  }\n\n  /**\n\
    \   * @brief Get the k-th node in the treap (0-indexed).\n   * @param p The root\
    \ of the treap.\n   * @param k The index of the node to get.\n   * @return The\
    \ index of the found node, or `null` if not found.\n   */\n  size_t get_by_size(size_t\
    \ p, size_t k) const {\n    if (p == null || k >= node_size(p))\n      return\
    \ null;\n    if (node_size(nodes[p].left) == k)\n      return p;\n    else if\
    \ (node_size(nodes[p].left) > k)\n      return get_by_size(nodes[p].left, k);\n\
    \    else\n      return get_by_size(nodes[p].right, k - node_size(nodes[p].left)\
    \ - 1);\n  }\n\n  /**\n   * @brief Get the first node with a value not less than\
    \ the given value.\n   * @tparam Compare The comparison functor type (default\
    \ is `std::less<T>`).\n   * @param p The root of the treap.\n   * @param value\
    \ The value to search for.\n   * @return The index of the found node, or `null`\
    \ if not found.\n   * @note If the treap has not maintained sorted order, the\
    \ result is undefined.\n   */\n  template <typename Compare = std::less<T>> size_t\
    \ get_greater(size_t p, const T &value) const {\n    if (p == null)\n      return\
    \ null;\n    constexpr Compare less;\n    if (less(nodes[p].value, value))\n \
    \     return get_greater<Compare>(nodes[p].right, value);\n    else {\n      size_t\
    \ res = get_greater<Compare>(nodes[p].left, value);\n      return res == null\
    \ ? p : res;\n    }\n  }\n\n  /**\n   * @brief Get the last node with a value\
    \ not greater than the given value.\n   * @tparam Compare The comparison functor\
    \ type (default is `std::less<T>`).\n   * @param p The root of the treap.\n  \
    \ * @param value The value to search for.\n   * @return The index of the found\
    \ node, or `null` if not found.\n   * @note If the treap has not maintained sorted\
    \ order, the result is undefined.\n   */\n  template <typename Compare = std::less<T>>\
    \ size_t get_less(size_t p, const T &value) const {\n    if (p == null)\n    \
    \  return null;\n    constexpr Compare less;\n    if (less(value, nodes[p].value))\n\
    \      return get_less<Compare>(nodes[p].left, value);\n    else {\n      size_t\
    \ res = get_less<Compare>(nodes[p].right, value);\n      return res == null ?\
    \ p : res;\n    }\n  }\n\n  /**\n   * @brief Get the number of elements in the\
    \ treap less than the given value.\n   * @tparam Compare The comparison functor\
    \ type (default is `std::less<T>`).\n   * @param p The root of the treap.\n  \
    \ * @param value The value to compare.\n   * @return The number of elements less\
    \ than the given value.\n   * @note If the treap has not maintained sorted order,\
    \ the result is undefined.\n   */\n  template <typename Compare = std::less<T>>\
    \ size_t get_rank(size_t p, const T &value) const {\n    if (p == null)\n    \
    \  return 0;\n    constexpr Compare less;\n    if (less(nodes[p].value, value))\n\
    \      return node_size(nodes[p].left) + 1 + get_rank<Compare>(nodes[p].right,\
    \ value);\n    else\n      return get_rank<Compare>(nodes[p].left, value);\n \
    \ }\n\n  /**\n   * @brief Merge two treaps into one.\n   * @param left The root\
    \ of the left treap.\n   * @param right The root of the right treap.\n   * @return\
    \ The root of the merged treap.\n   */\n  size_t merge(size_t left, size_t right)\
    \ {\n    if (left == null || right == null)\n      return left == null ? right\
    \ : left;\n    if (nodes[left].priority > nodes[right].priority) {\n      nodes[left].right\
    \ = merge(nodes[left].right, right);\n      return pushup(left), left;\n    }\
    \ else {\n      nodes[right].left = merge(left, nodes[right].left);\n      return\
    \ pushup(right), right;\n    }\n  }\n\n  /**\n   * @brief Insert a value at a\
    \ given position in the treap.\n   * @param root The root of the treap.\n   *\
    \ @param pos The position to insert the value at.\n   * @param value The value\
    \ to insert.\n   * @return The new root of the treap after insertion.\n   */\n\
    \  size_t insert(size_t root, size_t pos, const T &value) {\n    auto [left, right]\
    \ = size_split2(root, pos);\n    size_t newnode = new_node(value);\n    return\
    \ merge(merge(left, newnode), right);\n  }\n\n  /**\n   * @brief Insert a value\
    \ into the treap while maintaining sorted order.\n   * @tparam Compare The comparison\
    \ functor type (default is `std::less<T>`).\n   * @param root The root of the\
    \ treap.\n   * @param value The value to insert.\n   * @return The new root of\
    \ the treap after insertion.\n   * @note If the treap has not maintained sorted\
    \ order, the result is undefined.\n   */\n  template <typename Compare = std::less<T>>\
    \ size_t insert(size_t root, const T &value) {\n    auto [left, right] = lower_split<Compare>(root,\
    \ value);\n    size_t newnode = new_node(value);\n    return merge(merge(left,\
    \ newnode), right);\n  }\n\n  /**\n   * @brief Insert a unique value into the\
    \ treap while maintaining sorted order.\n   * @tparam Compare The comparison functor\
    \ type (default is `std::less<T>`).\n   * @param root The root of the treap.\n\
    \   * @param value The value to insert.\n   * @return A pair containing the new\
    \ root of the treap after insertion\n   *         and a boolean indicating whether\
    \ the insertion took place.\n   * @note If the treap has not maintained sorted\
    \ order, the result is undefined.\n   */\n  template <typename Compare = std::less<T>>\
    \ std::pair<size_t, bool> insert_unique(size_t root, const T &value) {\n    auto\
    \ [left, mid, right] = value_split<Compare>(root, value);\n    if (mid != null)\
    \ {\n      // Value already exists, do not insert\n      return {merge(merge(left,\
    \ mid), right), false};\n    }\n    size_t newnode = new_node(value);\n    return\
    \ {merge(merge(left, newnode), right), true};\n  }\n\n  /**\n   * @brief Erase\
    \ the node at a given position in the treap.\n   * @param root The root of the\
    \ treap.\n   * @param pos The position of the node to erase.\n   * @return The\
    \ new root of the treap after erasure.\n   */\n  size_t erase(size_t root, size_t\
    \ pos) {\n    auto [left, mid, right] = size_split3(root, pos);\n    free_list.push_back(mid);\n\
    \    return merge(left, right);\n  }\n\n  /**\n   * @brief Erase a value from\
    \ the treap while maintaining sorted order.\n   * @tparam Compare The comparison\
    \ functor type (default is `std::less<T>`).\n   * @param root The root of the\
    \ treap.\n   * @param value The value to erase.\n   * @return The new root of\
    \ the treap after erasure.\n   * @note If the treap has not maintained sorted\
    \ order, the result is undefined.\n   */\n  template <typename Compare = std::less<T>>\
    \ size_t erase_value(size_t root, const T &value) {\n    auto [left, mid, right]\
    \ = value_split<Compare>(root, value);\n    if (mid != null)\n      free_list.push_back(mid);\n\
    \    return merge(left, right);\n  }\n\n  /**\n   * @brief Erase all occurrences\
    \ of a value from the treap while maintaining sorted\n   *        order.\n   *\
    \ @tparam Compare The comparison functor type (default is `std::less<T>`).\n \
    \  * @param root The root of the treap.\n   * @param value The value to erase.\n\
    \   * @return The new root of the treap after erasure.\n   * @note If the treap\
    \ has not maintained sorted order, the result is undefined.\n   */\n  template\
    \ <typename Compare = std::less<T>> size_t erase_value_all(size_t root, const\
    \ T &value) {\n    auto [left, right] = lower_split<Compare>(root, value);\n \
    \   auto [mid, rright] = upper_split<Compare>(right, value);\n    erase_treap(mid);\n\
    \    return merge(left, rright);\n  }\n\n  /**\n   * @brief Recursively erase\
    \ all nodes in the treap rooted at p.\n   * @param p The root of the treap.\n\
    \   */\n  void erase_treap(size_t p) {\n    if (p != null) {\n      erase_treap(nodes[p].left);\n\
    \      erase_treap(nodes[p].right);\n      free_list.push_back(p);\n    }\n  }\n\
    \n  /**\n   * @brief Apply a function to all nodes in the treap in-order.\n  \
    \ * @tparam Func The function type.\n   * @param p The root of the treap.\n  \
    \ * @param func The function to apply to each node index.\n   */\n  template <typename\
    \ Func> void work_nodes(size_t p, Func func) const {\n    if (p == null)\n   \
    \   return;\n    work_nodes(nodes[p].left, func);\n    func(p);\n    work_nodes(nodes[p].right,\
    \ func);\n  }\n\n  /**\n   * @brief Get all node indices in the treap in-order.\n\
    \   * @param p The root of the treap.\n   * @return A vector of node indices in\
    \ in-order.\n   */\n  std::vector<size_t> get_nodes(size_t p) const {\n    std::vector<size_t>\
    \ res;\n    work_nodes(p, [&](size_t node) { res.push_back(node); });\n    return\
    \ res;\n  }\n};\n} // namespace weilycoder\n\n\n#line 4 \"test/ordered_set.test.cpp\"\
    \n#include <iostream>\nusing namespace std;\nusing namespace weilycoder;\n\nint\
    \ main() {\n  cin.tie(nullptr)->sync_with_stdio(false);\n  cin.exceptions(cin.failbit\
    \ | cin.badbit);\n  size_t n, q;\n  cin >> n >> q;\n\n  Treap<uint32_t> treap;\n\
    \  treap.reserve(n + q);\n  size_t root = Treap<uint32_t>::null;\n\n  for (size_t\
    \ i = 0; i < n; ++i) {\n    uint32_t x;\n    cin >> x;\n    root = treap.insert(root,\
    \ x);\n  }\n\n  while (q--) {\n    uint32_t o, x;\n    cin >> o >> x;\n    switch\
    \ (o) {\n    case 0:\n      root = treap.insert_unique(root, x).first;\n     \
    \ break;\n    case 1:\n      root = treap.erase_value(root, x);\n      break;\n\
    \    case 2:\n      if (x > treap.node_size(root))\n        cout << -1 << '\\\
    n';\n      else {\n        size_t node = treap.get_by_size(root, x - 1);\n   \
    \     cout << treap.node_value(node) << '\\n';\n      }\n      break;\n    case\
    \ 3:\n      cout << treap.get_rank<std::less_equal<uint32_t>>(root, x) << '\\\
    n';\n      break;\n    case 4: {\n      size_t node = treap.get_less(root, x);\n\
    \      if (node == Treap<uint32_t>::null)\n        cout << -1 << '\\n';\n    \
    \  else\n        cout << treap.node_value(node) << '\\n';\n      break;\n    }\n\
    \    case 5: {\n      size_t node = treap.get_greater(root, x);\n      if (node\
    \ == Treap<uint32_t>::null)\n        cout << -1 << '\\n';\n      else\n      \
    \  cout << treap.node_value(node) << '\\n';\n      break;\n    }\n    }\n  }\n\
    \  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/ordered_set\"\n\n#include\
    \ \"../weilycoder/ds/treap.hpp\"\n#include <iostream>\nusing namespace std;\n\
    using namespace weilycoder;\n\nint main() {\n  cin.tie(nullptr)->sync_with_stdio(false);\n\
    \  cin.exceptions(cin.failbit | cin.badbit);\n  size_t n, q;\n  cin >> n >> q;\n\
    \n  Treap<uint32_t> treap;\n  treap.reserve(n + q);\n  size_t root = Treap<uint32_t>::null;\n\
    \n  for (size_t i = 0; i < n; ++i) {\n    uint32_t x;\n    cin >> x;\n    root\
    \ = treap.insert(root, x);\n  }\n\n  while (q--) {\n    uint32_t o, x;\n    cin\
    \ >> o >> x;\n    switch (o) {\n    case 0:\n      root = treap.insert_unique(root,\
    \ x).first;\n      break;\n    case 1:\n      root = treap.erase_value(root, x);\n\
    \      break;\n    case 2:\n      if (x > treap.node_size(root))\n        cout\
    \ << -1 << '\\n';\n      else {\n        size_t node = treap.get_by_size(root,\
    \ x - 1);\n        cout << treap.node_value(node) << '\\n';\n      }\n      break;\n\
    \    case 3:\n      cout << treap.get_rank<std::less_equal<uint32_t>>(root, x)\
    \ << '\\n';\n      break;\n    case 4: {\n      size_t node = treap.get_less(root,\
    \ x);\n      if (node == Treap<uint32_t>::null)\n        cout << -1 << '\\n';\n\
    \      else\n        cout << treap.node_value(node) << '\\n';\n      break;\n\
    \    }\n    case 5: {\n      size_t node = treap.get_greater(root, x);\n     \
    \ if (node == Treap<uint32_t>::null)\n        cout << -1 << '\\n';\n      else\n\
    \        cout << treap.node_value(node) << '\\n';\n      break;\n    }\n    }\n\
    \  }\n  return 0;\n}"
  dependsOn:
  - weilycoder/ds/treap.hpp
  - weilycoder/random.hpp
  isVerificationFile: true
  path: test/ordered_set.test.cpp
  requiredBy: []
  timestamp: '2025-11-10 13:48:15+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/ordered_set.test.cpp
layout: document
redirect_from:
- /verify/test/ordered_set.test.cpp
- /verify/test/ordered_set.test.cpp.html
title: test/ordered_set.test.cpp
---
