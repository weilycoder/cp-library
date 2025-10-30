#ifndef WEILYCODER_FAST_IO_HPP
#define WEILYCODER_FAST_IO_HPP

/**
 * @file fast-io.hpp
 * @brief Fast Input/Output Utilities
 */

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <limits>

#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

namespace weilycoder {
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
/**
 * @brief Fast Reader using Memory-Mapped I/O
 */
struct FastReadMMap {
  size_t file_size;
  char *data, *pos;

  FastReadMMap(const FastReadMMap &) = delete;
  FastReadMMap &operator=(const FastReadMMap &) = delete;

  /**
   * @brief Constructs a FastReadMMap object and memory-maps stdin.
   *        If mapping fails, sets file_size to max size_t.
   */
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

  /**
   * @brief Destructor that unmaps the memory-mapped file.
   */
  ~FastReadMMap() {
    if (file_size != std::numeric_limits<size_t>::max())
      munmap(data, file_size);
  }

  /**
   * @brief Gets the next character from the memory-mapped input.
   * @return The next character, or EOF if the end of the file is reached.
   */
  inline char getchar() {
    return static_cast<size_t>(pos - data) < file_size ? *pos++ : EOF;
  }

  /**
   * @brief Alias for getchar().
   * @return The next character from input.
   */
  inline char operator()() { return getchar(); }
};
#endif

/**
 * @brief Fast Reader using fread
 * @tparam buffer_size Size of the internal buffer (default: 1 MB)
 */
template <size_t buffer_size = 1 << 20> struct FastReadFRead {
  char buf[buffer_size], *pos = buf, *end = buf;

  FastReadFRead() = default;

  FastReadFRead(const FastReadFRead &) = delete;
  FastReadFRead &operator=(const FastReadFRead &) = delete;

  /**
   * @brief Gets the next character from input using buffered fread.
   * @return The next character, or EOF if the end of the file is reached.
   */
  inline char getchar() {
    return pos == end && (end = (pos = buf) + fread(buf, 1, buffer_size, stdin),
                          pos == end)
               ? EOF
               : *pos++;
  }

  /**
   * @brief Clears the internal buffer.
   */
  inline void clear() { pos = end = buf; }

  /**
   * @brief Reopens the input stream by clearing the buffer
   *        and seeking to the beginning.
   */
  inline void reopen() { clear(), fseek(stdin, 0, SEEK_SET); }

  /**
   * @brief Alias for getchar().
   * @return The next character from input.
   */
  inline char operator()() { return getchar(); }
};

/**
 * @brief Fast Writer using fwrite
 * @tparam buffer_size Size of the internal buffer (default: 1 MB)
 */
template <size_t buffer_size = 1 << 20> struct FastWriteFWrite {
  char buf[buffer_size], *pos = buf;

  FastWriteFWrite() = default;
  ~FastWriteFWrite() { flush(); }

  FastWriteFWrite(const FastWriteFWrite &) = delete;
  FastWriteFWrite &operator=(const FastWriteFWrite &) = delete;

  /**
   * @brief Puts a character into the output buffer.
   *        Flushes the buffer if it is full.
   * @param c Character to put into the buffer.
   */
  inline void putchar(char c) {
    if (pos - buf == buffer_size)
      flush();
    *pos++ = c;
  }

  /**
   * @brief Flushes the output buffer to stdout.
   */
  inline void flush() {
    size_t write_size = pos - buf;
    if (write_size) {
      fwrite(buf, 1, write_size, stdout);
      pos = buf;
    }
  }

  /**
   * @brief Alias for putchar().
   * @param c Character to put into the buffer.
   */
  inline void operator()(char c) { putchar(c); }
};

/**
 * @brief Fast Input/Output handler combining a Reader and a Writer.
 * @tparam Reader Type of the input reader.
 * @tparam Writer Type of the output writer.
 * @tparam debug If true, uses standard I/O functions for debugging.
 */
template <typename Reader, typename Writer, bool debug = false> struct FastIO {
  Reader reader;
  Writer writer;

  FastIO() = default;

  FastIO(const FastIO &) = delete;
  FastIO &operator=(const FastIO &) = delete;

  /**
   * @brief Gets the next character from input.
   * @return The next character from input.
   */
  inline char getchar() {
    if constexpr (debug)
      return std::getchar();
    else
      return reader.getchar();
  }

  /**
   * @brief Puts a character into output.
   * @param c Character to put into output.
   */
  inline void putchar(char c) {
    if constexpr (debug)
      std::putchar(c), std::fflush(stdout);
    else
      writer.putchar(c);
  }

  /**
   * @brief Flushes the output buffer.
   */
  inline void flush() { writer.flush(); }

  /**
   * @brief Computes the absolute value of a 32-bit integer.
   * @param x The integer to compute the absolute value for.
   * @return The absolute value of x.
   */
  static int32_t abs(int32_t x) { return x >= 0 ? x : -x; }

  /**
   * @brief Reads an unsigned integer of type utype from input.
   * @tparam utype Unsigned integer type to read.
   * @return The read unsigned integer.
   */
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

  /**
   * @brief Reads a signed integer of type itype from input.
   * @tparam itype Signed integer type to read.
   * @tparam utype Unsigned integer type used for intermediate calculations,
   *         should be the corresponding unsigned type of itype.
   * @return The read signed integer.
   */
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

  /**
   * @brief Writes an unsigned integer of type utype to output.
   * @tparam utype Unsigned integer type to write.
   * @tparam bufsize Size of the internal buffer used for conversion.
   * @param x The unsigned integer to write.
   */
  template <typename utype, size_t bufsize> inline void _write_u(utype x) {
    static char buf[bufsize];
    size_t len = 0;
    do
      buf[len++] = '0' + (x % 10), x /= 10;
    while (x);
    for (size_t i = len - 1; ~i; --i)
      putchar(buf[i]);
  }

  /**
   * @brief Writes a signed integer of type itype to output.
   * @tparam itype Signed integer type to write.
   * @tparam bufsize Size of the internal buffer used for conversion.
   * @param x The signed integer to write.
   */
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

  /**
   * @brief Reads a signed 32-bit integer from input.
   * @return The read signed 32-bit integer.
   */
  inline int32_t read_i32() { return _read_i<int32_t, uint32_t>(); }

  /**
   * @brief Reads an unsigned 32-bit integer from input.
   * @return The read unsigned 32-bit integer.
   */
  inline uint32_t read_u32() { return _read_u<uint32_t>(); }

  /**
   * @brief Writes a signed 32-bit integer to output.
   * @param x The signed 32-bit integer to write.
   */
  inline void write_i32(int32_t x) { _write_i<int32_t, 10>(x); }

  /**
   * @brief Writes an unsigned 32-bit integer to output.
   * @param x The unsigned 32-bit integer to write.
   */
  inline void write_u32(uint32_t x) { _write_u<uint32_t, 10>(x); }

  /**
   * @brief Reads a signed 64-bit integer from input.
   * @return The read signed 64-bit integer.
   */
  inline int64_t read_i64() { return _read_i<int64_t, uint64_t>(); }

  /**
   * @brief Reads an unsigned 64-bit integer from input.
   * @return The read unsigned 64-bit integer.
   */
  inline uint64_t read_u64() { return _read_u<uint64_t>(); }

  /**
   * @brief Writes a signed 64-bit integer to output.
   * @param x The signed 64-bit integer to write.
   */
  inline void write_i64(int64_t x) { _write_i<int64_t, 20>(x); }

  /**
   * @brief Writes an unsigned 64-bit integer to output.
   * @param x The unsigned 64-bit integer to write.
   */
  inline void write_u64(uint64_t x) { _write_u<uint64_t, 20>(x); }

  /**
   * @brief Reads a signed 128-bit integer from input.
   * @return The read signed 128-bit integer.
   */
  inline __int128 read_i128() { return _read_i<__int128, unsigned __int128>(); }

  /**
   * @brief Reads an unsigned 128-bit integer from input.
   * @return The read unsigned 128-bit integer.
   */
  inline unsigned __int128 read_u128() { return _read_u<unsigned __int128>(); }

  /**
   * @brief Writes a signed 128-bit integer to output.
   * @param x The signed 128-bit integer to write.
   */
  inline void write_i128(__int128 x) { _write_i<__int128, 40>(x); }

  /**
   * @brief Writes an unsigned 128-bit integer to output.
   * @param x The unsigned 128-bit integer to write.
   */
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

#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
template <bool debug = false>
using FastIOMMap = FastIO<FastReadMMap, FastWriteFWrite<>, debug>;
#endif

template <bool debug = false>
using FastIOFile = FastIO<FastReadFRead<>, FastWriteFWrite<>, debug>;
} // namespace weilycoder

#endif
