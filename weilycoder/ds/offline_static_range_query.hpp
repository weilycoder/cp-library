#ifndef WEILYCODER_OFFLINE_STATIC_RANGE_QUERY_HPP
#define WEILYCODER_OFFLINE_STATIC_RANGE_QUERY_HPP

/**
 * @file offline_static_range_query.hpp
 * @brief Offline Static Range Query Data Structure
 */

#include <cstddef>
#include <numeric>
#include <stdexcept>
#include <utility>
#include <vector>

namespace weilycoder {
/**
 * @brief Offline Static Range Query Data Structure
 * @tparam Monoid The monoid defining the operation and identity
 * @tparam ptr_t The type used for indexing (default: size_t)
 */
template <typename Monoid, typename ptr_t = size_t> class OfflineStaticRangeQuery {
public:
  using T = typename Monoid::value_type;

private:
  ptr_t query_count, data_size;

  std::vector<std::vector<std::pair<ptr_t, ptr_t>>> queries;

  std::vector<T> values;
  std::vector<ptr_t> parent;

  /**
   * @brief Find with path compression and value aggregation
   * @param x The index to find
   * @return The root index after path compression
   */
  ptr_t find(ptr_t x) {
    ptr_t y = parent[x];
    if (y == x)
      return x;
    parent[x] = find(y);
    if (y != parent[x])
      values[x] = Monoid::operation(values[x], values[y]);
    return parent[x];
  }

  /**
   * @brief Initialize data values
   * @param datas The data values to initialize
   * @throws std::invalid_argument if the size does not match
   */
  void init_datas(const std::vector<T> &datas) {
    values = datas;
    if (datas.size() != data_size)
      throw std::invalid_argument("Data size does not match the initialized size.");
    values.resize(datas.size() + 1, Monoid::identity());
  }

  /**
   * @brief Initialize data values from iterators
   * @tparam InputIt The type of the input iterator
   * @param first The beginning iterator
   * @param last The ending iterator
   * @throws std::invalid_argument if the size does not match
   */
  template <typename InputIt> void init_datas(InputIt first, InputIt last) {
    values.assign(first, last);
    if (values.size() != data_size)
      throw std::invalid_argument("Data size does not match the initialized size.");
    values.resize(data_size + 1, Monoid::identity());
  }

  /**
   * @brief Process the queries and return results
   * @param datas The data values
   * @return A vector of results for each query
   */
  std::vector<T> work(const std::vector<T> &datas) {
    parent.resize(datas.size() + 1);
    std::iota(parent.begin(), parent.end(), 0);

    std::vector<T> results(query_count, Monoid::identity());
    for (size_t i = 1; i <= datas.size(); ++i) {
      parent[i - 1] = i;
      for (const auto &[l, idx] : queries[i])
        if (l < i)
          find(l), results[idx] = values[l];
    }
    return results;
  }

public:
  /**
   * @brief Constructor
   * @param n The size of the data
   */
  explicit OfflineStaticRangeQuery(ptr_t n)
      : query_count(0), data_size(n), queries(n + 1) {}

  /**
   * @brief Add a query for the range [l, r)
   * @param l The left index (inclusive)
   * @param r The right index (exclusive)
   */
  void add_query(ptr_t l, ptr_t r) {
    queries[std::min(r, data_size)].emplace_back(l, query_count++);
  }

  /**
   * @brief Process the queries with the given data values
   * @param datas The data values
   * @return A vector of results for each query
   */
  std::vector<T> process(const std::vector<T> &datas) {
    init_datas(datas);
    return work(datas);
  }

  /**
   * @brief Process the queries with the given data values from iterators
   * @tparam InputIt The type of the input iterator
   * @param first The beginning iterator
   * @param last The ending iterator
   * @return A vector of results for each query
   */
  template <typename InputIt> std::vector<T> process(InputIt first, InputIt last) {
    init_datas(first, last);
    return work(values);
  }
};
} // namespace weilycoder

#endif
