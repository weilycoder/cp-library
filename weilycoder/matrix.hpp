#ifndef WEILYCODER_MATRIX_HPP
#define WEILYCODER_MATRIX_HPP

/**
 * @file matrix.hpp
 * @brief Matrix implementation using narray
 */

#include "ds/bitset.hpp"
#include "ds/narray.hpp"
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace weilycoder {
template <typename T, size_t R, size_t C> struct Matrix {
  T data[R][C];

  Matrix() : data{} {}
  Matrix(std::initializer_list<T> init) {
    size_t i = 0, j = 0;
    for (const auto &val : init) {
      data[i][j] = val;
      if (++j == C)
        j = 0, ++i;
    }
  }

  /**
   * @brief Access element at specified row and column.
   * @param row Row index.
   * @param col Column index.
   * @return Reference to the element at the specified row and column.
   */
  constexpr const T &operator()(size_t row, size_t col) const { return data[row][col]; }

  /**
   * @brief Access element at specified row and column.
   * @param row Row index.
   * @param col Column index.
   * @return Reference to the element at the specified row and column.
   */
  T &operator()(size_t row, size_t col) { return data[row][col]; }

  Matrix<T, R, C> &operator+=(const Matrix<T, R, C> &other) {
    for (size_t i = 0; i < R; ++i)
      for (size_t j = 0; j < C; ++j)
        data(i, j) += other(i, j);
    return *this;
  }

  Matrix<T, R, C> &operator-=(const Matrix<T, R, C> &other) {
    for (size_t i = 0; i < R; ++i)
      for (size_t j = 0; j < C; ++j)
        data(i, j) -= other(i, j);
    return *this;
  }

  template <size_t M> Matrix<T, R, M> &operator*=(const Matrix<T, C, M> &other) {
    Matrix<T, R, M> result;
    for (size_t i = 0; i < R; ++i)
      for (size_t j = 0; j < M; ++j)
        for (size_t k = 0; k < C; ++k)
          result(i, j) += data(i, k) * other(k, j);
    return *this = result;
  }

  friend Matrix<T, R, C> operator+(const Matrix<T, R, C> &a, const Matrix<T, R, C> &b) {
    Matrix<T, R, C> result;
    for (size_t i = 0; i < R; ++i)
      for (size_t j = 0; j < C; ++j)
        result(i, j) = a(i, j) + b(i, j);
    return result;
  }

  friend Matrix<T, R, C> operator-(const Matrix<T, R, C> &a, const Matrix<T, R, C> &b) {
    Matrix<T, R, C> result;
    for (size_t i = 0; i < R; ++i)
      for (size_t j = 0; j < C; ++j)
        result(i, j) = a(i, j) - b(i, j);
    return result;
  }

  template <size_t M>
  friend Matrix<T, R, C> operator*(const Matrix<T, R, M> &a, const Matrix<T, M, C> &b) {
    Matrix<T, R, C> result;
    for (size_t i = 0; i < R; ++i)
      for (size_t j = 0; j < C; ++j)
        for (size_t k = 0; k < M; ++k)
          result(i, j) += a(i, k) * b(k, j);
    return result;
  }
};

template <typename T> struct NMatrix {
  narray<T, 2> data;

  NMatrix(size_t rows, size_t cols) : data(rows, cols) {}

  template <size_t R, size_t C> NMatrix(const Matrix<T, R, C> &matrix) : data(R, C) {
    for (size_t i = 0; i < R; ++i)
      for (size_t j = 0; j < C; ++j)
        data(i, j) = matrix(i, j);
  }

  /**
   * @brief Access element at specified row and column.
   * @param row Row index.
   * @param col Column index.
   * @return Reference to the element at the specified row and column.
   */
  constexpr const T &operator()(size_t row, size_t col) const { return data(row, col); }

  /**
   * @brief Access element at specified row and column.
   * @param row Row index.
   * @param col Column index.
   * @return Reference to the element at the specified row and column.
   */
  T &operator()(size_t row, size_t col) { return data(row, col); }

  NMatrix<T> &operator+=(const NMatrix<T> &other) {
    if (data.shape != other.data.shape)
      throw std::invalid_argument("Matrix dimensions do not match for addition.");
    for (size_t i = 0; i < data.shape[0]; ++i)
      for (size_t j = 0; j < data.shape[1]; ++j)
        data(i, j) += other(i, j);
    return *this;
  }

  NMatrix<T> &operator-=(const NMatrix<T> &other) {
    if (data.shape != other.data.shape)
      throw std::invalid_argument("Matrix dimensions do not match for subtraction.");
    for (size_t i = 0; i < data.shape[0]; ++i)
      for (size_t j = 0; j < data.shape[1]; ++j)
        data(i, j) -= other(i, j);
    return *this;
  }

  NMatrix<T> &operator*=(const NMatrix<T> &other) {
    if (data.shape[1] != other.data.shape[0])
      throw std::invalid_argument("Matrix dimensions do not match for multiplication.");
    size_t R = data.shape[0];
    size_t C = other.data.shape[1];
    size_t K = data.shape[1];
    NMatrix<T> result(R, C);
    for (size_t i = 0; i < R; ++i)
      for (size_t k = 0; k < K; ++k)
        for (size_t j = 0; j < C; ++j)
          result(i, j) += data(i, k) * other(k, j);
    return *this = result;
  }

  friend NMatrix<T> operator+(const NMatrix<T> &a, const NMatrix<T> &b) {
    if (a.data.shape != b.data.shape)
      throw std::invalid_argument("Matrix dimensions do not match for addition.");
    NMatrix<T> result(a.data.shape[0], a.data.shape[1]);
    for (size_t i = 0; i < a.data.shape[0]; ++i)
      for (size_t j = 0; j < a.data.shape[1]; ++j)
        result(i, j) = a(i, j) + b(i, j);
    return result;
  }

  friend NMatrix<T> operator-(const NMatrix<T> &a, const NMatrix<T> &b) {
    if (a.data.shape != b.data.shape)
      throw std::invalid_argument("Matrix dimensions do not match for subtraction.");
    NMatrix<T> result(a.data.shape[0], a.data.shape[1]);
    for (size_t i = 0; i < a.data.shape[0]; ++i)
      for (size_t j = 0; j < a.data.shape[1]; ++j)
        result(i, j) = a(i, j) - b(i, j);
    return result;
  }

  friend NMatrix<T> operator*(const NMatrix<T> &a, const NMatrix<T> &b) {
    if (a.data.shape[1] != b.data.shape[0])
      throw std::invalid_argument("Matrix dimensions do not match for multiplication.");
    size_t R = a.data.shape[0];
    size_t C = b.data.shape[1];
    size_t K = a.data.shape[1];
    NMatrix<T> result(R, C);
    for (size_t i = 0; i < R; ++i)
      for (size_t k = 0; k < K; ++k)
        for (size_t j = 0; j < C; ++j)
          result(i, j) += a(i, k) * b(k, j);
    return result;
  }
};

struct BMatrix {
  size_t rows, cols;
  std::vector<dbitset> data;

  BMatrix(size_t rows, size_t cols)
      : rows(rows), cols(cols), data(rows, dbitset(cols)) {}

  /**
   * @brief Access element at specified row and column.
   * @param row Row index.
   * @param col Column index.
   * @return Reference to the element at the specified row and column.
   */
  dbitset::reference operator()(size_t row, size_t col) { return data[row][col]; }

  /**
   * @brief Access element at specified row and column.
   * @param row Row index.
   * @param col Column index.
   * @return Reference to the element at the specified row and column.
   */
  dbitset::const_reference operator()(size_t row, size_t col) const {
    return data[row][col];
  }

  BMatrix &operator&=(const BMatrix &other) {
    for (size_t i = 0; i < rows; ++i)
      data[i] &= other.data[i];
    return *this;
  }

  BMatrix &operator|=(const BMatrix &other) {
    for (size_t i = 0; i < rows; ++i)
      data[i] |= other.data[i];
    return *this;
  }

  BMatrix &operator^=(const BMatrix &other) {
    for (size_t i = 0; i < rows; ++i)
      data[i] ^= other.data[i];
    return *this;
  }

  BMatrix operator*=(const BMatrix &other) {
    if (cols != other.rows)
      throw std::invalid_argument("Matrix dimensions do not match for multiplication.");
    BMatrix result(rows, other.cols);
    for (size_t i = 0; i < rows; ++i)
      for (size_t k = 0; k < cols; ++k)
        if (data[i][k])
          result.data[i] ^= other.data[k];
    return *this = result;
  }

  friend BMatrix operator&(const BMatrix &a, const BMatrix &b) {
    if (a.rows != b.rows || a.cols != b.cols)
      throw std::invalid_argument("Matrix dimensions do not match for AND operation.");
    BMatrix result(a.rows, a.cols);
    for (size_t i = 0; i < a.rows; ++i)
      for (size_t j = 0; j < a.cols; ++j)
        result(i, j) = static_cast<bool>(a(i, j)) && static_cast<bool>(b(i, j));
    return result;
  }

  friend BMatrix operator|(const BMatrix &a, const BMatrix &b) {
    if (a.rows != b.rows || a.cols != b.cols)
      throw std::invalid_argument("Matrix dimensions do not match for OR operation.");
    BMatrix result(a.rows, a.cols);
    for (size_t i = 0; i < a.rows; ++i)
      for (size_t j = 0; j < a.cols; ++j)
        result(i, j) = static_cast<bool>(a(i, j)) || static_cast<bool>(b(i, j));
    return result;
  }

  friend BMatrix operator^(const BMatrix &a, const BMatrix &b) {
    if (a.rows != b.rows || a.cols != b.cols)
      throw std::invalid_argument("Matrix dimensions do not match for XOR operation.");
    BMatrix result(a.rows, a.cols);
    for (size_t i = 0; i < a.rows; ++i)
      for (size_t j = 0; j < a.cols; ++j)
        result(i, j) = static_cast<bool>(a(i, j)) ^ static_cast<bool>(b(i, j));
    return result;
  }

  friend BMatrix operator~(const BMatrix &a) {
    BMatrix result(a.rows, a.cols);
    for (size_t i = 0; i < a.rows; ++i)
      for (size_t j = 0; j < a.cols; ++j)
        result(i, j) = !static_cast<bool>(a(i, j));
    return result;
  }

  friend BMatrix operator*(const BMatrix &a, const BMatrix &b) {
    if (a.cols != b.rows)
      throw std::invalid_argument("Matrix dimensions do not match for multiplication.");
    BMatrix result(a.rows, b.cols);
    for (size_t i = 0; i < a.rows; ++i)
      for (size_t k = 0; k < a.cols; ++k)
        if (a(i, k))
          result.data[i] ^= b.data[k];
    return result;
  }
};
} // namespace weilycoder

#endif
