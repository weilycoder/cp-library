#ifndef WEILYCODER_DS_NARRAY_HPP
#define WEILYCODER_DS_NARRAY_HPP

/**
 * @file narray.hpp
 * @brief N-dimensional array (narray)
 */

#include <array>
#include <cstddef>
#include <initializer_list>
#include <vector>

namespace weilycoder {
/**
 * @brief N-dimensional array (narray) implementation.
 * @tparam T Type of elements stored in the narray.
 * @tparam D Number of dimensions.
 */
template <typename T, size_t D> struct narray {
  const std::array<size_t, D> shape;
  std::vector<T> data;

  /**
   * @brief Constructor to initialize narray with given dimensions.
   * @tparam Sizes Parameter pack for sizes of each dimension.
   * @param sizes Sizes of each dimension.
   */
  template <typename... Sizes>
  narray(Sizes... sizes) : shape{static_cast<size_t>(sizes)...} {
    static_assert(sizeof...(Sizes) == D, "Number of sizes must match dimensions.");
    data.resize(size());
  }

  /**
   * @brief Get the total number of elements in the narray.
   * @return Total number of elements.
   */
  size_t size() const {
    size_t res = 1;
    for (size_t i = 0; i < D; ++i)
      res *= shape[i];
    return res;
  }

  /**
   * @brief Compute the linear index from multi-dimensional indices.
   * @tparam Indices Parameter pack for indices in each dimension.
   * @param indices Indices in each dimension.
   * @return Linear index corresponding to the multi-dimensional indices.
   */
  template <typename... Indices> size_t _index(Indices... indices) const {
    static_assert(sizeof...(Indices) == D, "Number of indices must match dimensions.");
    const size_t idxs[] = {static_cast<size_t>(indices)...};
    size_t res = 0;
    for (size_t i = 0; i < D; ++i)
      res = res * shape[i] + idxs[i];
    return res;
  }

  /**
   * @brief Access element at specified multi-dimensional indices.
   * @tparam Indices Parameter pack for indices in each dimension.
   * @param indices Indices in each dimension.
   * @return Reference to the element at the specified indices.
   */
  template <typename... Indices> const T &operator()(Indices... indices) const {
    return data[_index(indices...)];
  }

  /**
   * @brief Access element at specified multi-dimensional indices.
   * @tparam Indices Parameter pack for indices in each dimension.
   * @param indices Indices in each dimension.
   * @return Reference to the element at the specified indices.
   */
  template <typename... Indices> T &operator()(Indices... indices) {
    return data[_index(indices...)];
  }
};
} // namespace weilycoder

#endif
