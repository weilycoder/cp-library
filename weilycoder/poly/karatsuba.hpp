#ifndef WEILYCODER_POLY_KARATSUBA_HPP
#define WEILYCODER_POLY_KARATSUBA_HPP

#include <algorithm>
#include <iterator>
#include <type_traits>
#include <vector>

namespace weilycoder {
/**
 * @brief Multiply two polynomials using the Karatsuba algorithm.
 * @tparam InputIt Iterator type for input polynomials.
 * @tparam OutputIt Iterator type for output polynomial.
 * @tparam Threshold Size threshold to switch to standard multiplication.
 * @param a_begin Iterator to the beginning of the first polynomial.
 * @param a_end Iterator to the end of the first polynomial.
 * @param b_begin Iterator to the beginning of the second polynomial.
 * @param b_end Iterator to the end of the second polynomial.
 * @param result_begin Iterator to the beginning of the result polynomial.
 */
template <typename InputIt, typename OutputIt, size_t Threshold = 32>
void karatsuba_multiply(InputIt a_begin, InputIt a_end, InputIt b_begin, InputIt b_end,
                        OutputIt result_begin) {
  using T = typename std::iterator_traits<InputIt>::value_type;

  static_assert(
      std::is_base_of<std::random_access_iterator_tag,
                      typename std::iterator_traits<InputIt>::iterator_category>::value,
      "karatsuba_multiply requires InputIt to be a random access iterator");
  static_assert(std::is_base_of<
                    std::random_access_iterator_tag,
                    typename std::iterator_traits<OutputIt>::iterator_category>::value,
                "karatsuba_multiply requires OutputIt to be a random access iterator");

  size_t a_size = std::distance(a_begin, a_end);
  size_t b_size = std::distance(b_begin, b_end);

  if (a_size <= Threshold || b_size <= Threshold) {
    // Base case: use standard multiplication
    for (size_t i = 0; i < a_size; ++i)
      for (size_t j = 0; j < b_size; ++j)
        result_begin[i + j] += a_begin[i] * b_begin[j];
    return;
  }

  size_t res_size = a_size + b_size - 1;
  size_t half_size = std::max(a_size, b_size) / 2;

  // Split the polynomials
  auto a_mid = (a_size > half_size) ? a_begin + half_size : a_end;
  auto b_mid = (b_size > half_size) ? b_begin + half_size : b_end;

  size_t a_low_size = std::distance(a_begin, a_mid);
  size_t b_low_size = std::distance(b_begin, b_mid);
  size_t a_high_size = std::distance(a_mid, a_end);
  size_t b_high_size = std::distance(b_mid, b_end);
  size_t a_max_size = std::max(a_low_size, a_high_size);
  size_t b_max_size = std::max(b_low_size, b_high_size);
  size_t part_size = a_max_size + b_max_size - 1;

  std::vector<T> z0(part_size);
  std::vector<T> z1(part_size);
  std::vector<T> z2(part_size);

  // z0 = a_low * b_low
  karatsuba_multiply(a_begin, a_mid, b_begin, b_mid, z0.begin());
  // z2 = a_high * b_high
  karatsuba_multiply(a_mid, a_end, b_mid, b_end, z2.begin());

  // z1 = (a_low + a_high) * (b_low + b_high) - z0 - z2
  std::vector<T> a_sum(std::max(a_low_size, a_high_size));
  for (size_t i = 0; i < a_low_size; ++i)
    a_sum[i] += a_begin[i];
  for (size_t i = 0; i < a_high_size; ++i)
    a_sum[i] += a_mid[i];
  std::vector<T> b_sum(std::max(b_low_size, b_high_size));
  for (size_t i = 0; i < b_low_size; ++i)
    b_sum[i] += b_begin[i];
  for (size_t i = 0; i < b_high_size; ++i)
    b_sum[i] += b_mid[i];
  karatsuba_multiply(a_sum.begin(), a_sum.end(), b_sum.begin(), b_sum.end(),
                     z1.begin());
  for (size_t i = 0; i < part_size; ++i)
    z1[i] -= z0[i] + z2[i];

  // Combine results
  for (size_t i = 0; i < part_size; ++i) {
    if (i >= res_size)
      break;
    result_begin[i] += z0[i];
  }
  for (size_t i = 0; i < part_size; ++i) {
    if (i + half_size >= res_size)
      break;
    result_begin[i + half_size] += z1[i];
  }
  for (size_t i = 0; i < part_size; ++i) {
    if (i + 2 * half_size >= res_size)
      break;
    result_begin[i + 2 * half_size] += z2[i];
  }
}

/**
 * @brief Multiply two polynomials using the Karatsuba algorithm.
 * @tparam T Coefficient type of the polynomials.
 * @tparam Threshold Size threshold to switch to standard multiplication.
 * @param a First polynomial coefficients.
 * @param b Second polynomial coefficients.
 * @return Resulting polynomial coefficients after multiplication.
 */
template <typename T, size_t Threshold = 32>
std::vector<T> karatsuba_multiply(const std::vector<T> &a, const std::vector<T> &b) {
  using I_It = typename std::vector<T>::const_iterator;
  using O_It = typename std::vector<T>::iterator;
  std::vector<T> result(a.size() + b.size() - 1);
  karatsuba_multiply<I_It, O_It, Threshold>(a.begin(), a.end(), b.begin(), b.end(),
                                            result.begin());
  return result;
}
} // namespace weilycoder

#endif
