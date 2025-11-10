---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: weilycoder/poly/karatsuba.hpp
    title: Multiply two polynomials using the Karatsuba algorithm.
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/convolution_mod_2_64
    links:
    - https://judge.yosupo.jp/problem/convolution_mod_2_64
  bundledCode: "#line 1 \"test/convolution_mod_2_64.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/convolution_mod_2_64\"\n\n#line 1 \"weilycoder/poly/karatsuba.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <iterator>\n#include <type_traits>\n#include\
    \ <vector>\n\nnamespace weilycoder {\n/**\n * @brief Multiply two polynomials\
    \ using the Karatsuba algorithm.\n * @tparam InputIt Iterator type for input polynomials.\n\
    \ * @tparam OutputIt Iterator type for output polynomial.\n * @tparam Threshold\
    \ Size threshold to switch to standard multiplication.\n * @param a_begin Iterator\
    \ to the beginning of the first polynomial.\n * @param a_end Iterator to the end\
    \ of the first polynomial.\n * @param b_begin Iterator to the beginning of the\
    \ second polynomial.\n * @param b_end Iterator to the end of the second polynomial.\n\
    \ * @param result_begin Iterator to the beginning of the result polynomial.\n\
    \ */\ntemplate <typename InputIt, typename OutputIt, size_t Threshold = 32>\n\
    void karatsuba_multiply(InputIt a_begin, InputIt a_end, InputIt b_begin, InputIt\
    \ b_end,\n                        OutputIt result_begin) {\n  using T = typename\
    \ std::iterator_traits<InputIt>::value_type;\n\n  static_assert(\n      std::is_base_of<std::random_access_iterator_tag,\n\
    \                      typename std::iterator_traits<InputIt>::iterator_category>::value,\n\
    \      \"karatsuba_multiply requires InputIt to be a random access iterator\"\
    );\n  static_assert(std::is_base_of<\n                    std::random_access_iterator_tag,\n\
    \                    typename std::iterator_traits<OutputIt>::iterator_category>::value,\n\
    \                \"karatsuba_multiply requires OutputIt to be a random access\
    \ iterator\");\n\n  size_t a_size = std::distance(a_begin, a_end);\n  size_t b_size\
    \ = std::distance(b_begin, b_end);\n\n  if (a_size <= Threshold || b_size <= Threshold)\
    \ {\n    // Base case: use standard multiplication\n    for (size_t i = 0; i <\
    \ a_size; ++i)\n      for (size_t j = 0; j < b_size; ++j)\n        result_begin[i\
    \ + j] += a_begin[i] * b_begin[j];\n    return;\n  }\n\n  size_t res_size = a_size\
    \ + b_size - 1;\n  size_t half_size = std::max(a_size, b_size) / 2;\n\n  // Split\
    \ the polynomials\n  auto a_mid = (a_size > half_size) ? a_begin + half_size :\
    \ a_end;\n  auto b_mid = (b_size > half_size) ? b_begin + half_size : b_end;\n\
    \n  size_t a_low_size = std::distance(a_begin, a_mid);\n  size_t b_low_size =\
    \ std::distance(b_begin, b_mid);\n  size_t a_high_size = std::distance(a_mid,\
    \ a_end);\n  size_t b_high_size = std::distance(b_mid, b_end);\n  size_t a_max_size\
    \ = std::max(a_low_size, a_high_size);\n  size_t b_max_size = std::max(b_low_size,\
    \ b_high_size);\n  size_t part_size = a_max_size + b_max_size - 1;\n\n  std::vector<T>\
    \ z0(part_size);\n  std::vector<T> z1(part_size);\n  std::vector<T> z2(part_size);\n\
    \n  // z0 = a_low * b_low\n  karatsuba_multiply(a_begin, a_mid, b_begin, b_mid,\
    \ z0.begin());\n  // z2 = a_high * b_high\n  karatsuba_multiply(a_mid, a_end,\
    \ b_mid, b_end, z2.begin());\n\n  // z1 = (a_low + a_high) * (b_low + b_high)\
    \ - z0 - z2\n  std::vector<T> a_sum(std::max(a_low_size, a_high_size));\n  for\
    \ (size_t i = 0; i < a_low_size; ++i)\n    a_sum[i] += a_begin[i];\n  for (size_t\
    \ i = 0; i < a_high_size; ++i)\n    a_sum[i] += a_mid[i];\n  std::vector<T> b_sum(std::max(b_low_size,\
    \ b_high_size));\n  for (size_t i = 0; i < b_low_size; ++i)\n    b_sum[i] += b_begin[i];\n\
    \  for (size_t i = 0; i < b_high_size; ++i)\n    b_sum[i] += b_mid[i];\n  karatsuba_multiply(a_sum.begin(),\
    \ a_sum.end(), b_sum.begin(), b_sum.end(),\n                     z1.begin());\n\
    \  for (size_t i = 0; i < part_size; ++i)\n    z1[i] -= z0[i] + z2[i];\n\n  //\
    \ Combine results\n  for (size_t i = 0; i < part_size; ++i) {\n    if (i >= res_size)\n\
    \      break;\n    result_begin[i] += z0[i];\n  }\n  for (size_t i = 0; i < part_size;\
    \ ++i) {\n    if (i + half_size >= res_size)\n      break;\n    result_begin[i\
    \ + half_size] += z1[i];\n  }\n  for (size_t i = 0; i < part_size; ++i) {\n  \
    \  if (i + 2 * half_size >= res_size)\n      break;\n    result_begin[i + 2 *\
    \ half_size] += z2[i];\n  }\n}\n\n/**\n * @brief Multiply two polynomials using\
    \ the Karatsuba algorithm.\n * @tparam T Coefficient type of the polynomials.\n\
    \ * @tparam Threshold Size threshold to switch to standard multiplication.\n *\
    \ @param a First polynomial coefficients.\n * @param b Second polynomial coefficients.\n\
    \ * @return Resulting polynomial coefficients after multiplication.\n */\ntemplate\
    \ <typename T, size_t Threshold = 32>\nstd::vector<T> karatsuba_multiply(const\
    \ std::vector<T> &a, const std::vector<T> &b) {\n  using I_It = typename std::vector<T>::const_iterator;\n\
    \  using O_It = typename std::vector<T>::iterator;\n  std::vector<T> result(a.size()\
    \ + b.size() - 1);\n  karatsuba_multiply<I_It, O_It, Threshold>(a.begin(), a.end(),\
    \ b.begin(), b.end(),\n                                            result.begin());\n\
    \  return result;\n}\n} // namespace weilycoder\n\n\n#line 4 \"test/convolution_mod_2_64.test.cpp\"\
    \n#include <cstdint>\n#include <iostream>\n#line 7 \"test/convolution_mod_2_64.test.cpp\"\
    \nusing namespace std;\nusing namespace weilycoder;\n\nint main() {\n  cin.tie(nullptr)->sync_with_stdio(false);\n\
    \  cin.exceptions(cin.badbit | cin.failbit);\n  size_t n, m;\n  cin >> n >> m;\n\
    \n  vector<uint64_t> a(n), b(m);\n  for (size_t i = 0; i < n; ++i)\n    cin >>\
    \ a[i];\n  for (size_t j = 0; j < m; ++j)\n    cin >> b[j];\n\n  auto c = karatsuba_multiply(a,\
    \ b);\n  for (size_t k = 0; k < n + m - 1; ++k)\n    cout << c[k] << (k + 1 ==\
    \ n + m - 1 ? '\\n' : ' ');\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod_2_64\"\n\
    \n#include \"../weilycoder/poly/karatsuba.hpp\"\n#include <cstdint>\n#include\
    \ <iostream>\n#include <vector>\nusing namespace std;\nusing namespace weilycoder;\n\
    \nint main() {\n  cin.tie(nullptr)->sync_with_stdio(false);\n  cin.exceptions(cin.badbit\
    \ | cin.failbit);\n  size_t n, m;\n  cin >> n >> m;\n\n  vector<uint64_t> a(n),\
    \ b(m);\n  for (size_t i = 0; i < n; ++i)\n    cin >> a[i];\n  for (size_t j =\
    \ 0; j < m; ++j)\n    cin >> b[j];\n\n  auto c = karatsuba_multiply(a, b);\n \
    \ for (size_t k = 0; k < n + m - 1; ++k)\n    cout << c[k] << (k + 1 == n + m\
    \ - 1 ? '\\n' : ' ');\n  return 0;\n}"
  dependsOn:
  - weilycoder/poly/karatsuba.hpp
  isVerificationFile: true
  path: test/convolution_mod_2_64.test.cpp
  requiredBy: []
  timestamp: '2025-11-05 00:26:33+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/convolution_mod_2_64.test.cpp
layout: document
redirect_from:
- /verify/test/convolution_mod_2_64.test.cpp
- /verify/test/convolution_mod_2_64.test.cpp.html
title: test/convolution_mod_2_64.test.cpp
---
