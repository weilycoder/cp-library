---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: weilycoder/ds/narray.hpp
    title: N-dimensional array (narray)
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/matrix_product.test.cpp
    title: test/matrix_product.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Matrix implementation using narray
    links: []
  bundledCode: "#line 1 \"weilycoder/matrix.hpp\"\n\n\n\n/**\n * @file matrix.hpp\n\
    \ * @brief Matrix implementation using narray\n */\n\n#line 1 \"weilycoder/ds/narray.hpp\"\
    \n\n\n\n/**\n * @file narray.hpp\n * @brief N-dimensional array (narray)\n */\n\
    \n#include <array>\n#include <cstddef>\n#include <initializer_list>\n#include\
    \ <vector>\n\nnamespace weilycoder {\n/**\n * @brief N-dimensional array (narray)\
    \ implementation.\n * @tparam T Type of elements stored in the narray.\n * @tparam\
    \ D Number of dimensions.\n */\ntemplate <typename T, size_t D> struct narray\
    \ {\n  const std::array<size_t, D> shape;\n  std::vector<T> data;\n\n  /**\n \
    \  * @brief Constructor to initialize narray with given dimensions.\n   * @tparam\
    \ Sizes Parameter pack for sizes of each dimension.\n   * @param sizes Sizes of\
    \ each dimension.\n   */\n  template <typename... Sizes>\n  narray(Sizes... sizes)\
    \ : shape{static_cast<size_t>(sizes)...} {\n    static_assert(sizeof...(Sizes)\
    \ == D, \"Number of sizes must match dimensions.\");\n    data.resize(size());\n\
    \  }\n\n  /**\n   * @brief Get the total number of elements in the narray.\n \
    \  * @return Total number of elements.\n   */\n  size_t size() const {\n    size_t\
    \ res = 1;\n    for (size_t i = 0; i < D; ++i)\n      res *= shape[i];\n    return\
    \ res;\n  }\n\n  /**\n   * @brief Compute the linear index from multi-dimensional\
    \ indices.\n   * @tparam Indices Parameter pack for indices in each dimension.\n\
    \   * @param indices Indices in each dimension.\n   * @return Linear index corresponding\
    \ to the multi-dimensional indices.\n   */\n  template <typename... Indices> size_t\
    \ _index(Indices... indices) const {\n    static_assert(sizeof...(Indices) ==\
    \ D, \"Number of indices must match dimensions.\");\n    const size_t idxs[] =\
    \ {static_cast<size_t>(indices)...};\n    size_t res = 0;\n    for (size_t i =\
    \ 0; i < D; ++i)\n      res = res * shape[i] + idxs[i];\n    return res;\n  }\n\
    \n  /**\n   * @brief Access element at specified multi-dimensional indices.\n\
    \   * @tparam Indices Parameter pack for indices in each dimension.\n   * @param\
    \ indices Indices in each dimension.\n   * @return Reference to the element at\
    \ the specified indices.\n   */\n  template <typename... Indices> const T &operator()(Indices...\
    \ indices) const {\n    return data[_index(indices...)];\n  }\n\n  /**\n   * @brief\
    \ Access element at specified multi-dimensional indices.\n   * @tparam Indices\
    \ Parameter pack for indices in each dimension.\n   * @param indices Indices in\
    \ each dimension.\n   * @return Reference to the element at the specified indices.\n\
    \   */\n  template <typename... Indices> T &operator()(Indices... indices) {\n\
    \    return data[_index(indices...)];\n  }\n};\n} // namespace weilycoder\n\n\n\
    #line 11 \"weilycoder/matrix.hpp\"\n#include <stdexcept>\n\nnamespace weilycoder\
    \ {\ntemplate <typename T, size_t R, size_t C> struct Matrix {\n  T data[R][C];\n\
    \n  Matrix() : data{} {}\n  Matrix(std::initializer_list<T> init) {\n    size_t\
    \ i = 0, j = 0;\n    for (const auto &val : init) {\n      data[i][j] = val;\n\
    \      if (++j == C)\n        j = 0, ++i;\n    }\n  }\n\n  /**\n   * @brief Access\
    \ element at specified row and column.\n   * @param row Row index.\n   * @param\
    \ col Column index.\n   * @return Reference to the element at the specified row\
    \ and column.\n   */\n  constexpr const T &operator()(size_t row, size_t col)\
    \ const { return data[row][col]; }\n\n  /**\n   * @brief Access element at specified\
    \ row and column.\n   * @param row Row index.\n   * @param col Column index.\n\
    \   * @return Reference to the element at the specified row and column.\n   */\n\
    \  T &operator()(size_t row, size_t col) { return data[row][col]; }\n\n  Matrix<T,\
    \ R, C> &operator+=(const Matrix<T, R, C> &other) {\n    for (size_t i = 0; i\
    \ < R; ++i)\n      for (size_t j = 0; j < C; ++j)\n        data(i, j) += other(i,\
    \ j);\n    return *this;\n  }\n\n  Matrix<T, R, C> &operator-=(const Matrix<T,\
    \ R, C> &other) {\n    for (size_t i = 0; i < R; ++i)\n      for (size_t j = 0;\
    \ j < C; ++j)\n        data(i, j) -= other(i, j);\n    return *this;\n  }\n\n\
    \  template <size_t M> Matrix<T, R, M> &operator*=(const Matrix<T, C, M> &other)\
    \ {\n    Matrix<T, R, M> result;\n    for (size_t i = 0; i < R; ++i)\n      for\
    \ (size_t j = 0; j < M; ++j)\n        for (size_t k = 0; k < C; ++k)\n       \
    \   result(i, j) += data(i, k) * other(k, j);\n    return *this = result;\n  }\n\
    \n  friend Matrix<T, R, C> operator+(const Matrix<T, R, C> &a, const Matrix<T,\
    \ R, C> &b) {\n    Matrix<T, R, C> result;\n    for (size_t i = 0; i < R; ++i)\n\
    \      for (size_t j = 0; j < C; ++j)\n        result(i, j) = a(i, j) + b(i, j);\n\
    \    return result;\n  }\n\n  friend Matrix<T, R, C> operator-(const Matrix<T,\
    \ R, C> &a, const Matrix<T, R, C> &b) {\n    Matrix<T, R, C> result;\n    for\
    \ (size_t i = 0; i < R; ++i)\n      for (size_t j = 0; j < C; ++j)\n        result(i,\
    \ j) = a(i, j) - b(i, j);\n    return result;\n  }\n\n  template <size_t M>\n\
    \  friend Matrix<T, R, C> operator*(const Matrix<T, R, M> &a, const Matrix<T,\
    \ M, C> &b) {\n    Matrix<T, R, C> result;\n    for (size_t i = 0; i < R; ++i)\n\
    \      for (size_t j = 0; j < C; ++j)\n        for (size_t k = 0; k < M; ++k)\n\
    \          result(i, j) += a(i, k) * b(k, j);\n    return result;\n  }\n};\n\n\
    template <typename T> struct NMatrix {\n  narray<T, 2> data;\n\n  NMatrix(size_t\
    \ rows, size_t cols) : data(rows, cols) {}\n\n  template <size_t R, size_t C>\
    \ NMatrix(const Matrix<T, R, C> &matrix) : data(R, C) {\n    for (size_t i = 0;\
    \ i < R; ++i)\n      for (size_t j = 0; j < C; ++j)\n        data(i, j) = matrix(i,\
    \ j);\n  }\n\n  /**\n   * @brief Access element at specified row and column.\n\
    \   * @param row Row index.\n   * @param col Column index.\n   * @return Reference\
    \ to the element at the specified row and column.\n   */\n  constexpr const T\
    \ &operator()(size_t row, size_t col) const { return data(row, col); }\n\n  /**\n\
    \   * @brief Access element at specified row and column.\n   * @param row Row\
    \ index.\n   * @param col Column index.\n   * @return Reference to the element\
    \ at the specified row and column.\n   */\n  T &operator()(size_t row, size_t\
    \ col) { return data(row, col); }\n\n  NMatrix<T> &operator+=(const NMatrix<T>\
    \ &other) {\n    if (data.shape != other.data.shape)\n      throw std::invalid_argument(\"\
    Matrix dimensions do not match for addition.\");\n    for (size_t i = 0; i < data.shape[0];\
    \ ++i)\n      for (size_t j = 0; j < data.shape[1]; ++j)\n        data(i, j) +=\
    \ other(i, j);\n    return *this;\n  }\n\n  NMatrix<T> &operator-=(const NMatrix<T>\
    \ &other) {\n    if (data.shape != other.data.shape)\n      throw std::invalid_argument(\"\
    Matrix dimensions do not match for subtraction.\");\n    for (size_t i = 0; i\
    \ < data.shape[0]; ++i)\n      for (size_t j = 0; j < data.shape[1]; ++j)\n  \
    \      data(i, j) -= other(i, j);\n    return *this;\n  }\n\n  NMatrix<T> &operator*=(const\
    \ NMatrix<T> &other) {\n    if (data.shape[1] != other.data.shape[0])\n      throw\
    \ std::invalid_argument(\"Matrix dimensions do not match for multiplication.\"\
    );\n    size_t R = data.shape[0];\n    size_t C = other.data.shape[1];\n    size_t\
    \ K = data.shape[1];\n    NMatrix<T> result(R, C);\n    for (size_t i = 0; i <\
    \ R; ++i)\n      for (size_t k = 0; k < K; ++k)\n        for (size_t j = 0; j\
    \ < C; ++j)\n          result(i, j) += data(i, k) * other(k, j);\n    return *this\
    \ = result;\n  }\n\n  friend NMatrix<T> operator+(const NMatrix<T> &a, const NMatrix<T>\
    \ &b) {\n    if (a.data.shape != b.data.shape)\n      throw std::invalid_argument(\"\
    Matrix dimensions do not match for addition.\");\n    NMatrix<T> result(a.data.shape[0],\
    \ a.data.shape[1]);\n    for (size_t i = 0; i < a.data.shape[0]; ++i)\n      for\
    \ (size_t j = 0; j < a.data.shape[1]; ++j)\n        result(i, j) = a(i, j) + b(i,\
    \ j);\n    return result;\n  }\n\n  friend NMatrix<T> operator-(const NMatrix<T>\
    \ &a, const NMatrix<T> &b) {\n    if (a.data.shape != b.data.shape)\n      throw\
    \ std::invalid_argument(\"Matrix dimensions do not match for subtraction.\");\n\
    \    NMatrix<T> result(a.data.shape[0], a.data.shape[1]);\n    for (size_t i =\
    \ 0; i < a.data.shape[0]; ++i)\n      for (size_t j = 0; j < a.data.shape[1];\
    \ ++j)\n        result(i, j) = a(i, j) - b(i, j);\n    return result;\n  }\n\n\
    \  friend NMatrix<T> operator*(const NMatrix<T> &a, const NMatrix<T> &b) {\n \
    \   if (a.data.shape[1] != b.data.shape[0])\n      throw std::invalid_argument(\"\
    Matrix dimensions do not match for multiplication.\");\n    size_t R = a.data.shape[0];\n\
    \    size_t C = b.data.shape[1];\n    size_t K = a.data.shape[1];\n    NMatrix<T>\
    \ result(R, C);\n    for (size_t i = 0; i < R; ++i)\n      for (size_t k = 0;\
    \ k < K; ++k)\n        for (size_t j = 0; j < C; ++j)\n          result(i, j)\
    \ += a(i, k) * b(k, j);\n    return result;\n  }\n};\n} // namespace weilycoder\n\
    \n\n"
  code: "#ifndef WEILYCODER_MATRIX_HPP\n#define WEILYCODER_MATRIX_HPP\n\n/**\n * @file\
    \ matrix.hpp\n * @brief Matrix implementation using narray\n */\n\n#include \"\
    ds/narray.hpp\"\n#include <cstddef>\n#include <stdexcept>\n\nnamespace weilycoder\
    \ {\ntemplate <typename T, size_t R, size_t C> struct Matrix {\n  T data[R][C];\n\
    \n  Matrix() : data{} {}\n  Matrix(std::initializer_list<T> init) {\n    size_t\
    \ i = 0, j = 0;\n    for (const auto &val : init) {\n      data[i][j] = val;\n\
    \      if (++j == C)\n        j = 0, ++i;\n    }\n  }\n\n  /**\n   * @brief Access\
    \ element at specified row and column.\n   * @param row Row index.\n   * @param\
    \ col Column index.\n   * @return Reference to the element at the specified row\
    \ and column.\n   */\n  constexpr const T &operator()(size_t row, size_t col)\
    \ const { return data[row][col]; }\n\n  /**\n   * @brief Access element at specified\
    \ row and column.\n   * @param row Row index.\n   * @param col Column index.\n\
    \   * @return Reference to the element at the specified row and column.\n   */\n\
    \  T &operator()(size_t row, size_t col) { return data[row][col]; }\n\n  Matrix<T,\
    \ R, C> &operator+=(const Matrix<T, R, C> &other) {\n    for (size_t i = 0; i\
    \ < R; ++i)\n      for (size_t j = 0; j < C; ++j)\n        data(i, j) += other(i,\
    \ j);\n    return *this;\n  }\n\n  Matrix<T, R, C> &operator-=(const Matrix<T,\
    \ R, C> &other) {\n    for (size_t i = 0; i < R; ++i)\n      for (size_t j = 0;\
    \ j < C; ++j)\n        data(i, j) -= other(i, j);\n    return *this;\n  }\n\n\
    \  template <size_t M> Matrix<T, R, M> &operator*=(const Matrix<T, C, M> &other)\
    \ {\n    Matrix<T, R, M> result;\n    for (size_t i = 0; i < R; ++i)\n      for\
    \ (size_t j = 0; j < M; ++j)\n        for (size_t k = 0; k < C; ++k)\n       \
    \   result(i, j) += data(i, k) * other(k, j);\n    return *this = result;\n  }\n\
    \n  friend Matrix<T, R, C> operator+(const Matrix<T, R, C> &a, const Matrix<T,\
    \ R, C> &b) {\n    Matrix<T, R, C> result;\n    for (size_t i = 0; i < R; ++i)\n\
    \      for (size_t j = 0; j < C; ++j)\n        result(i, j) = a(i, j) + b(i, j);\n\
    \    return result;\n  }\n\n  friend Matrix<T, R, C> operator-(const Matrix<T,\
    \ R, C> &a, const Matrix<T, R, C> &b) {\n    Matrix<T, R, C> result;\n    for\
    \ (size_t i = 0; i < R; ++i)\n      for (size_t j = 0; j < C; ++j)\n        result(i,\
    \ j) = a(i, j) - b(i, j);\n    return result;\n  }\n\n  template <size_t M>\n\
    \  friend Matrix<T, R, C> operator*(const Matrix<T, R, M> &a, const Matrix<T,\
    \ M, C> &b) {\n    Matrix<T, R, C> result;\n    for (size_t i = 0; i < R; ++i)\n\
    \      for (size_t j = 0; j < C; ++j)\n        for (size_t k = 0; k < M; ++k)\n\
    \          result(i, j) += a(i, k) * b(k, j);\n    return result;\n  }\n};\n\n\
    template <typename T> struct NMatrix {\n  narray<T, 2> data;\n\n  NMatrix(size_t\
    \ rows, size_t cols) : data(rows, cols) {}\n\n  template <size_t R, size_t C>\
    \ NMatrix(const Matrix<T, R, C> &matrix) : data(R, C) {\n    for (size_t i = 0;\
    \ i < R; ++i)\n      for (size_t j = 0; j < C; ++j)\n        data(i, j) = matrix(i,\
    \ j);\n  }\n\n  /**\n   * @brief Access element at specified row and column.\n\
    \   * @param row Row index.\n   * @param col Column index.\n   * @return Reference\
    \ to the element at the specified row and column.\n   */\n  constexpr const T\
    \ &operator()(size_t row, size_t col) const { return data(row, col); }\n\n  /**\n\
    \   * @brief Access element at specified row and column.\n   * @param row Row\
    \ index.\n   * @param col Column index.\n   * @return Reference to the element\
    \ at the specified row and column.\n   */\n  T &operator()(size_t row, size_t\
    \ col) { return data(row, col); }\n\n  NMatrix<T> &operator+=(const NMatrix<T>\
    \ &other) {\n    if (data.shape != other.data.shape)\n      throw std::invalid_argument(\"\
    Matrix dimensions do not match for addition.\");\n    for (size_t i = 0; i < data.shape[0];\
    \ ++i)\n      for (size_t j = 0; j < data.shape[1]; ++j)\n        data(i, j) +=\
    \ other(i, j);\n    return *this;\n  }\n\n  NMatrix<T> &operator-=(const NMatrix<T>\
    \ &other) {\n    if (data.shape != other.data.shape)\n      throw std::invalid_argument(\"\
    Matrix dimensions do not match for subtraction.\");\n    for (size_t i = 0; i\
    \ < data.shape[0]; ++i)\n      for (size_t j = 0; j < data.shape[1]; ++j)\n  \
    \      data(i, j) -= other(i, j);\n    return *this;\n  }\n\n  NMatrix<T> &operator*=(const\
    \ NMatrix<T> &other) {\n    if (data.shape[1] != other.data.shape[0])\n      throw\
    \ std::invalid_argument(\"Matrix dimensions do not match for multiplication.\"\
    );\n    size_t R = data.shape[0];\n    size_t C = other.data.shape[1];\n    size_t\
    \ K = data.shape[1];\n    NMatrix<T> result(R, C);\n    for (size_t i = 0; i <\
    \ R; ++i)\n      for (size_t k = 0; k < K; ++k)\n        for (size_t j = 0; j\
    \ < C; ++j)\n          result(i, j) += data(i, k) * other(k, j);\n    return *this\
    \ = result;\n  }\n\n  friend NMatrix<T> operator+(const NMatrix<T> &a, const NMatrix<T>\
    \ &b) {\n    if (a.data.shape != b.data.shape)\n      throw std::invalid_argument(\"\
    Matrix dimensions do not match for addition.\");\n    NMatrix<T> result(a.data.shape[0],\
    \ a.data.shape[1]);\n    for (size_t i = 0; i < a.data.shape[0]; ++i)\n      for\
    \ (size_t j = 0; j < a.data.shape[1]; ++j)\n        result(i, j) = a(i, j) + b(i,\
    \ j);\n    return result;\n  }\n\n  friend NMatrix<T> operator-(const NMatrix<T>\
    \ &a, const NMatrix<T> &b) {\n    if (a.data.shape != b.data.shape)\n      throw\
    \ std::invalid_argument(\"Matrix dimensions do not match for subtraction.\");\n\
    \    NMatrix<T> result(a.data.shape[0], a.data.shape[1]);\n    for (size_t i =\
    \ 0; i < a.data.shape[0]; ++i)\n      for (size_t j = 0; j < a.data.shape[1];\
    \ ++j)\n        result(i, j) = a(i, j) - b(i, j);\n    return result;\n  }\n\n\
    \  friend NMatrix<T> operator*(const NMatrix<T> &a, const NMatrix<T> &b) {\n \
    \   if (a.data.shape[1] != b.data.shape[0])\n      throw std::invalid_argument(\"\
    Matrix dimensions do not match for multiplication.\");\n    size_t R = a.data.shape[0];\n\
    \    size_t C = b.data.shape[1];\n    size_t K = a.data.shape[1];\n    NMatrix<T>\
    \ result(R, C);\n    for (size_t i = 0; i < R; ++i)\n      for (size_t k = 0;\
    \ k < K; ++k)\n        for (size_t j = 0; j < C; ++j)\n          result(i, j)\
    \ += a(i, k) * b(k, j);\n    return result;\n  }\n};\n} // namespace weilycoder\n\
    \n#endif\n"
  dependsOn:
  - weilycoder/ds/narray.hpp
  isVerificationFile: false
  path: weilycoder/matrix.hpp
  requiredBy: []
  timestamp: '2025-11-11 19:29:27+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/matrix_product.test.cpp
documentation_of: weilycoder/matrix.hpp
layout: document
redirect_from:
- /library/weilycoder/matrix.hpp
- /library/weilycoder/matrix.hpp.html
title: Matrix implementation using narray
---
