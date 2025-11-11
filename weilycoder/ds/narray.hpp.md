---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: weilycoder/matrix.hpp
    title: Matrix implementation using narray
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/matrix_product.test.cpp
    title: test/matrix_product.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: N-dimensional array (narray)
    links: []
  bundledCode: "#line 1 \"weilycoder/ds/narray.hpp\"\n\n\n\n/**\n * @file narray.hpp\n\
    \ * @brief N-dimensional array (narray)\n */\n\n#include <array>\n#include <cstddef>\n\
    #include <initializer_list>\n#include <vector>\n\nnamespace weilycoder {\n/**\n\
    \ * @brief N-dimensional array (narray) implementation.\n * @tparam T Type of\
    \ elements stored in the narray.\n * @tparam D Number of dimensions.\n */\ntemplate\
    \ <typename T, size_t D> struct narray {\n  const std::array<size_t, D> shape;\n\
    \  std::vector<T> data;\n\n  /**\n   * @brief Constructor to initialize narray\
    \ with given dimensions.\n   * @tparam Sizes Parameter pack for sizes of each\
    \ dimension.\n   * @param sizes Sizes of each dimension.\n   */\n  template <typename...\
    \ Sizes>\n  narray(Sizes... sizes) : shape{static_cast<size_t>(sizes)...} {\n\
    \    static_assert(sizeof...(Sizes) == D, \"Number of sizes must match dimensions.\"\
    );\n    data.resize(size());\n  }\n\n  /**\n   * @brief Get the total number of\
    \ elements in the narray.\n   * @return Total number of elements.\n   */\n  size_t\
    \ size() const {\n    size_t res = 1;\n    for (size_t i = 0; i < D; ++i)\n  \
    \    res *= shape[i];\n    return res;\n  }\n\n  /**\n   * @brief Compute the\
    \ linear index from multi-dimensional indices.\n   * @tparam Indices Parameter\
    \ pack for indices in each dimension.\n   * @param indices Indices in each dimension.\n\
    \   * @return Linear index corresponding to the multi-dimensional indices.\n \
    \  */\n  template <typename... Indices> size_t _index(Indices... indices) const\
    \ {\n    static_assert(sizeof...(Indices) == D, \"Number of indices must match\
    \ dimensions.\");\n    const size_t idxs[] = {static_cast<size_t>(indices)...};\n\
    \    size_t res = 0;\n    for (size_t i = 0; i < D; ++i)\n      res = res * shape[i]\
    \ + idxs[i];\n    return res;\n  }\n\n  /**\n   * @brief Access element at specified\
    \ multi-dimensional indices.\n   * @tparam Indices Parameter pack for indices\
    \ in each dimension.\n   * @param indices Indices in each dimension.\n   * @return\
    \ Reference to the element at the specified indices.\n   */\n  template <typename...\
    \ Indices> const T &operator()(Indices... indices) const {\n    return data[_index(indices...)];\n\
    \  }\n\n  /**\n   * @brief Access element at specified multi-dimensional indices.\n\
    \   * @tparam Indices Parameter pack for indices in each dimension.\n   * @param\
    \ indices Indices in each dimension.\n   * @return Reference to the element at\
    \ the specified indices.\n   */\n  template <typename... Indices> T &operator()(Indices...\
    \ indices) {\n    return data[_index(indices...)];\n  }\n};\n} // namespace weilycoder\n\
    \n\n"
  code: "#ifndef WEILYCODER_DS_NARRAY_HPP\n#define WEILYCODER_DS_NARRAY_HPP\n\n/**\n\
    \ * @file narray.hpp\n * @brief N-dimensional array (narray)\n */\n\n#include\
    \ <array>\n#include <cstddef>\n#include <initializer_list>\n#include <vector>\n\
    \nnamespace weilycoder {\n/**\n * @brief N-dimensional array (narray) implementation.\n\
    \ * @tparam T Type of elements stored in the narray.\n * @tparam D Number of dimensions.\n\
    \ */\ntemplate <typename T, size_t D> struct narray {\n  const std::array<size_t,\
    \ D> shape;\n  std::vector<T> data;\n\n  /**\n   * @brief Constructor to initialize\
    \ narray with given dimensions.\n   * @tparam Sizes Parameter pack for sizes of\
    \ each dimension.\n   * @param sizes Sizes of each dimension.\n   */\n  template\
    \ <typename... Sizes>\n  narray(Sizes... sizes) : shape{static_cast<size_t>(sizes)...}\
    \ {\n    static_assert(sizeof...(Sizes) == D, \"Number of sizes must match dimensions.\"\
    );\n    data.resize(size());\n  }\n\n  /**\n   * @brief Get the total number of\
    \ elements in the narray.\n   * @return Total number of elements.\n   */\n  size_t\
    \ size() const {\n    size_t res = 1;\n    for (size_t i = 0; i < D; ++i)\n  \
    \    res *= shape[i];\n    return res;\n  }\n\n  /**\n   * @brief Compute the\
    \ linear index from multi-dimensional indices.\n   * @tparam Indices Parameter\
    \ pack for indices in each dimension.\n   * @param indices Indices in each dimension.\n\
    \   * @return Linear index corresponding to the multi-dimensional indices.\n \
    \  */\n  template <typename... Indices> size_t _index(Indices... indices) const\
    \ {\n    static_assert(sizeof...(Indices) == D, \"Number of indices must match\
    \ dimensions.\");\n    const size_t idxs[] = {static_cast<size_t>(indices)...};\n\
    \    size_t res = 0;\n    for (size_t i = 0; i < D; ++i)\n      res = res * shape[i]\
    \ + idxs[i];\n    return res;\n  }\n\n  /**\n   * @brief Access element at specified\
    \ multi-dimensional indices.\n   * @tparam Indices Parameter pack for indices\
    \ in each dimension.\n   * @param indices Indices in each dimension.\n   * @return\
    \ Reference to the element at the specified indices.\n   */\n  template <typename...\
    \ Indices> const T &operator()(Indices... indices) const {\n    return data[_index(indices...)];\n\
    \  }\n\n  /**\n   * @brief Access element at specified multi-dimensional indices.\n\
    \   * @tparam Indices Parameter pack for indices in each dimension.\n   * @param\
    \ indices Indices in each dimension.\n   * @return Reference to the element at\
    \ the specified indices.\n   */\n  template <typename... Indices> T &operator()(Indices...\
    \ indices) {\n    return data[_index(indices...)];\n  }\n};\n} // namespace weilycoder\n\
    \n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: weilycoder/ds/narray.hpp
  requiredBy:
  - weilycoder/matrix.hpp
  timestamp: '2025-11-11 19:14:58+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/matrix_product.test.cpp
documentation_of: weilycoder/ds/narray.hpp
layout: document
redirect_from:
- /library/weilycoder/ds/narray.hpp
- /library/weilycoder/ds/narray.hpp.html
title: N-dimensional array (narray)
---
