#ifndef WEILYCODER_POLY_ELEMENTARY_FUNC_DERIVATIVE_HPP
#define WEILYCODER_POLY_ELEMENTARY_FUNC_DERIVATIVE_HPP

#include <vector>

namespace weilycoder {
template <typename T, typename MultiplyFunc>
std::vector<T> derivative(const std::vector<T> &poly, MultiplyFunc number_mul) {
  if (poly.size() <= 1)
    return {};
  std::vector<T> res(poly.size() - 1);
  for (size_t i = 1; i < poly.size(); ++i)
    res[i - 1] = number_mul(poly[i], T(i));
  return res;
}
} // namespace weilycoder

#endif
