#ifndef WEILYCODER_BITSET_HPP
#define WEILYCODER_BITSET_HPP

/**
 * @file bitset.hpp
 * @brief Run-time sized bitset
 */

#include <cstdint>
#include <stdexcept>
#include <vector>

namespace weilycoder {
/**
 * @class dbitset
 * @brief Run-time sized bitset implementation
 */
class dbitset {
private:
  const size_t bitsize;
  std::vector<uint64_t> bits;

  size_t extra_size() const { return bits.size() * 64 - bitsize; }

  uint64_t extra_mask() const {
    size_t extra = extra_size();
    return extra ? ((1ULL << (64 - extra)) - 1) : ~0ULL;
  }

  void trim_extra() { bits.back() &= extra_mask(); }

public:
  dbitset(size_t n) : bitsize(n), bits((n + 63) / 64, 0) {}
  dbitset(const dbitset &other) : bitsize(other.bitsize), bits(other.bits) {}

  dbitset &operator=(const dbitset &other) {
    if (this != &other) {
      if (bitsize != other.bitsize)
        throw std::invalid_argument("Bitset sizes do not match for assignment.");
      bits = other.bits;
    }
    return *this;
  }

  struct reference {
    dbitset &bs;
    size_t pos;

    reference(dbitset &bs, size_t pos) : bs(bs), pos(pos) {}

    operator bool() const {
      size_t idx = pos / 64;
      size_t bit = pos % 64;
      return (bs.bits[idx] >> bit) & 1ULL;
    }

    reference &operator=(bool val) {
      size_t idx = pos / 64;
      size_t bit = pos % 64;
      if (val)
        bs.bits[idx] |= (1ULL << bit);
      else
        bs.bits[idx] &= ~(1ULL << bit);
      return *this;
    }
  };

  struct const_reference {
    const dbitset &bs;
    size_t pos;

    const_reference(const dbitset &bs, size_t pos) : bs(bs), pos(pos) {}

    operator bool() const {
      size_t idx = pos / 64;
      size_t bit = pos % 64;
      return (bs.bits[idx] >> bit) & 1ULL;
    }
  };

  struct iterator {
    dbitset &bs;
    size_t pos;

    iterator(dbitset &bs, size_t pos) : bs(bs), pos(pos) {}
    bool operator!=(const iterator &other) const { return pos != other.pos; }
    reference operator*() { return reference(bs, pos); }
    iterator &operator++() { return ++pos, *this; }
    iterator operator++(int) {
      iterator temp = *this;
      ++pos;
      return temp;
    }
  };

  struct const_iterator {
    const dbitset &bs;
    size_t pos;

    const_iterator(const dbitset &bs, size_t pos) : bs(bs), pos(pos) {}
    bool operator!=(const const_iterator &other) const { return pos != other.pos; }
    const_reference operator*() const { return const_reference(bs, pos); }
    const_iterator &operator++() { return ++pos, *this; }
    const_iterator operator++(int) {
      const_iterator temp = *this;
      ++pos;
      return temp;
    }
  };

  iterator begin() { return iterator(*this, 0); }
  iterator end() { return iterator(*this, bitsize); }
  const_iterator begin() const { return const_iterator(*this, 0); }
  const_iterator end() const { return const_iterator(*this, bitsize); }

  reference operator[](size_t pos) { return reference(*this, pos); }
  const_reference operator[](size_t pos) const { return const_reference(*this, pos); }

  size_t size() const { return bitsize; }

  size_t d_size() const { return bits.size(); }
  uint64_t &d_get_word(size_t idx) { return bits[idx]; }
  const uint64_t &d_get_word(size_t idx) const { return bits[idx]; }

  dbitset &operator&=(const dbitset &other) {
    if (bitsize != other.bitsize)
      throw std::invalid_argument("Bitset sizes do not match for AND operation.");
    for (size_t i = 0; i < bits.size(); ++i)
      bits[i] &= other.bits[i];
    return this->trim_extra(), *this;
  }

