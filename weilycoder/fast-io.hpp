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

  inline uint64_t read_u64() {
    char c;
    do
      c = getchar();
    while (c < '0' || c > '9');
    uint64_t x = 0;
    do
      x = x * 10 + (c - '0'), c = getchar();
    while (c >= '0' && c <= '9');
    return x;
  }

  inline void write_u64(uint64_t x) {
    static char buf[20];
    size_t len = 0;
    do
      buf[len++] = '0' + (x % 10), x /= 10;
    while (x);
    for (size_t i = len - 1; ~i; --i)
      putchar(buf[i]);
  }

  inline void write_u64_line(uint64_t x) { write_u64(x), putchar('\n'); }
};

template <bool debug = false>
using FastIOStd = FastIO<FastReadMMap, FastWriteFWrite<>, debug>;

template <bool debug = false>
using FastIOFile = FastIO<FastReadFRead<>, FastWriteFWrite<>, debug>;
} // namespace weilycoder

#endif
