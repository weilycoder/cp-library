---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: weilycoder/fast-io.hpp
    title: weilycoder/fast-io.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/many_aplusb
    links:
    - https://judge.yosupo.jp/problem/many_aplusb
  bundledCode: "#line 1 \"test/many_aplusb.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/many_aplusb\"\
    \n\n#line 1 \"weilycoder/fast-io.hpp\"\n\n\n\n#include <cstddef>\n#include <cstdint>\n\
    #include <cstdio>\n#include <limits>\n#include <sys/mman.h>\n#include <sys/stat.h>\n\
    #include <unistd.h>\n\nnamespace weilycoder {\nstruct FastReadMMap {\n  size_t\
    \ file_size;\n  char *data, *pos;\n\n  FastReadMMap(const FastReadMMap &) = delete;\n\
    \  FastReadMMap &operator=(const FastReadMMap &) = delete;\n\n  FastReadMMap()\
    \ {\n    struct stat st;\n\n    if (fstat(0, &st) != 0) {\n      file_size = std::numeric_limits<size_t>::max();\n\
    \      return;\n    }\n\n    file_size = st.st_size;\n    data = reinterpret_cast<char\
    \ *>(\n        mmap(nullptr, file_size, PROT_READ, MAP_PRIVATE, 0, 0));\n    pos\
    \ = data;\n  }\n\n  ~FastReadMMap() {\n    if (file_size != std::numeric_limits<size_t>::max())\n\
    \      munmap(data, file_size);\n  }\n\n  char getchar() {\n    return static_cast<size_t>(pos\
    \ - data) < file_size ? *pos++ : EOF;\n  }\n\n  char operator()() { return getchar();\
    \ }\n};\n\ntemplate <size_t buffer_size = 1 << 20> struct FastWriteFWrite {\n\
    \  char buffer[buffer_size], *pos = buffer;\n\n  FastWriteFWrite() = default;\n\
    \  ~FastWriteFWrite() { flush(); }\n\n  FastWriteFWrite(const FastWriteFWrite\
    \ &) = delete;\n  FastWriteFWrite &operator=(const FastWriteFWrite &) = delete;\n\
    \n  void putchar(char c) {\n    if (pos - buffer == buffer_size)\n      flush();\n\
    \    *pos++ = c;\n  }\n\n  void flush() {\n    size_t write_size = pos - buffer;\n\
    \    if (write_size) {\n      fwrite(buffer, 1, write_size, stdout);\n      pos\
    \ = buffer;\n    }\n  }\n\n  void operator()(char c) { putchar(c); }\n};\n\ntemplate\
    \ <typename Reader, typename Writer> struct FastIO {\n  Reader reader;\n  Writer\
    \ writer;\n\n  FastIO() = default;\n\n  FastIO(const FastIO &) = delete;\n  FastIO\
    \ &operator=(const FastIO &) = delete;\n\n  char getchar() { return reader.getchar();\
    \ }\n  void putchar(char c) { writer.putchar(c); }\n\n  void flush() { writer.flush();\
    \ }\n\n  uint64_t read_u64() {\n    char c;\n    do\n      c = getchar();\n  \
    \  while (c < '0' || c > '9');\n    uint64_t x = 0;\n    do\n      x = x * 10\
    \ + (c - '0'), c = getchar();\n    while (c >= '0' && c <= '9');\n    return x;\n\
    \  }\n\n  void write_u64(uint64_t x) {\n    static char buf[20];\n    size_t len\
    \ = 0;\n    do\n      buf[len++] = '0' + (x % 10), x /= 10;\n    while (x);\n\
    \    for (size_t i = len - 1; ~i; --i)\n      putchar(buf[i]);\n  }\n\n  void\
    \ write_u64_line(uint64_t x) { write_u64(x), putchar('\\n'); }\n};\n\nusing FastIODefault\
    \ = FastIO<FastReadMMap, FastWriteFWrite<>>;\n} // namespace weilycoder\n\n\n\
    #line 4 \"test/many_aplusb.test.cpp\"\nusing namespace weilycoder;\n\nstatic FastIODefault\
    \ io;\n\nint main() {\n  size_t t = io.read_u64();\n  while (t--) {\n    uint64_t\
    \ a = io.read_u64();\n    uint64_t b = io.read_u64();\n    uint64_t c = a + b;\n\
    \    io.write_u64_line(c);\n  }\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/many_aplusb\"\n\n#include\
    \ \"../weilycoder/fast-io.hpp\"\nusing namespace weilycoder;\n\nstatic FastIODefault\
    \ io;\n\nint main() {\n  size_t t = io.read_u64();\n  while (t--) {\n    uint64_t\
    \ a = io.read_u64();\n    uint64_t b = io.read_u64();\n    uint64_t c = a + b;\n\
    \    io.write_u64_line(c);\n  }\n  return 0;\n}"
  dependsOn:
  - weilycoder/fast-io.hpp
  isVerificationFile: true
  path: test/many_aplusb.test.cpp
  requiredBy: []
  timestamp: '2025-10-29 20:09:11+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/many_aplusb.test.cpp
layout: document
redirect_from:
- /verify/test/many_aplusb.test.cpp
- /verify/test/many_aplusb.test.cpp.html
title: test/many_aplusb.test.cpp
---