  dbitset &operator|=(const dbitset &other) {
    if (bitsize != other.bitsize)
      throw std::invalid_argument("Bitset sizes do not match for OR operation.");
    for (size_t i = 0; i < bits.size(); ++i)
      bits[i] |= other.bits[i];
    return this->trim_extra(), *this;
  }

  dbitset &operator^=(const dbitset &other) {
    if (bitsize != other.bitsize)
      throw std::invalid_argument("Bitset sizes do not match for XOR operation.");
    for (size_t i = 0; i < bits.size(); ++i)
      bits[i] ^= other.bits[i];
    return this->trim_extra(), *this;
  }

  dbitset &operator<<=(size_t shift) {
    if (shift >= bitsize) {
      std::fill(bits.begin(), bits.end(), 0);
      return *this;
    }
    size_t word_shift = shift / 64;
    size_t bit_shift = shift % 64;
    if (bit_shift == 0) {
      for (size_t i = bits.size() - 1; i >= word_shift; --i)
        bits[i] = bits[i - word_shift];
    } else {
      for (size_t i = bits.size() - 1; i > word_shift; --i)
        bits[i] = (bits[i - word_shift] << bit_shift) |
                  (bits[i - word_shift - 1] >> (64 - bit_shift));
      bits[word_shift] = bits[0] << bit_shift;
    }
    std::fill(bits.begin(), bits.begin() + word_shift, 0);
    return this->trim_extra(), *this;
  }

  dbitset &operator>>=(size_t shift) {
    if (shift >= bitsize) {
      std::fill(bits.begin(), bits.end(), 0);
      return *this;
    }
    size_t word_shift = shift / 64;
    size_t bit_shift = shift % 64;
    size_t n = bits.size();
    if (bit_shift == 0) {
      for (size_t i = 0; i < n - word_shift; ++i)
        bits[i] = bits[i + word_shift];
    } else {
      for (size_t i = 0; i < n - word_shift - 1; ++i)
        bits[i] = (bits[i + word_shift] >> bit_shift) |
                  (bits[i + word_shift + 1] << (64 - bit_shift));
      bits[n - word_shift - 1] = bits[n - 1] >> bit_shift;
    }
    std::fill(bits.end() - word_shift, bits.end(), 0);
    return *this;
  }

  friend dbitset operator~(const dbitset &bs) {
    dbitset result(bs.bitsize);
    for (size_t i = 0; i < bs.bits.size(); ++i)
      result.bits[i] = ~bs.bits[i];
    return result.trim_extra(), result;
  }

  friend dbitset operator&(const dbitset &a, const dbitset &b) {
    if (a.bitsize != b.bitsize)
      throw std::invalid_argument("Bitset sizes do not match for AND operation.");
    dbitset result(a.bitsize);
    for (size_t i = 0; i < a.bits.size(); ++i)
      result.bits[i] = a.bits[i] & b.bits[i];
    return result.trim_extra(), result;
  }

  friend dbitset operator|(const dbitset &a, const dbitset &b) {
    if (a.bitsize != b.bitsize)
      throw std::invalid_argument("Bitset sizes do not match for OR operation.");
    dbitset result(a.bitsize);
    for (size_t i = 0; i < a.bits.size(); ++i)
      result.bits[i] = a.bits[i] | b.bits[i];
    return result.trim_extra(), result;
  }

  friend dbitset operator^(const dbitset &a, const dbitset &b) {
    if (a.bitsize != b.bitsize)
      throw std::invalid_argument("Bitset sizes do not match for XOR operation.");
    dbitset result(a.bitsize);
    for (size_t i = 0; i < a.bits.size(); ++i)
      result.bits[i] = a.bits[i] ^ b.bits[i];
    return result.trim_extra(), result;
  }

  friend dbitset operator<<(const dbitset &bs, size_t shift) {
    dbitset result = bs;
    return result <<= shift, result;
  }

  friend dbitset operator>>(const dbitset &bs, size_t shift) {
    dbitset result = bs;
    return result >>= shift, result;
  }
};
} // namespace weilycoder

#endif
