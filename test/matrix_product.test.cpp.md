---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: weilycoder/ds/narray.hpp
    title: N-dimensional array (narray)
  - icon: ':heavy_check_mark:'
    path: weilycoder/matrix.hpp
    title: Matrix implementation using narray
  - icon: ':heavy_check_mark:'
    path: weilycoder/number_theory/mod_utility.hpp
    title: Modular Arithmetic Utilities
  - icon: ':heavy_check_mark:'
    path: weilycoder/number_theory/modint.hpp
    title: Modular Integer Class
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/matrix_product
    links:
    - https://judge.yosupo.jp/problem/matrix_product
  bundledCode: "#line 1 \"test/matrix_product.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/matrix_product\"\
    \n\n#line 1 \"weilycoder/matrix.hpp\"\n\n\n\n/**\n * @file matrix.hpp\n * @brief\
    \ Matrix implementation using narray\n */\n\n#line 1 \"weilycoder/ds/narray.hpp\"\
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
    \n\n#line 1 \"weilycoder/number_theory/modint.hpp\"\n\n\n\n/**\n * @file modint.hpp\n\
    \ * @brief Modular Integer Class\n */\n\n#line 1 \"weilycoder/number_theory/mod_utility.hpp\"\
    \n\n\n\n/**\n * @file mod_utility.hpp\n * @brief Modular Arithmetic Utilities\n\
    \ */\n\n#include <cstdint>\n\nnamespace weilycoder {\nusing u128 = unsigned __int128;\n\
    \n/**\n * @brief Perform modular addition for 64-bit integers.\n * @tparam bit32\
    \ If true, won't use 128-bit arithmetic. You should ensure that\n *         all\
    \ inputs are small enough to avoid overflow (i.e. bit-32).\n * @param a The first\
    \ addend.\n * @param b The second addend.\n * @param modulus The modulus.\n *\
    \ @return (a + b) % modulus\n */\ntemplate <bool bit32 = false>\nconstexpr uint64_t\
    \ mod_add(uint64_t a, uint64_t b, uint64_t modulus) {\n  if constexpr (bit32)\
    \ {\n    uint64_t res = a + b;\n    if (res >= modulus)\n      res -= modulus;\n\
    \    return res;\n  } else {\n    u128 res = static_cast<u128>(a) + b;\n    if\
    \ (res >= modulus)\n      res -= modulus;\n    return res;\n  }\n}\n\n/**\n *\
    \ @brief Perform modular addition for 64-bit integers with a compile-time\n *\
    \        modulus.\n * @tparam Modulus The modulus.\n * @param a The first addend.\n\
    \ * @param b The second addend.\n * @return (a + b) % Modulus\n */\ntemplate <uint64_t\
    \ Modulus> constexpr uint64_t mod_add(uint64_t a, uint64_t b) {\n  if constexpr\
    \ (Modulus <= UINT32_MAX) {\n    uint64_t res = a + b;\n    if (res >= Modulus)\n\
    \      res -= Modulus;\n    return res;\n  } else {\n    u128 res = static_cast<u128>(a)\
    \ + b;\n    if (res >= Modulus)\n      res -= Modulus;\n    return res;\n  }\n\
    }\n\n/**\n * @brief Perform modular subtraction for 64-bit integers.\n * @tparam\
    \ bit32 If true, won't use 128-bit arithmetic. You should ensure that\n *    \
    \     all inputs are small enough to avoid overflow (i.e. bit-32).\n * @param\
    \ a The minuend.\n * @param b The subtrahend.\n * @param modulus The modulus.\n\
    \ * @return (a - b) % modulus\n */\ntemplate <bool bit32 = false>\nconstexpr uint64_t\
    \ mod_sub(uint64_t a, uint64_t b, uint64_t modulus) {\n  if constexpr (bit32)\
    \ {\n    uint64_t res = (a >= b) ? (a - b) : (modulus + a - b);\n    return res;\n\
    \  } else {\n    u128 res = (a >= b) ? (a - b) : (static_cast<u128>(modulus) +\
    \ a - b);\n    return res;\n  }\n}\n\n/**\n * @brief Perform modular subtraction\
    \ for 64-bit integers with a compile-time\n *        modulus.\n * @tparam Modulus\
    \ The modulus.\n * @param a The minuend.\n * @param b The subtrahend.\n * @return\
    \ (a - b) % Modulus\n */\ntemplate <uint64_t Modulus> constexpr uint64_t mod_sub(uint64_t\
    \ a, uint64_t b) {\n  if constexpr (Modulus <= UINT32_MAX) {\n    uint64_t res\
    \ = (a >= b) ? (a - b) : (Modulus + a - b);\n    return res;\n  } else {\n   \
    \ u128 res = (a >= b) ? (a - b) : (static_cast<u128>(Modulus) + a - b);\n    return\
    \ res;\n  }\n}\n\n/**\n * @brief Perform modular multiplication for 64-bit integers.\n\
    \ * @tparam bit32 If true, won't use 128-bit arithmetic. You should ensure that\n\
    \ *         all inputs are small enough to avoid overflow (i.e. bit-32).\n * @param\
    \ a The first multiplicand.\n * @param b The second multiplicand.\n * @param modulus\
    \ The modulus.\n * @return (a * b) % modulus\n */\ntemplate <bool bit32 = false>\n\
    constexpr uint64_t mod_mul(uint64_t a, uint64_t b, uint64_t modulus) {\n  if constexpr\
    \ (bit32)\n    return a * b % modulus;\n  else\n    return static_cast<u128>(a)\
    \ * b % modulus;\n}\n\n/**\n * @brief Perform modular multiplication for 64-bit\
    \ integers with a compile-time\n *        modulus.\n * @tparam Modulus The modulus.\n\
    \ * @param a The first multiplicand.\n * @param b The second multiplicand.\n *\
    \ @return (a * b) % Modulus\n */\ntemplate <uint64_t Modulus> constexpr uint64_t\
    \ mod_mul(uint64_t a, uint64_t b) {\n  if constexpr (Modulus <= UINT32_MAX)\n\
    \    return a * b % Modulus;\n  else\n    return static_cast<u128>(a) * b % Modulus;\n\
    }\n\n/**\n * @brief Perform modular exponentiation for 64-bit integers.\n * @tparam\
    \ bit32 If true, won't use 128-bit arithmetic. You should ensure that\n *    \
    \     all inputs are small enough to avoid overflow (i.e. bit-32).\n * @param\
    \ base The base number.\n * @param exponent The exponent.\n * @param modulus The\
    \ modulus.\n * @return (base^exponent) % modulus\n */\ntemplate <bool bit32 =\
    \ false>\nconstexpr uint64_t mod_pow(uint64_t base, uint64_t exponent, uint64_t\
    \ modulus) {\n  uint64_t result = 1 % modulus;\n  base %= modulus;\n  while (exponent\
    \ > 0) {\n    if (exponent & 1)\n      result = mod_mul<bit32>(result, base, modulus);\n\
    \    base = mod_mul<bit32>(base, base, modulus);\n    exponent >>= 1;\n  }\n \
    \ return result;\n}\n\n/**\n * @brief Perform modular exponentiation for 64-bit\
    \ integers with a compile-time\n *        modulus.\n * @tparam Modulus The modulus.\n\
    \ * @param base The base number.\n * @param exponent The exponent.\n * @return\
    \ (base^exponent) % Modulus\n */\ntemplate <uint64_t Modulus>\nconstexpr uint64_t\
    \ mod_pow(uint64_t base, uint64_t exponent) {\n  uint64_t result = 1 % Modulus;\n\
    \  base %= Modulus;\n  while (exponent > 0) {\n    if (exponent & 1)\n      result\
    \ = mod_mul<Modulus>(result, base);\n    base = mod_mul<Modulus>(base, base);\n\
    \    exponent >>= 1;\n  }\n  return result;\n}\n\n/**\n * @brief Compute the modular\
    \ inverse of a 64-bit integer using Fermat's Little\n *        Theorem.\n * @tparam\
    \ Modulus The modulus (must be prime).\n * @param a The number to find the modular\
    \ inverse of.\n * @return The modular inverse of a modulo Modulus.\n */\ntemplate\
    \ <uint64_t Modulus> constexpr uint64_t mod_inv(uint64_t a) {\n  return mod_pow<Modulus>(a,\
    \ Modulus - 2);\n}\n\n/**\n * @brief Compute the modular inverse of a compile-time\
    \ 64-bit integer using\n *        Fermat's Little Theorem.\n * @tparam Modulus\
    \ The modulus (must be prime).\n * @tparam a The number to find the modular inverse\
    \ of.\n * @return The modular inverse of a modulo Modulus.\n */\ntemplate <uint64_t\
    \ Modulus, uint64_t a> constexpr uint64_t mod_inv() {\n  return mod_pow<Modulus>(a,\
    \ Modulus - 2);\n}\n} // namespace weilycoder\n\n\n#line 11 \"weilycoder/number_theory/modint.hpp\"\
    \n#include <istream>\n#include <ostream>\n\nnamespace weilycoder {\n/**\n * @brief\
    \ Modular Integer with compile-time modulus.\n * @tparam Modulus The modulus.\n\
    \ */\ntemplate <uint64_t Modulus> struct modint {\nprivate:\n  uint64_t value;\n\
    \npublic:\n  constexpr modint() : value(0) {}\n  constexpr modint(uint32_t v)\
    \ : value(v % Modulus) {}\n  constexpr modint(int32_t v) { from_i64(v); }\n  constexpr\
    \ modint(uint64_t v) : value(v % Modulus) {}\n  constexpr modint(int64_t v) {\
    \ from_i64(v); }\n\n  constexpr void from_i64(int64_t v) {\n    int64_t x = v\
    \ % static_cast<int64_t>(Modulus);\n    if (x < 0)\n      x += Modulus;\n    value\
    \ = static_cast<uint64_t>(x);\n  }\n\n  explicit operator uint64_t() const { return\
    \ value; }\n\n  friend constexpr modint<Modulus> operator+(const modint<Modulus>\
    \ &lhs,\n                                             const modint<Modulus> &rhs)\
    \ {\n    return modint<Modulus>(mod_add<Modulus>(lhs.value, rhs.value));\n  }\n\
    \n  friend constexpr modint<Modulus> operator-(const modint<Modulus> &lhs,\n \
    \                                            const modint<Modulus> &rhs) {\n \
    \   return modint<Modulus>(mod_sub<Modulus>(lhs.value, rhs.value));\n  }\n\n \
    \ friend constexpr modint<Modulus> operator*(const modint<Modulus> &lhs,\n   \
    \                                          const modint<Modulus> &rhs) {\n   \
    \ return modint<Modulus>(mod_mul<Modulus>(lhs.value, rhs.value));\n  }\n\n  modint\
    \ &operator+=(const modint &other) {\n    value = mod_add<Modulus>(value, other.value);\n\
    \    return *this;\n  }\n\n  modint &operator-=(const modint &other) {\n    value\
    \ = mod_sub<Modulus>(value, other.value);\n    return *this;\n  }\n\n  modint\
    \ &operator*=(const modint &other) {\n    value = mod_mul<Modulus>(value, other.value);\n\
    \    return *this;\n  }\n\n  friend std::ostream &operator<<(std::ostream &os,\
    \ const modint &m) {\n    return os << m.value;\n  }\n\n  friend std::istream\
    \ &operator>>(std::istream &is, modint &m) {\n    int64_t v;\n    is >> v;\n \
    \   m.from_i64(v);\n    return is;\n  }\n};\n} // namespace weilycoder\n\n\n#line\
    \ 6 \"test/matrix_product.test.cpp\"\n#include <iostream>\nusing namespace std;\n\
    using namespace weilycoder;\n\nint main() {\n  cin.tie(nullptr)->sync_with_stdio(false);\n\
    \  cin.exceptions(cin.failbit | cin.badbit);\n  size_t N, M, K;\n  cin >> N >>\
    \ M >> K;\n  NMatrix<modint<998244353>> A(N, M), B(M, K);\n  for (size_t i = 0;\
    \ i < N; ++i)\n    for (size_t j = 0; j < M; ++j)\n      cin >> A(i, j);\n  for\
    \ (size_t i = 0; i < M; ++i)\n    for (size_t j = 0; j < K; ++j)\n      cin >>\
    \ B(i, j);\n  auto C = A * B;\n  for (size_t i = 0; i < N; ++i)\n    for (size_t\
    \ j = 0; j < K; ++j)\n      cout << C(i, j) << \" \\n\"[j + 1 == K];\n  return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/matrix_product\"\n\n#include\
    \ \"../weilycoder/matrix.hpp\"\n#include \"../weilycoder/number_theory/modint.hpp\"\
    \n#include <cstdint>\n#include <iostream>\nusing namespace std;\nusing namespace\
    \ weilycoder;\n\nint main() {\n  cin.tie(nullptr)->sync_with_stdio(false);\n \
    \ cin.exceptions(cin.failbit | cin.badbit);\n  size_t N, M, K;\n  cin >> N >>\
    \ M >> K;\n  NMatrix<modint<998244353>> A(N, M), B(M, K);\n  for (size_t i = 0;\
    \ i < N; ++i)\n    for (size_t j = 0; j < M; ++j)\n      cin >> A(i, j);\n  for\
    \ (size_t i = 0; i < M; ++i)\n    for (size_t j = 0; j < K; ++j)\n      cin >>\
    \ B(i, j);\n  auto C = A * B;\n  for (size_t i = 0; i < N; ++i)\n    for (size_t\
    \ j = 0; j < K; ++j)\n      cout << C(i, j) << \" \\n\"[j + 1 == K];\n  return\
    \ 0;\n}"
  dependsOn:
  - weilycoder/matrix.hpp
  - weilycoder/ds/narray.hpp
  - weilycoder/number_theory/modint.hpp
  - weilycoder/number_theory/mod_utility.hpp
  isVerificationFile: true
  path: test/matrix_product.test.cpp
  requiredBy: []
  timestamp: '2025-11-11 19:32:33+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/matrix_product.test.cpp
layout: document
redirect_from:
- /verify/test/matrix_product.test.cpp
- /verify/test/matrix_product.test.cpp.html
title: test/matrix_product.test.cpp
---
