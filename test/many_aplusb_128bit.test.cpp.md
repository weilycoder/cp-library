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
    PROBLEM: https://judge.yosupo.jp/problem/many_aplusb_128bit
    links:
    - https://judge.yosupo.jp/problem/many_aplusb_128bit
  bundledCode: "#line 1 \"test/many_aplusb_128bit.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/many_aplusb_128bit\"\
    \n\n#line 1 \"weilycoder/fast-io.hpp\"\n\n\n\n#include <cstddef>\n#include <cstdint>\n\
    #include <cstdio>\n#include <limits>\n\n#if defined(__linux__) || defined(__unix__)\
    \ || defined(__APPLE__)\n#include <sys/mman.h>\n#include <sys/stat.h>\n#include\
    \ <unistd.h>\n#endif\n\nnamespace weilycoder {\n#if defined(__linux__) || defined(__unix__)\
    \ || defined(__APPLE__)\nstruct FastReadMMap {\n  size_t file_size;\n  char *data,\
    \ *pos;\n\n  FastReadMMap(const FastReadMMap &) = delete;\n  FastReadMMap &operator=(const\
    \ FastReadMMap &) = delete;\n\n  FastReadMMap() {\n    struct stat st;\n\n   \
    \ if (fstat(0, &st) != 0) {\n      file_size = std::numeric_limits<size_t>::max();\n\
    \      return;\n    }\n\n    file_size = st.st_size;\n    data = reinterpret_cast<char\
    \ *>(\n        mmap(nullptr, file_size, PROT_READ, MAP_PRIVATE, 0, 0));\n    pos\
    \ = data;\n  }\n\n  ~FastReadMMap() {\n    if (file_size != std::numeric_limits<size_t>::max())\n\
    \      munmap(data, file_size);\n  }\n\n  inline char getchar() {\n    return\
    \ static_cast<size_t>(pos - data) < file_size ? *pos++ : EOF;\n  }\n\n  inline\
    \ char operator()() { return getchar(); }\n};\n#endif\n\ntemplate <size_t buffer_size\
    \ = 1 << 20> struct FastReadFRead {\n  char buf[buffer_size], *pos = buf, *end\
    \ = buf;\n\n  FastReadFRead() = default;\n\n  FastReadFRead(const FastReadFRead\
    \ &) = delete;\n  FastReadFRead &operator=(const FastReadFRead &) = delete;\n\n\
    \  inline char getchar() {\n    return pos == end && (end = (pos = buf) + fread(buf,\
    \ 1, buffer_size, stdin),\n                          pos == end)\n           \
    \    ? EOF\n               : *pos++;\n  }\n\n  inline void clear() { pos = end\
    \ = buf; }\n\n  inline void reopen() { clear(), fseek(stdin, 0, SEEK_SET); }\n\
    \n  inline char operator()() { return getchar(); }\n};\n\ntemplate <size_t buffer_size\
    \ = 1 << 20> struct FastWriteFWrite {\n  char buf[buffer_size], *pos = buf;\n\n\
    \  FastWriteFWrite() = default;\n  ~FastWriteFWrite() { flush(); }\n\n  FastWriteFWrite(const\
    \ FastWriteFWrite &) = delete;\n  FastWriteFWrite &operator=(const FastWriteFWrite\
    \ &) = delete;\n\n  inline void putchar(char c) {\n    if (pos - buf == buffer_size)\n\
    \      flush();\n    *pos++ = c;\n  }\n\n  inline void flush() {\n    size_t write_size\
    \ = pos - buf;\n    if (write_size) {\n      fwrite(buf, 1, write_size, stdout);\n\
    \      pos = buf;\n    }\n  }\n\n  inline void operator()(char c) { putchar(c);\
    \ }\n};\n\ntemplate <typename Reader, typename Writer, bool debug = false> struct\
    \ FastIO {\n  Reader reader;\n  Writer writer;\n\n  FastIO() = default;\n\n  FastIO(const\
    \ FastIO &) = delete;\n  FastIO &operator=(const FastIO &) = delete;\n\n  inline\
    \ char getchar() {\n    if constexpr (debug)\n      return std::getchar();\n \
    \   else\n      return reader.getchar();\n  }\n\n  inline void putchar(char c)\
    \ {\n    if constexpr (debug)\n      std::putchar(c), std::fflush(stdout);\n \
    \   else\n      writer.putchar(c);\n  }\n\n  inline void flush() { writer.flush();\
    \ }\n\n  int32_t abs(int32_t x) { return x >= 0 ? x : -x; }\n\n  template <typename\
    \ utype> inline utype _read_u() {\n    char c;\n    do\n      c = getchar();\n\
    \    while (c < '0' || c > '9');\n    utype x = 0;\n    do\n      x = x * 10 +\
    \ (c - '0'), c = getchar();\n    while (c >= '0' && c <= '9');\n    return x;\n\
    \  }\n\n  template <typename itype, typename utype> inline itype _read_i() {\n\
    \    char c;\n    bool neg = false;\n    do\n      if ((c = getchar()) == '-')\n\
    \        neg = true;\n    while ((c < '0' || c > '9'));\n    utype x = 0;\n  \
    \  do\n      x = x * 10 + (c - '0'), c = getchar();\n    while (c >= '0' && c\
    \ <= '9');\n    return static_cast<itype>(neg ? -x : x);\n  }\n\n  template <typename\
    \ utype, size_t bufsize> inline void _write_u(utype x) {\n    static char buf[bufsize];\n\
    \    size_t len = 0;\n    do\n      buf[len++] = '0' + (x % 10), x /= 10;\n  \
    \  while (x);\n    for (size_t i = len - 1; ~i; --i)\n      putchar(buf[i]);\n\
    \  }\n\n  template <typename itype, size_t bufsize> inline void _write_i(itype\
    \ x) {\n    bool neg = x < 0;\n    static char buf[bufsize];\n    size_t len =\
    \ 0;\n    do\n      buf[len++] = '0' + this->abs(x % 10), x /= 10;\n    while\
    \ (x);\n    if (neg)\n      putchar('-');\n    for (size_t i = len - 1; ~i; --i)\n\
    \      putchar(buf[i]);\n  }\n\n  inline int32_t read_i32() { return _read_i<int32_t,\
    \ uint32_t>(); }\n  inline uint32_t read_u32() { return _read_u<uint32_t>(); }\n\
    \n  inline void write_i32(int32_t x) { _write_i<int32_t, 10>(x); }\n  inline void\
    \ write_u32(uint32_t x) { _write_u<uint32_t, 10>(x); }\n\n  inline int64_t read_i64()\
    \ { return _read_i<int64_t, uint64_t>(); }\n  inline uint64_t read_u64() { return\
    \ _read_u<uint64_t>(); }\n\n  inline void write_i64(int64_t x) { _write_i<int64_t,\
    \ 20>(x); }\n  inline void write_u64(uint64_t x) { _write_u<uint64_t, 20>(x);\
    \ }\n\n  inline __int128 read_i128() { return _read_i<__int128, unsigned __int128>();\
    \ }\n  inline unsigned __int128 read_u128() { return _read_u<unsigned __int128>();\
    \ }\n\n  inline void write_i128(__int128 x) { _write_i<__int128, 40>(x); }\n \
    \ inline void write_u128(unsigned __int128 x) {\n    _write_u<unsigned __int128,\
    \ 40>(x);\n  }\n\n  inline void write_i32_line(int32_t x) { write_i32(x), putchar('\\\
    n'); }\n  inline void write_u32_line(uint32_t x) { write_u32(x), putchar('\\n');\
    \ }\n  inline void write_i64_line(int64_t x) { write_i64(x), putchar('\\n'); }\n\
    \  inline void write_u64_line(uint64_t x) { write_u64(x), putchar('\\n'); }\n\
    \  inline void write_i128_line(__int128 x) { write_i128(x), putchar('\\n'); }\n\
    \  inline void write_u128_line(unsigned __int128 x) {\n    write_u128(x), putchar('\\\
    n');\n  }\n};\n\n#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)\n\
    template <bool debug = false>\nusing FastIOMMap = FastIO<FastReadMMap, FastWriteFWrite<>,\
    \ debug>;\n#endif\n\ntemplate <bool debug = false>\nusing FastIOFile = FastIO<FastReadFRead<>,\
    \ FastWriteFWrite<>, debug>;\n} // namespace weilycoder\n\n\n#line 4 \"test/many_aplusb_128bit.test.cpp\"\
    \nusing namespace weilycoder;\n\nstatic FastIOFile<> io;\n\nint main() {\n  size_t\
    \ t = io.read_u64();\n  while (t--) {\n    auto a = io.read_i128();\n    auto\
    \ b = io.read_i128();\n    io.write_i128_line(a + b);\n  }\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/many_aplusb_128bit\"\n\n\
    #include \"../weilycoder/fast-io.hpp\"\nusing namespace weilycoder;\n\nstatic\
    \ FastIOFile<> io;\n\nint main() {\n  size_t t = io.read_u64();\n  while (t--)\
    \ {\n    auto a = io.read_i128();\n    auto b = io.read_i128();\n    io.write_i128_line(a\
    \ + b);\n  }\n  return 0;\n}"
  dependsOn:
  - weilycoder/fast-io.hpp
  isVerificationFile: true
  path: test/many_aplusb_128bit.test.cpp
  requiredBy: []
  timestamp: '2025-10-29 23:28:06+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/many_aplusb_128bit.test.cpp
layout: document
redirect_from:
- /verify/test/many_aplusb_128bit.test.cpp
- /verify/test/many_aplusb_128bit.test.cpp.html
title: test/many_aplusb_128bit.test.cpp
---
