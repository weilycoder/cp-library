---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: weilycoder/ds/bitset.hpp
    title: Run-time sized bitset
  - icon: ':heavy_check_mark:'
    path: weilycoder/ds/narray.hpp
    title: N-dimensional array (narray)
  - icon: ':heavy_check_mark:'
    path: weilycoder/matrix.hpp
    title: Matrix implementation using narray
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/matrix_product_mod_2
    links:
    - https://judge.yosupo.jp/problem/matrix_product_mod_2
  bundledCode: "#line 1 \"test/matrix_product_mod_2.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/matrix_product_mod_2\"\n\n#line 1 \"weilycoder/matrix.hpp\"\
    \n\n\n\n/**\n * @file matrix.hpp\n * @brief Matrix implementation using narray\n\
    \ */\n\n#line 1 \"weilycoder/ds/bitset.hpp\"\n\n\n\n/**\n * @file bitset.hpp\n\
    \ * @brief Run-time sized bitset\n */\n\n#include <cstdint>\n#include <stdexcept>\n\
    #include <vector>\n\nnamespace weilycoder {\n/**\n * @class dbitset\n * @brief\
    \ Run-time sized bitset implementation\n */\nclass dbitset {\nprivate:\n  const\
    \ size_t bitsize;\n  std::vector<uint64_t> bits;\n\n  size_t extra_size() const\
    \ { return bits.size() * 64 - bitsize; }\n\n  uint64_t extra_mask() const {\n\
    \    size_t extra = extra_size();\n    return extra ? ((1ULL << (64 - extra))\
    \ - 1) : ~0ULL;\n  }\n\n  void trim_extra() { bits.back() &= extra_mask(); }\n\
    \npublic:\n  dbitset(size_t n) : bitsize(n), bits((n + 63) / 64, 0) {}\n  dbitset(const\
    \ dbitset &other) : bitsize(other.bitsize), bits(other.bits) {}\n\n  dbitset &operator=(const\
    \ dbitset &other) {\n    if (this != &other) {\n      if (bitsize != other.bitsize)\n\
    \        throw std::invalid_argument(\"Bitset sizes do not match for assignment.\"\
    );\n      bits = other.bits;\n    }\n    return *this;\n  }\n\n  struct reference\
    \ {\n    dbitset &bs;\n    size_t pos;\n\n    reference(dbitset &bs, size_t pos)\
    \ : bs(bs), pos(pos) {}\n\n    operator bool() const {\n      size_t idx = pos\
    \ / 64;\n      size_t bit = pos % 64;\n      return (bs.bits[idx] >> bit) & 1ULL;\n\
    \    }\n\n    reference &operator=(bool val) {\n      size_t idx = pos / 64;\n\
    \      size_t bit = pos % 64;\n      if (val)\n        bs.bits[idx] |= (1ULL <<\
    \ bit);\n      else\n        bs.bits[idx] &= ~(1ULL << bit);\n      return *this;\n\
    \    }\n  };\n\n  struct const_reference {\n    const dbitset &bs;\n    size_t\
    \ pos;\n\n    const_reference(const dbitset &bs, size_t pos) : bs(bs), pos(pos)\
    \ {}\n\n    operator bool() const {\n      size_t idx = pos / 64;\n      size_t\
    \ bit = pos % 64;\n      return (bs.bits[idx] >> bit) & 1ULL;\n    }\n  };\n\n\
    \  struct iterator {\n    dbitset &bs;\n    size_t pos;\n\n    iterator(dbitset\
    \ &bs, size_t pos) : bs(bs), pos(pos) {}\n    bool operator!=(const iterator &other)\
    \ const { return pos != other.pos; }\n    reference operator*() { return reference(bs,\
    \ pos); }\n    iterator &operator++() { return ++pos, *this; }\n    iterator operator++(int)\
    \ {\n      iterator temp = *this;\n      ++pos;\n      return temp;\n    }\n \
    \ };\n\n  struct const_iterator {\n    const dbitset &bs;\n    size_t pos;\n\n\
    \    const_iterator(const dbitset &bs, size_t pos) : bs(bs), pos(pos) {}\n   \
    \ bool operator!=(const const_iterator &other) const { return pos != other.pos;\
    \ }\n    const_reference operator*() const { return const_reference(bs, pos);\
    \ }\n    const_iterator &operator++() { return ++pos, *this; }\n    const_iterator\
    \ operator++(int) {\n      const_iterator temp = *this;\n      ++pos;\n      return\
    \ temp;\n    }\n  };\n\n  iterator begin() { return iterator(*this, 0); }\n  iterator\
    \ end() { return iterator(*this, bitsize); }\n  const_iterator begin() const {\
    \ return const_iterator(*this, 0); }\n  const_iterator end() const { return const_iterator(*this,\
    \ bitsize); }\n\n  reference operator[](size_t pos) { return reference(*this,\
    \ pos); }\n  const_reference operator[](size_t pos) const { return const_reference(*this,\
    \ pos); }\n\n  size_t size() const { return bitsize; }\n\n  size_t d_size() const\
    \ { return bits.size(); }\n  uint64_t &d_get_word(size_t idx) { return bits[idx];\
    \ }\n  const uint64_t &d_get_word(size_t idx) const { return bits[idx]; }\n\n\
    \  dbitset &operator&=(const dbitset &other) {\n    if (bitsize != other.bitsize)\n\
    \      throw std::invalid_argument(\"Bitset sizes do not match for AND operation.\"\
    );\n    for (size_t i = 0; i < bits.size(); ++i)\n      bits[i] &= other.bits[i];\n\
    \    return this->trim_extra(), *this;\n  }\n\n  dbitset &operator|=(const dbitset\
    \ &other) {\n    if (bitsize != other.bitsize)\n      throw std::invalid_argument(\"\
    Bitset sizes do not match for OR operation.\");\n    for (size_t i = 0; i < bits.size();\
    \ ++i)\n      bits[i] |= other.bits[i];\n    return this->trim_extra(), *this;\n\
    \  }\n\n  dbitset &operator^=(const dbitset &other) {\n    if (bitsize != other.bitsize)\n\
    \      throw std::invalid_argument(\"Bitset sizes do not match for XOR operation.\"\
    );\n    for (size_t i = 0; i < bits.size(); ++i)\n      bits[i] ^= other.bits[i];\n\
    \    return this->trim_extra(), *this;\n  }\n\n  dbitset &operator<<=(size_t shift)\
    \ {\n    if (shift >= bitsize) {\n      std::fill(bits.begin(), bits.end(), 0);\n\
    \      return *this;\n    }\n    size_t word_shift = shift / 64;\n    size_t bit_shift\
    \ = shift % 64;\n    if (bit_shift == 0) {\n      for (size_t i = bits.size()\
    \ - 1; i >= word_shift; --i)\n        bits[i] = bits[i - word_shift];\n    } else\
    \ {\n      for (size_t i = bits.size() - 1; i > word_shift; --i)\n        bits[i]\
    \ = (bits[i - word_shift] << bit_shift) |\n                  (bits[i - word_shift\
    \ - 1] >> (64 - bit_shift));\n      bits[word_shift] = bits[0] << bit_shift;\n\
    \    }\n    std::fill(bits.begin(), bits.begin() + word_shift, 0);\n    return\
    \ this->trim_extra(), *this;\n  }\n\n  dbitset &operator>>=(size_t shift) {\n\
    \    if (shift >= bitsize) {\n      std::fill(bits.begin(), bits.end(), 0);\n\
    \      return *this;\n    }\n    size_t word_shift = shift / 64;\n    size_t bit_shift\
    \ = shift % 64;\n    size_t n = bits.size();\n    if (bit_shift == 0) {\n    \
    \  for (size_t i = 0; i < n - word_shift; ++i)\n        bits[i] = bits[i + word_shift];\n\
    \    } else {\n      for (size_t i = 0; i < n - word_shift - 1; ++i)\n       \
    \ bits[i] = (bits[i + word_shift] >> bit_shift) |\n                  (bits[i +\
    \ word_shift + 1] << (64 - bit_shift));\n      bits[n - word_shift - 1] = bits[n\
    \ - 1] >> bit_shift;\n    }\n    std::fill(bits.end() - word_shift, bits.end(),\
    \ 0);\n    return *this;\n  }\n\n  friend dbitset operator~(const dbitset &bs)\
    \ {\n    dbitset result(bs.bitsize);\n    for (size_t i = 0; i < bs.bits.size();\
    \ ++i)\n      result.bits[i] = ~bs.bits[i];\n    return result.trim_extra(), result;\n\
    \  }\n\n  friend dbitset operator&(const dbitset &a, const dbitset &b) {\n   \
    \ if (a.bitsize != b.bitsize)\n      throw std::invalid_argument(\"Bitset sizes\
    \ do not match for AND operation.\");\n    dbitset result(a.bitsize);\n    for\
    \ (size_t i = 0; i < a.bits.size(); ++i)\n      result.bits[i] = a.bits[i] & b.bits[i];\n\
    \    return result.trim_extra(), result;\n  }\n\n  friend dbitset operator|(const\
    \ dbitset &a, const dbitset &b) {\n    if (a.bitsize != b.bitsize)\n      throw\
    \ std::invalid_argument(\"Bitset sizes do not match for OR operation.\");\n  \
    \  dbitset result(a.bitsize);\n    for (size_t i = 0; i < a.bits.size(); ++i)\n\
    \      result.bits[i] = a.bits[i] | b.bits[i];\n    return result.trim_extra(),\
    \ result;\n  }\n\n  friend dbitset operator^(const dbitset &a, const dbitset &b)\
    \ {\n    if (a.bitsize != b.bitsize)\n      throw std::invalid_argument(\"Bitset\
    \ sizes do not match for XOR operation.\");\n    dbitset result(a.bitsize);\n\
    \    for (size_t i = 0; i < a.bits.size(); ++i)\n      result.bits[i] = a.bits[i]\
    \ ^ b.bits[i];\n    return result.trim_extra(), result;\n  }\n\n  friend dbitset\
    \ operator<<(const dbitset &bs, size_t shift) {\n    dbitset result = bs;\n  \
    \  return result <<= shift, result;\n  }\n\n  friend dbitset operator>>(const\
    \ dbitset &bs, size_t shift) {\n    dbitset result = bs;\n    return result >>=\
    \ shift, result;\n  }\n};\n} // namespace weilycoder\n\n\n#line 1 \"weilycoder/ds/narray.hpp\"\
    \n\n\n\n/**\n * @file narray.hpp\n * @brief N-dimensional array (narray)\n */\n\
    \n#include <array>\n#include <cstddef>\n#include <initializer_list>\n#line 13\
    \ \"weilycoder/ds/narray.hpp\"\n\nnamespace weilycoder {\n/**\n * @brief N-dimensional\
    \ array (narray) implementation.\n * @tparam T Type of elements stored in the\
    \ narray.\n * @tparam D Number of dimensions.\n */\ntemplate <typename T, size_t\
    \ D> struct narray {\n  const std::array<size_t, D> shape;\n  std::vector<T> data;\n\
    \n  /**\n   * @brief Constructor to initialize narray with given dimensions.\n\
    \   * @tparam Sizes Parameter pack for sizes of each dimension.\n   * @param sizes\
    \ Sizes of each dimension.\n   */\n  template <typename... Sizes>\n  narray(Sizes...\
    \ sizes) : shape{static_cast<size_t>(sizes)...} {\n    static_assert(sizeof...(Sizes)\
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
    #line 14 \"weilycoder/matrix.hpp\"\n\nnamespace weilycoder {\ntemplate <typename\
    \ T, size_t R, size_t C> struct Matrix {\n  T data[R][C];\n\n  Matrix() : data{}\
    \ {}\n  Matrix(std::initializer_list<T> init) {\n    size_t i = 0, j = 0;\n  \
    \  for (const auto &val : init) {\n      data[i][j] = val;\n      if (++j == C)\n\
    \        j = 0, ++i;\n    }\n  }\n\n  /**\n   * @brief Access element at specified\
    \ row and column.\n   * @param row Row index.\n   * @param col Column index.\n\
    \   * @return Reference to the element at the specified row and column.\n   */\n\
    \  constexpr const T &operator()(size_t row, size_t col) const { return data[row][col];\
    \ }\n\n  /**\n   * @brief Access element at specified row and column.\n   * @param\
    \ row Row index.\n   * @param col Column index.\n   * @return Reference to the\
    \ element at the specified row and column.\n   */\n  T &operator()(size_t row,\
    \ size_t col) { return data[row][col]; }\n\n  Matrix<T, R, C> &operator+=(const\
    \ Matrix<T, R, C> &other) {\n    for (size_t i = 0; i < R; ++i)\n      for (size_t\
    \ j = 0; j < C; ++j)\n        data(i, j) += other(i, j);\n    return *this;\n\
    \  }\n\n  Matrix<T, R, C> &operator-=(const Matrix<T, R, C> &other) {\n    for\
    \ (size_t i = 0; i < R; ++i)\n      for (size_t j = 0; j < C; ++j)\n        data(i,\
    \ j) -= other(i, j);\n    return *this;\n  }\n\n  template <size_t M> Matrix<T,\
    \ R, M> &operator*=(const Matrix<T, C, M> &other) {\n    Matrix<T, R, M> result;\n\
    \    for (size_t i = 0; i < R; ++i)\n      for (size_t j = 0; j < M; ++j)\n  \
    \      for (size_t k = 0; k < C; ++k)\n          result(i, j) += data(i, k) *\
    \ other(k, j);\n    return *this = result;\n  }\n\n  friend Matrix<T, R, C> operator+(const\
    \ Matrix<T, R, C> &a, const Matrix<T, R, C> &b) {\n    Matrix<T, R, C> result;\n\
    \    for (size_t i = 0; i < R; ++i)\n      for (size_t j = 0; j < C; ++j)\n  \
    \      result(i, j) = a(i, j) + b(i, j);\n    return result;\n  }\n\n  friend\
    \ Matrix<T, R, C> operator-(const Matrix<T, R, C> &a, const Matrix<T, R, C> &b)\
    \ {\n    Matrix<T, R, C> result;\n    for (size_t i = 0; i < R; ++i)\n      for\
    \ (size_t j = 0; j < C; ++j)\n        result(i, j) = a(i, j) - b(i, j);\n    return\
    \ result;\n  }\n\n  template <size_t M>\n  friend Matrix<T, R, C> operator*(const\
    \ Matrix<T, R, M> &a, const Matrix<T, M, C> &b) {\n    Matrix<T, R, C> result;\n\
    \    for (size_t i = 0; i < R; ++i)\n      for (size_t j = 0; j < C; ++j)\n  \
    \      for (size_t k = 0; k < M; ++k)\n          result(i, j) += a(i, k) * b(k,\
    \ j);\n    return result;\n  }\n};\n\ntemplate <typename T> struct NMatrix {\n\
    \  narray<T, 2> data;\n\n  NMatrix(size_t rows, size_t cols) : data(rows, cols)\
    \ {}\n\n  template <size_t R, size_t C> NMatrix(const Matrix<T, R, C> &matrix)\
    \ : data(R, C) {\n    for (size_t i = 0; i < R; ++i)\n      for (size_t j = 0;\
    \ j < C; ++j)\n        data(i, j) = matrix(i, j);\n  }\n\n  /**\n   * @brief Access\
    \ element at specified row and column.\n   * @param row Row index.\n   * @param\
    \ col Column index.\n   * @return Reference to the element at the specified row\
    \ and column.\n   */\n  constexpr const T &operator()(size_t row, size_t col)\
    \ const { return data(row, col); }\n\n  /**\n   * @brief Access element at specified\
    \ row and column.\n   * @param row Row index.\n   * @param col Column index.\n\
    \   * @return Reference to the element at the specified row and column.\n   */\n\
    \  T &operator()(size_t row, size_t col) { return data(row, col); }\n\n  NMatrix<T>\
    \ &operator+=(const NMatrix<T> &other) {\n    if (data.shape != other.data.shape)\n\
    \      throw std::invalid_argument(\"Matrix dimensions do not match for addition.\"\
    );\n    for (size_t i = 0; i < data.shape[0]; ++i)\n      for (size_t j = 0; j\
    \ < data.shape[1]; ++j)\n        data(i, j) += other(i, j);\n    return *this;\n\
    \  }\n\n  NMatrix<T> &operator-=(const NMatrix<T> &other) {\n    if (data.shape\
    \ != other.data.shape)\n      throw std::invalid_argument(\"Matrix dimensions\
    \ do not match for subtraction.\");\n    for (size_t i = 0; i < data.shape[0];\
    \ ++i)\n      for (size_t j = 0; j < data.shape[1]; ++j)\n        data(i, j) -=\
    \ other(i, j);\n    return *this;\n  }\n\n  NMatrix<T> &operator*=(const NMatrix<T>\
    \ &other) {\n    if (data.shape[1] != other.data.shape[0])\n      throw std::invalid_argument(\"\
    Matrix dimensions do not match for multiplication.\");\n    size_t R = data.shape[0];\n\
    \    size_t C = other.data.shape[1];\n    size_t K = data.shape[1];\n    NMatrix<T>\
    \ result(R, C);\n    for (size_t i = 0; i < R; ++i)\n      for (size_t k = 0;\
    \ k < K; ++k)\n        for (size_t j = 0; j < C; ++j)\n          result(i, j)\
    \ += data(i, k) * other(k, j);\n    return *this = result;\n  }\n\n  friend NMatrix<T>\
    \ operator+(const NMatrix<T> &a, const NMatrix<T> &b) {\n    if (a.data.shape\
    \ != b.data.shape)\n      throw std::invalid_argument(\"Matrix dimensions do not\
    \ match for addition.\");\n    NMatrix<T> result(a.data.shape[0], a.data.shape[1]);\n\
    \    for (size_t i = 0; i < a.data.shape[0]; ++i)\n      for (size_t j = 0; j\
    \ < a.data.shape[1]; ++j)\n        result(i, j) = a(i, j) + b(i, j);\n    return\
    \ result;\n  }\n\n  friend NMatrix<T> operator-(const NMatrix<T> &a, const NMatrix<T>\
    \ &b) {\n    if (a.data.shape != b.data.shape)\n      throw std::invalid_argument(\"\
    Matrix dimensions do not match for subtraction.\");\n    NMatrix<T> result(a.data.shape[0],\
    \ a.data.shape[1]);\n    for (size_t i = 0; i < a.data.shape[0]; ++i)\n      for\
    \ (size_t j = 0; j < a.data.shape[1]; ++j)\n        result(i, j) = a(i, j) - b(i,\
    \ j);\n    return result;\n  }\n\n  friend NMatrix<T> operator*(const NMatrix<T>\
    \ &a, const NMatrix<T> &b) {\n    if (a.data.shape[1] != b.data.shape[0])\n  \
    \    throw std::invalid_argument(\"Matrix dimensions do not match for multiplication.\"\
    );\n    size_t R = a.data.shape[0];\n    size_t C = b.data.shape[1];\n    size_t\
    \ K = a.data.shape[1];\n    NMatrix<T> result(R, C);\n    for (size_t i = 0; i\
    \ < R; ++i)\n      for (size_t k = 0; k < K; ++k)\n        for (size_t j = 0;\
    \ j < C; ++j)\n          result(i, j) += a(i, k) * b(k, j);\n    return result;\n\
    \  }\n};\n\nstruct BMatrix {\n  size_t rows, cols;\n  std::vector<dbitset> data;\n\
    \n  BMatrix(size_t rows, size_t cols)\n      : rows(rows), cols(cols), data(rows,\
    \ dbitset(cols)) {}\n\n  /**\n   * @brief Access element at specified row and\
    \ column.\n   * @param row Row index.\n   * @param col Column index.\n   * @return\
    \ Reference to the element at the specified row and column.\n   */\n  dbitset::reference\
    \ operator()(size_t row, size_t col) { return data[row][col]; }\n\n  /**\n   *\
    \ @brief Access element at specified row and column.\n   * @param row Row index.\n\
    \   * @param col Column index.\n   * @return Reference to the element at the specified\
    \ row and column.\n   */\n  dbitset::const_reference operator()(size_t row, size_t\
    \ col) const {\n    return data[row][col];\n  }\n\n  BMatrix &operator&=(const\
    \ BMatrix &other) {\n    for (size_t i = 0; i < rows; ++i)\n      data[i] &= other.data[i];\n\
    \    return *this;\n  }\n\n  BMatrix &operator|=(const BMatrix &other) {\n   \
    \ for (size_t i = 0; i < rows; ++i)\n      data[i] |= other.data[i];\n    return\
    \ *this;\n  }\n\n  BMatrix &operator^=(const BMatrix &other) {\n    for (size_t\
    \ i = 0; i < rows; ++i)\n      data[i] ^= other.data[i];\n    return *this;\n\
    \  }\n\n  BMatrix operator*=(const BMatrix &other) {\n    if (cols != other.rows)\n\
    \      throw std::invalid_argument(\"Matrix dimensions do not match for multiplication.\"\
    );\n    BMatrix result(rows, other.cols);\n    for (size_t i = 0; i < rows; ++i)\n\
    \      for (size_t k = 0; k < cols; ++k)\n        if (data[i][k])\n          result.data[i]\
    \ ^= other.data[k];\n    return *this = result;\n  }\n\n  friend BMatrix operator&(const\
    \ BMatrix &a, const BMatrix &b) {\n    if (a.rows != b.rows || a.cols != b.cols)\n\
    \      throw std::invalid_argument(\"Matrix dimensions do not match for AND operation.\"\
    );\n    BMatrix result(a.rows, a.cols);\n    for (size_t i = 0; i < a.rows; ++i)\n\
    \      for (size_t j = 0; j < a.cols; ++j)\n        result(i, j) = static_cast<bool>(a(i,\
    \ j)) && static_cast<bool>(b(i, j));\n    return result;\n  }\n\n  friend BMatrix\
    \ operator|(const BMatrix &a, const BMatrix &b) {\n    if (a.rows != b.rows ||\
    \ a.cols != b.cols)\n      throw std::invalid_argument(\"Matrix dimensions do\
    \ not match for OR operation.\");\n    BMatrix result(a.rows, a.cols);\n    for\
    \ (size_t i = 0; i < a.rows; ++i)\n      for (size_t j = 0; j < a.cols; ++j)\n\
    \        result(i, j) = static_cast<bool>(a(i, j)) || static_cast<bool>(b(i, j));\n\
    \    return result;\n  }\n\n  friend BMatrix operator^(const BMatrix &a, const\
    \ BMatrix &b) {\n    if (a.rows != b.rows || a.cols != b.cols)\n      throw std::invalid_argument(\"\
    Matrix dimensions do not match for XOR operation.\");\n    BMatrix result(a.rows,\
    \ a.cols);\n    for (size_t i = 0; i < a.rows; ++i)\n      for (size_t j = 0;\
    \ j < a.cols; ++j)\n        result(i, j) = static_cast<bool>(a(i, j)) ^ static_cast<bool>(b(i,\
    \ j));\n    return result;\n  }\n\n  friend BMatrix operator~(const BMatrix &a)\
    \ {\n    BMatrix result(a.rows, a.cols);\n    for (size_t i = 0; i < a.rows; ++i)\n\
    \      for (size_t j = 0; j < a.cols; ++j)\n        result(i, j) = !static_cast<bool>(a(i,\
    \ j));\n    return result;\n  }\n\n  friend BMatrix operator*(const BMatrix &a,\
    \ const BMatrix &b) {\n    if (a.cols != b.rows)\n      throw std::invalid_argument(\"\
    Matrix dimensions do not match for multiplication.\");\n    BMatrix result(a.rows,\
    \ b.cols);\n    for (size_t i = 0; i < a.rows; ++i)\n      for (size_t k = 0;\
    \ k < a.cols; ++k)\n        if (a(i, k))\n          result.data[i] ^= b.data[k];\n\
    \    return result;\n  }\n};\n} // namespace weilycoder\n\n\n#line 4 \"test/matrix_product_mod_2.test.cpp\"\
    \n#include <iostream>\nusing namespace std;\nusing namespace weilycoder;\n\nint\
    \ main() {\n  cin.tie(nullptr)->sync_with_stdio(false);\n  cin.exceptions(cin.failbit\
    \ | cin.badbit);\n  size_t N, M, K;\n  cin >> N >> M >> K;\n  BMatrix A(N, M),\
    \ B(M, K);\n  for (size_t i = 0; i < N; ++i) {\n    string s;\n    cin >> s;\n\
    \    for (size_t j = 0; j < M; ++j)\n      A(i, j) = s[j] - '0';\n  }\n  for (size_t\
    \ i = 0; i < M; ++i) {\n    string s;\n    cin >> s;\n    for (size_t j = 0; j\
    \ < K; ++j)\n      B(i, j) = s[j] - '0';\n  }\n  BMatrix C = A * B;\n  for (size_t\
    \ i = 0; i < N; ++i)\n    for (size_t j = 0; j < K; ++j)\n      cout << (C(i,\
    \ j) ? 1 : 0) << (j + 1 == K ? \"\\n\" : \"\");\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/matrix_product_mod_2\"\n\
    \n#include \"../weilycoder/matrix.hpp\"\n#include <iostream>\nusing namespace\
    \ std;\nusing namespace weilycoder;\n\nint main() {\n  cin.tie(nullptr)->sync_with_stdio(false);\n\
    \  cin.exceptions(cin.failbit | cin.badbit);\n  size_t N, M, K;\n  cin >> N >>\
    \ M >> K;\n  BMatrix A(N, M), B(M, K);\n  for (size_t i = 0; i < N; ++i) {\n \
    \   string s;\n    cin >> s;\n    for (size_t j = 0; j < M; ++j)\n      A(i, j)\
    \ = s[j] - '0';\n  }\n  for (size_t i = 0; i < M; ++i) {\n    string s;\n    cin\
    \ >> s;\n    for (size_t j = 0; j < K; ++j)\n      B(i, j) = s[j] - '0';\n  }\n\
    \  BMatrix C = A * B;\n  for (size_t i = 0; i < N; ++i)\n    for (size_t j = 0;\
    \ j < K; ++j)\n      cout << (C(i, j) ? 1 : 0) << (j + 1 == K ? \"\\n\" : \"\"\
    );\n  return 0;\n}"
  dependsOn:
  - weilycoder/matrix.hpp
  - weilycoder/ds/bitset.hpp
  - weilycoder/ds/narray.hpp
  isVerificationFile: true
  path: test/matrix_product_mod_2.test.cpp
  requiredBy: []
  timestamp: '2025-11-11 20:36:03+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/matrix_product_mod_2.test.cpp
layout: document
redirect_from:
- /verify/test/matrix_product_mod_2.test.cpp
- /verify/test/matrix_product_mod_2.test.cpp.html
title: test/matrix_product_mod_2.test.cpp
---
