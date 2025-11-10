---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: weilycoder/fast-io.hpp
    title: Fast Input/Output Utilities
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
    \n\n#line 1 \"weilycoder/fast-io.hpp\"\n\n\n\n/**\n * @file fast-io.hpp\n * @brief\
    \ Fast Input/Output Utilities\n */\n\n#include <cstddef>\n#include <cstdint>\n\
    #include <cstdio>\n#include <limits>\n\n#if defined(__linux__) || defined(__unix__)\
    \ || defined(__APPLE__)\n#include <sys/mman.h>\n#include <sys/stat.h>\n#include\
    \ <unistd.h>\n#endif\n\nnamespace weilycoder {\n#if defined(__linux__) || defined(__unix__)\
    \ || defined(__APPLE__)\n/**\n * @brief Fast Reader using Memory-Mapped I/O\n\
    \ */\nstruct FastReadMMap {\n  size_t file_size;\n  char *data, *pos;\n\n  FastReadMMap(const\
    \ FastReadMMap &) = delete;\n  FastReadMMap &operator=(const FastReadMMap &) =\
    \ delete;\n\n  /**\n   * @brief Constructs a FastReadMMap object and memory-maps\
    \ stdin.\n   *        If mapping fails, sets file_size to max size_t.\n   */\n\
    \  FastReadMMap() {\n    struct stat st;\n\n    if (fstat(0, &st) != 0) {\n  \
    \    file_size = std::numeric_limits<size_t>::max();\n      return;\n    }\n\n\
    \    file_size = st.st_size;\n    data = reinterpret_cast<char *>(\n        mmap(nullptr,\
    \ file_size, PROT_READ, MAP_PRIVATE, 0, 0));\n    pos = data;\n  }\n\n  /**\n\
    \   * @brief Destructor that unmaps the memory-mapped file.\n   */\n  ~FastReadMMap()\
    \ {\n    if (file_size != std::numeric_limits<size_t>::max())\n      munmap(data,\
    \ file_size);\n  }\n\n  /**\n   * @brief Gets the next character from the memory-mapped\
    \ input.\n   * @return The next character, or EOF if the end of the file is reached.\n\
    \   */\n  inline char getchar() {\n    return static_cast<size_t>(pos - data)\
    \ < file_size ? *pos++ : EOF;\n  }\n\n  /**\n   * @brief Alias for getchar().\n\
    \   * @return The next character from input.\n   */\n  inline char operator()()\
    \ { return getchar(); }\n};\n#endif\n\n/**\n * @brief Fast Reader using fread\n\
    \ * @tparam buffer_size Size of the internal buffer (default: 1 MB)\n */\ntemplate\
    \ <size_t buffer_size = 1 << 20> struct FastReadFRead {\n  char buf[buffer_size],\
    \ *pos = buf, *end = buf;\n\n  FastReadFRead() = default;\n\n  FastReadFRead(const\
    \ FastReadFRead &) = delete;\n  FastReadFRead &operator=(const FastReadFRead &)\
    \ = delete;\n\n  /**\n   * @brief Gets the next character from input using buffered\
    \ fread.\n   * @return The next character, or EOF if the end of the file is reached.\n\
    \   */\n  inline char getchar() {\n    return pos == end && (end = (pos = buf)\
    \ + fread(buf, 1, buffer_size, stdin),\n                          pos == end)\n\
    \               ? EOF\n               : *pos++;\n  }\n\n  /**\n   * @brief Clears\
    \ the internal buffer.\n   */\n  inline void clear() { pos = end = buf; }\n\n\
    \  /**\n   * @brief Reopens the input stream by clearing the buffer\n   *    \
    \    and seeking to the beginning.\n   */\n  inline void reopen() { clear(), fseek(stdin,\
    \ 0, SEEK_SET); }\n\n  /**\n   * @brief Alias for getchar().\n   * @return The\
    \ next character from input.\n   */\n  inline char operator()() { return getchar();\
    \ }\n};\n\n/**\n * @brief Fast Writer using fwrite\n * @tparam buffer_size Size\
    \ of the internal buffer (default: 1 MB)\n */\ntemplate <size_t buffer_size =\
    \ 1 << 20> struct FastWriteFWrite {\n  char buf[buffer_size], *pos = buf;\n\n\
    \  FastWriteFWrite() = default;\n  ~FastWriteFWrite() { flush(); }\n\n  FastWriteFWrite(const\
    \ FastWriteFWrite &) = delete;\n  FastWriteFWrite &operator=(const FastWriteFWrite\
    \ &) = delete;\n\n  /**\n   * @brief Puts a character into the output buffer.\n\
    \   *        Flushes the buffer if it is full.\n   * @param c Character to put\
    \ into the buffer.\n   */\n  inline void putchar(char c) {\n    if (pos - buf\
    \ == buffer_size)\n      flush();\n    *pos++ = c;\n  }\n\n  /**\n   * @brief\
    \ Flushes the output buffer to stdout.\n   */\n  inline void flush() {\n    size_t\
    \ write_size = pos - buf;\n    if (write_size) {\n      fwrite(buf, 1, write_size,\
    \ stdout);\n      pos = buf;\n    }\n  }\n\n  /**\n   * @brief Alias for putchar().\n\
    \   * @param c Character to put into the buffer.\n   */\n  inline void operator()(char\
    \ c) { putchar(c); }\n};\n\n/**\n * @brief Fast Input/Output handler combining\
    \ a Reader and a Writer.\n * @tparam Reader Type of the input reader.\n * @tparam\
    \ Writer Type of the output writer.\n * @tparam debug If true, uses standard I/O\
    \ functions for debugging.\n */\ntemplate <typename Reader, typename Writer, bool\
    \ debug = false> struct FastIO {\n  Reader reader;\n  Writer writer;\n\n  FastIO()\
    \ = default;\n\n  FastIO(const FastIO &) = delete;\n  FastIO &operator=(const\
    \ FastIO &) = delete;\n\n  /**\n   * @brief Gets the next character from input.\n\
    \   * @return The next character from input.\n   */\n  inline char getchar() {\n\
    \    if constexpr (debug)\n      return std::getchar();\n    else\n      return\
    \ reader.getchar();\n  }\n\n  /**\n   * @brief Puts a character into output.\n\
    \   * @param c Character to put into output.\n   */\n  inline void putchar(char\
    \ c) {\n    if constexpr (debug)\n      std::putchar(c), std::fflush(stdout);\n\
    \    else\n      writer.putchar(c);\n  }\n\n  /**\n   * @brief Flushes the output\
    \ buffer.\n   */\n  inline void flush() { writer.flush(); }\n\n  /**\n   * @brief\
    \ Computes the absolute value of a 32-bit integer.\n   * @param x The integer\
    \ to compute the absolute value for.\n   * @return The absolute value of x.\n\
    \   */\n  static int32_t abs(int32_t x) { return x >= 0 ? x : -x; }\n\n  /**\n\
    \   * @brief Reads an unsigned integer of type utype from input.\n   * @tparam\
    \ utype Unsigned integer type to read.\n   * @return The read unsigned integer.\n\
    \   */\n  template <typename utype> inline utype _read_u() {\n    char c;\n  \
    \  do\n      c = getchar();\n    while (c < '0' || c > '9');\n    utype x = 0;\n\
    \    do\n      x = x * 10 + (c - '0'), c = getchar();\n    while (c >= '0' &&\
    \ c <= '9');\n    return x;\n  }\n\n  /**\n   * @brief Reads a signed integer\
    \ of type itype from input.\n   * @tparam itype Signed integer type to read.\n\
    \   * @tparam utype Unsigned integer type used for intermediate calculations,\n\
    \   *         should be the corresponding unsigned type of itype.\n   * @return\
    \ The read signed integer.\n   */\n  template <typename itype, typename utype>\
    \ inline itype _read_i() {\n    char c;\n    bool neg = false;\n    do\n     \
    \ if ((c = getchar()) == '-')\n        neg = true;\n    while ((c < '0' || c >\
    \ '9'));\n    utype x = 0;\n    do\n      x = x * 10 + (c - '0'), c = getchar();\n\
    \    while (c >= '0' && c <= '9');\n    return static_cast<itype>(neg ? -x : x);\n\
    \  }\n\n  /**\n   * @brief Writes an unsigned integer of type utype to output.\n\
    \   * @tparam utype Unsigned integer type to write.\n   * @tparam bufsize Size\
    \ of the internal buffer used for conversion.\n   * @param x The unsigned integer\
    \ to write.\n   */\n  template <typename utype, size_t bufsize> inline void _write_u(utype\
    \ x) {\n    static char buf[bufsize];\n    size_t len = 0;\n    do\n      buf[len++]\
    \ = '0' + (x % 10), x /= 10;\n    while (x);\n    for (size_t i = len - 1; ~i;\
    \ --i)\n      putchar(buf[i]);\n  }\n\n  /**\n   * @brief Writes a signed integer\
    \ of type itype to output.\n   * @tparam itype Signed integer type to write.\n\
    \   * @tparam bufsize Size of the internal buffer used for conversion.\n   * @param\
    \ x The signed integer to write.\n   */\n  template <typename itype, size_t bufsize>\
    \ inline void _write_i(itype x) {\n    bool neg = x < 0;\n    static char buf[bufsize];\n\
    \    size_t len = 0;\n    do\n      buf[len++] = '0' + this->abs(x % 10), x /=\
    \ 10;\n    while (x);\n    if (neg)\n      putchar('-');\n    for (size_t i =\
    \ len - 1; ~i; --i)\n      putchar(buf[i]);\n  }\n\n  /**\n   * @brief Reads a\
    \ signed 32-bit integer from input.\n   * @return The read signed 32-bit integer.\n\
    \   */\n  inline int32_t read_i32() { return _read_i<int32_t, uint32_t>(); }\n\
    \n  /**\n   * @brief Reads an unsigned 32-bit integer from input.\n   * @return\
    \ The read unsigned 32-bit integer.\n   */\n  inline uint32_t read_u32() { return\
    \ _read_u<uint32_t>(); }\n\n  /**\n   * @brief Writes a signed 32-bit integer\
    \ to output.\n   * @param x The signed 32-bit integer to write.\n   */\n  inline\
    \ void write_i32(int32_t x) { _write_i<int32_t, 10>(x); }\n\n  /**\n   * @brief\
    \ Writes an unsigned 32-bit integer to output.\n   * @param x The unsigned 32-bit\
    \ integer to write.\n   */\n  inline void write_u32(uint32_t x) { _write_u<uint32_t,\
    \ 10>(x); }\n\n  /**\n   * @brief Reads a signed 64-bit integer from input.\n\
    \   * @return The read signed 64-bit integer.\n   */\n  inline int64_t read_i64()\
    \ { return _read_i<int64_t, uint64_t>(); }\n\n  /**\n   * @brief Reads an unsigned\
    \ 64-bit integer from input.\n   * @return The read unsigned 64-bit integer.\n\
    \   */\n  inline uint64_t read_u64() { return _read_u<uint64_t>(); }\n\n  /**\n\
    \   * @brief Writes a signed 64-bit integer to output.\n   * @param x The signed\
    \ 64-bit integer to write.\n   */\n  inline void write_i64(int64_t x) { _write_i<int64_t,\
    \ 20>(x); }\n\n  /**\n   * @brief Writes an unsigned 64-bit integer to output.\n\
    \   * @param x The unsigned 64-bit integer to write.\n   */\n  inline void write_u64(uint64_t\
    \ x) { _write_u<uint64_t, 20>(x); }\n\n  /**\n   * @brief Reads a signed 128-bit\
    \ integer from input.\n   * @return The read signed 128-bit integer.\n   */\n\
    \  inline __int128 read_i128() { return _read_i<__int128, unsigned __int128>();\
    \ }\n\n  /**\n   * @brief Reads an unsigned 128-bit integer from input.\n   *\
    \ @return The read unsigned 128-bit integer.\n   */\n  inline unsigned __int128\
    \ read_u128() { return _read_u<unsigned __int128>(); }\n\n  /**\n   * @brief Writes\
    \ a signed 128-bit integer to output.\n   * @param x The signed 128-bit integer\
    \ to write.\n   */\n  inline void write_i128(__int128 x) { _write_i<__int128,\
    \ 40>(x); }\n\n  /**\n   * @brief Writes an unsigned 128-bit integer to output.\n\
    \   * @param x The unsigned 128-bit integer to write.\n   */\n  inline void write_u128(unsigned\
    \ __int128 x) {\n    _write_u<unsigned __int128, 40>(x);\n  }\n\n  inline void\
    \ write_i32_line(int32_t x) { write_i32(x), putchar('\\n'); }\n  inline void write_u32_line(uint32_t\
    \ x) { write_u32(x), putchar('\\n'); }\n  inline void write_i64_line(int64_t x)\
    \ { write_i64(x), putchar('\\n'); }\n  inline void write_u64_line(uint64_t x)\
    \ { write_u64(x), putchar('\\n'); }\n  inline void write_i128_line(__int128 x)\
    \ { write_i128(x), putchar('\\n'); }\n  inline void write_u128_line(unsigned __int128\
    \ x) {\n    write_u128(x), putchar('\\n');\n  }\n};\n\n#if defined(__linux__)\
    \ || defined(__unix__) || defined(__APPLE__)\ntemplate <bool debug = false>\n\
    using FastIOMMap = FastIO<FastReadMMap, FastWriteFWrite<>, debug>;\n#endif\n\n\
    template <bool debug = false>\nusing FastIOFile = FastIO<FastReadFRead<>, FastWriteFWrite<>,\
    \ debug>;\n} // namespace weilycoder\n\n\n#line 4 \"test/many_aplusb.test.cpp\"\
    \nusing namespace weilycoder;\n\nstatic FastIOMMap<> io;\n\nint main() {\n  size_t\
    \ t = io.read_u64();\n  while (t--) {\n    uint64_t a = io.read_u64();\n    uint64_t\
    \ b = io.read_u64();\n    uint64_t c = a + b;\n    io.write_u64_line(c);\n  }\n\
    \  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/many_aplusb\"\n\n#include\
    \ \"../weilycoder/fast-io.hpp\"\nusing namespace weilycoder;\n\nstatic FastIOMMap<>\
    \ io;\n\nint main() {\n  size_t t = io.read_u64();\n  while (t--) {\n    uint64_t\
    \ a = io.read_u64();\n    uint64_t b = io.read_u64();\n    uint64_t c = a + b;\n\
    \    io.write_u64_line(c);\n  }\n  return 0;\n}"
  dependsOn:
  - weilycoder/fast-io.hpp
  isVerificationFile: true
  path: test/many_aplusb.test.cpp
  requiredBy: []
  timestamp: '2025-10-30 21:08:02+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/many_aplusb.test.cpp
layout: document
redirect_from:
- /verify/test/many_aplusb.test.cpp
- /verify/test/many_aplusb.test.cpp.html
title: test/many_aplusb.test.cpp
---
