---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: weilycoder/data-struct/static_range_sum.hpp
    title: weilycoder/data-struct/static_range_sum.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/static_range_sum
    links:
    - https://judge.yosupo.jp/problem/static_range_sum
  bundledCode: "#line 1 \"test/static_range_sum.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_sum\"\
    \n\n#line 1 \"weilycoder/data-struct/static_range_sum.hpp\"\n\n\n\n#include <cstddef>\n\
    #include <vector>\n\nnamespace weilycoder {\ntemplate <typename T, typename ptr_t\
    \ = size_t> struct StaticRangeSum {\n  std::vector<T> prefix_sum;\n\n  StaticRangeSum(const\
    \ std::vector<T> &data) : prefix_sum(data.size() + 1) {\n    for (ptr_t i = 1;\
    \ i <= data.size(); ++i)\n      prefix_sum[i] = prefix_sum[i - 1] + data[i - 1];\n\
    \  }\n\n  T query(ptr_t l, ptr_t r) const { return prefix_sum[r] - prefix_sum[l];\
    \ }\n};\n} // namespace weilycoder\n\n\n#line 4 \"test/static_range_sum.test.cpp\"\
    \n#include <cstdint>\n#include <iostream>\n#line 7 \"test/static_range_sum.test.cpp\"\
    \nusing namespace std;\nusing namespace weilycoder;\n\nint main() {\n  cin.tie(nullptr)->sync_with_stdio(false);\n\
    \  cin.exceptions(cin.failbit | cin.badbit);\n  size_t n, q;\n  cin >> n >> q;\n\
    \n  vector<uint64_t> arr(n);\n  for (size_t i = 0; i < n; ++i)\n    cin >> arr[i];\n\
    \n  StaticRangeSum<uint64_t> sum(arr);\n  while (q--) {\n    size_t l, r;\n  \
    \  cin >> l >> r;\n    cout << sum.query(l, r) << '\\n';\n  }\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_sum\"\n\n\
    #include \"../weilycoder/data-struct/static_range_sum.hpp\"\n#include <cstdint>\n\
    #include <iostream>\n#include <vector>\nusing namespace std;\nusing namespace\
    \ weilycoder;\n\nint main() {\n  cin.tie(nullptr)->sync_with_stdio(false);\n \
    \ cin.exceptions(cin.failbit | cin.badbit);\n  size_t n, q;\n  cin >> n >> q;\n\
    \n  vector<uint64_t> arr(n);\n  for (size_t i = 0; i < n; ++i)\n    cin >> arr[i];\n\
    \n  StaticRangeSum<uint64_t> sum(arr);\n  while (q--) {\n    size_t l, r;\n  \
    \  cin >> l >> r;\n    cout << sum.query(l, r) << '\\n';\n  }\n  return 0;\n}"
  dependsOn:
  - weilycoder/data-struct/static_range_sum.hpp
  isVerificationFile: true
  path: test/static_range_sum.test.cpp
  requiredBy: []
  timestamp: '2025-10-28 23:07:26+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/static_range_sum.test.cpp
layout: document
redirect_from:
- /verify/test/static_range_sum.test.cpp
- /verify/test/static_range_sum.test.cpp.html
title: test/static_range_sum.test.cpp
---
