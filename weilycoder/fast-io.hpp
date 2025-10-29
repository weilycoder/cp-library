#ifndef WEILYCODER_FAST_IO_HPP
#define WEILYCODER_FAST_IO_HPP

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <limits>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

namespace weilycoder {
struct FastReadMMap {
  size_t file_size;
  char *data, *pos;

  FastReadMMap(const FastReadMMap &) = delete;
  FastReadMMap &operator=(const FastReadMMap &) = delete;

  FastReadMMap() {
    struct stat st;

    if (fstat(0, &st) != 0) {
      file_size = std::numeric_limits<size_t>::max();
      return;
    }

    file_size = st.st_size;
    data = reinterpret_cast<char *>(
        mmap(nullptr, file_size, PROT_READ, MAP_PRIVATE, 0, 0));
    pos = data;
  }

  ~FastReadMMap() {
    if (file_size != std::numeric_limits<size_t>::max())
      munmap(data, file_size);
  }

  inline char getchar() {
    return static_cast<size_t>(pos - data) < file_size ? *pos++ : EOF;
  }

  inline char operator()() { return getchar(); }
};

template <size_t buffer_size = 1 << 20> struct FastReadFRead {
  char buf[buffer_size], *pos = buf, *end = buf;

  FastReadFRead() = default;

  FastReadFRead(const FastReadFRead &) = delete;
  FastReadFRead &operator=(const FastReadFRead &) = delete;

  inline char getchar() {
    return pos == end && (end = (pos = buf) + fread(buf, 1, buffer_size, stdin),
                          pos == end)
               ? EOF
               : *pos++;
  }

  inline void clear() { pos = end = buf; }

  inline void reopen() { clear(), fseek(stdin, 0, SEEK_SET); }

  inline char operator()() { return getchar(); }
};

template <size_t buffer_size = 1 << 20> struct FastWriteFWrite {
  char buf[buffer_size], *pos = buf;

  FastWriteFWrite() = default;
  ~FastWriteFWrite() { flush(); }

  FastWriteFWrite(const FastWriteFWrite &) = delete;
  FastWriteFWrite &operator=(const FastWriteFWrite &) = delete;

  inline void putchar(char c) {
    if (pos - buf == buffer_size)
      flush();
    *pos++ = c;
  }

  inline void flush() {
    size_t write_size = pos - buf;
    if (write_size) {
      fwrite(buf, 1, write_size, stdout);
      pos = buf;
    }
  }

  inline void operator()(char c) { putchar(c); }
};

template <typename Reader, typename Writer, bool debug = false> struct FastIO {
  Reader reader;
  Writer writer;

  FastIO() = default;

  FastIO(const FastIO &) = delete;
  FastIO &operator=(const FastIO &) = delete;

  inline char getchar() {
    if constexpr (debug)
      return std::getchar();
    else
      return reader.getchar();
  }

  inline void putchar(char c) {
    if constexpr (debug)
      std::putchar(c), std::fflush(stdout);
    else
      writer.putchar(c);
  }

  inline void flush() { writer.flush(); }

  int32_t abs(int32_t x) { return x >= 0 ? x : -x; }

  template <typename utype> inline utype _read_u() {
    char c;
    do
      c = getchar();
    while (c < '0' || c > '9');
    utype x = 0;
    do
      x = x * 10 + (c - '0'), c = getchar();
    while (c >= '0' && c <= '9');
    return x;
  }

  template <typename itype, typename utype> inline itype _read_i() {
    char c;
    bool neg = false;
    do
      if ((c = getchar()) == '-')
        neg = true;
    while ((c < '0' || c > '9'));
    utype x = 0;
    do
      x = x * 10 + (c - '0'), c = getchar();
    while (c >= '0' && c <= '9');
    return static_cast<itype>(neg ? -x : x);
  }

  template <typename utype, size_t bufsize> inline void _write_u(utype x) {
    static char buf[bufsize];
    size_t len = 0;
    do
      buf[len++] = '0' + (x % 10), x /= 10;
    while (x);
    for (size_t i = len - 1; ~i; --i)
      putchar(buf[i]);
  }

  template <typename itype, size_t bufsize> inline void _write_i(itype x) {
    bool neg = x < 0;
    static char buf[bufsize];
    size_t len = 0;
    do
      buf[len++] = '0' + this->abs(x % 10), x /= 10;
    while (x);
    if (neg)
      putchar('-');
    for (size_t i = len - 1; ~i; --i)
      putchar(buf[i]);
  }

  inline int32_t read_i32() { return _read_i<int32_t, uint32_t>(); }
  inline uint32_t read_u32() { return _read_u<uint32_t>(); }

  inline void write_i32(int32_t x) { _write_i<int32_t, 10>(x); }
  inline void write_u32(uint32_t x) { _write_u<uint32_t, 10>(x); }

  inline int64_t read_i64() { return _read_i<int64_t, uint64_t>(); }
  inline uint64_t read_u64() { return _read_u<uint64_t>(); }

  inline void write_i64(int64_t x) { _write_i<int64_t, 20>(x); }
  inline void write_u64(uint64_t x) { _write_u<uint64_t, 20>(x); }

  inline __int128 read_i128() { return _read_i<__int128, unsigned __int128>(); }
  inline unsigned __int128 read_u128() { return _read_u<unsigned __int128>(); }

  inline void write_i128(__int128 x) { _write_i<__int128, 40>(x); }
  inline void write_u128(unsigned __int128 x) {
    _write_u<unsigned __int128, 40>(x);
  }

  inline void write_i32_line(int32_t x) { write_i32(x), putchar('\n'); }
  inline void write_u32_line(uint32_t x) { write_u32(x), putchar('\n'); }
  inline void write_i64_line(int64_t x) { write_i64(x), putchar('\n'); }
  inline void write_u64_line(uint64_t x) { write_u64(x), putchar('\n'); }
  inline void write_i128_line(__int128 x) { write_i128(x), putchar('\n'); }
  inline void write_u128_line(unsigned __int128 x) {
    write_u128(x), putchar('\n');
  }
};

template <bool debug = false>
using FastIOStd = FastIO<FastReadMMap, FastWriteFWrite<>, debug>;

template <bool debug = false>
using FastIOFile = FastIO<FastReadFRead<>, FastWriteFWrite<>, debug>;
} // namespace weilycoder

#endif
