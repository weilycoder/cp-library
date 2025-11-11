---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: weilycoder/matrix.hpp
    title: Matrix implementation using narray
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/matrix_product.test.cpp
    title: test/matrix_product.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/matrix_product_mod_2.test.cpp
    title: test/matrix_product_mod_2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Run-time sized bitset
    links: []
  bundledCode: "#line 1 \"weilycoder/ds/bitset.hpp\"\n\n\n\n/**\n * @file bitset.hpp\n\
    \ * @brief Run-time sized bitset\n */\n\n#include <cstdint>\n#include <stdexcept>\n\
    #include <vector>\n\nnamespace weilycoder {\n/**\n * @class dbitset\n * @brief\
    \ Run-time sized bitset implementation\n */\nclass dbitset {\nprivate:\n  const\
    \ size_t bitsize;\n  std::vector<uint64_t> bits;\n\n  size_t extra_size() const\
    \ { return bits.size() * 64 - bitsize; }\n\n  uint64_t extra_mask() const {\n\
    \    size_t extra = extra_size();\n    return extra ? ((1ULL << (64 - extra))\
    \ - 1) : ~0ULL;\n  }\n\n  void trim_extra() { bits.back() &= extra_mask(); }\n\
    \npublic:\n  dbitset(size_t n) : bitsize(n), bits((n + 63) / 64, 0) {}\n  dbitset(const\
    \ dbitset &other) : bitsize(other.bitsize), bits(other.bits) {}\n\n  dbitset &operator=(const\
    \ dbitset &other) {\n    if (this != &other) {\n      if (bitsize != other.bitsize)\n\
    \        throw std::invalid_argument(\"Bitset sizes do not match for assignment.\"\
    );\n      bits = other.bits;\n    }\n    return *this;\n  }\n\n  struct reference\
    \ {\n    dbitset &bs;\n    size_t pos;\n\n    reference(dbitset &bs, size_t pos)\
    \ : bs(bs), pos(pos) {}\n\n    operator bool() const {\n      size_t idx = pos\
    \ / 64;\n      size_t bit = pos % 64;\n      return (bs.bits[idx] >> bit) & 1ULL;\n\
    \    }\n\n    reference &operator=(bool val) {\n      size_t idx = pos / 64;\n\
    \      size_t bit = pos % 64;\n      if (val)\n        bs.bits[idx] |= (1ULL <<\
    \ bit);\n      else\n        bs.bits[idx] &= ~(1ULL << bit);\n      return *this;\n\
    \    }\n  };\n\n  struct const_reference {\n    const dbitset &bs;\n    size_t\
    \ pos;\n\n    const_reference(const dbitset &bs, size_t pos) : bs(bs), pos(pos)\
    \ {}\n\n    operator bool() const {\n      size_t idx = pos / 64;\n      size_t\
    \ bit = pos % 64;\n      return (bs.bits[idx] >> bit) & 1ULL;\n    }\n  };\n\n\
    \  struct iterator {\n    dbitset &bs;\n    size_t pos;\n\n    iterator(dbitset\
    \ &bs, size_t pos) : bs(bs), pos(pos) {}\n    bool operator!=(const iterator &other)\
    \ const { return pos != other.pos; }\n    reference operator*() { return reference(bs,\
    \ pos); }\n    iterator &operator++() { return ++pos, *this; }\n    iterator operator++(int)\
    \ {\n      iterator temp = *this;\n      ++pos;\n      return temp;\n    }\n \
    \ };\n\n  struct const_iterator {\n    const dbitset &bs;\n    size_t pos;\n\n\
    \    const_iterator(const dbitset &bs, size_t pos) : bs(bs), pos(pos) {}\n   \
    \ bool operator!=(const const_iterator &other) const { return pos != other.pos;\
    \ }\n    const_reference operator*() const { return const_reference(bs, pos);\
    \ }\n    const_iterator &operator++() { return ++pos, *this; }\n    const_iterator\
    \ operator++(int) {\n      const_iterator temp = *this;\n      ++pos;\n      return\
    \ temp;\n    }\n  };\n\n  iterator begin() { return iterator(*this, 0); }\n  iterator\
    \ end() { return iterator(*this, bitsize); }\n  const_iterator begin() const {\
    \ return const_iterator(*this, 0); }\n  const_iterator end() const { return const_iterator(*this,\
    \ bitsize); }\n\n  reference operator[](size_t pos) { return reference(*this,\
    \ pos); }\n  const_reference operator[](size_t pos) const { return const_reference(*this,\
    \ pos); }\n\n  size_t size() const { return bitsize; }\n\n  size_t d_size() const\
    \ { return bits.size(); }\n  uint64_t &d_get_word(size_t idx) { return bits[idx];\
    \ }\n  const uint64_t &d_get_word(size_t idx) const { return bits[idx]; }\n\n\
    \  dbitset &operator&=(const dbitset &other) {\n    if (bitsize != other.bitsize)\n\
    \      throw std::invalid_argument(\"Bitset sizes do not match for AND operation.\"\
    );\n    for (size_t i = 0; i < bits.size(); ++i)\n      bits[i] &= other.bits[i];\n\
    \    return this->trim_extra(), *this;\n  }\n\n  dbitset &operator|=(const dbitset\
    \ &other) {\n    if (bitsize != other.bitsize)\n      throw std::invalid_argument(\"\
    Bitset sizes do not match for OR operation.\");\n    for (size_t i = 0; i < bits.size();\
    \ ++i)\n      bits[i] |= other.bits[i];\n    return this->trim_extra(), *this;\n\
    \  }\n\n  dbitset &operator^=(const dbitset &other) {\n    if (bitsize != other.bitsize)\n\
    \      throw std::invalid_argument(\"Bitset sizes do not match for XOR operation.\"\
    );\n    for (size_t i = 0; i < bits.size(); ++i)\n      bits[i] ^= other.bits[i];\n\
    \    return this->trim_extra(), *this;\n  }\n\n  dbitset &operator<<=(size_t shift)\
    \ {\n    if (shift >= bitsize) {\n      std::fill(bits.begin(), bits.end(), 0);\n\
    \      return *this;\n    }\n    size_t word_shift = shift / 64;\n    size_t bit_shift\
    \ = shift % 64;\n    if (bit_shift == 0) {\n      for (size_t i = bits.size()\
    \ - 1; i >= word_shift; --i)\n        bits[i] = bits[i - word_shift];\n    } else\
    \ {\n      for (size_t i = bits.size() - 1; i > word_shift; --i)\n        bits[i]\
    \ = (bits[i - word_shift] << bit_shift) |\n                  (bits[i - word_shift\
    \ - 1] >> (64 - bit_shift));\n      bits[word_shift] = bits[0] << bit_shift;\n\
    \    }\n    std::fill(bits.begin(), bits.begin() + word_shift, 0);\n    return\
    \ this->trim_extra(), *this;\n  }\n\n  dbitset &operator>>=(size_t shift) {\n\
    \    if (shift >= bitsize) {\n      std::fill(bits.begin(), bits.end(), 0);\n\
    \      return *this;\n    }\n    size_t word_shift = shift / 64;\n    size_t bit_shift\
    \ = shift % 64;\n    size_t n = bits.size();\n    if (bit_shift == 0) {\n    \
    \  for (size_t i = 0; i < n - word_shift; ++i)\n        bits[i] = bits[i + word_shift];\n\
    \    } else {\n      for (size_t i = 0; i < n - word_shift - 1; ++i)\n       \
    \ bits[i] = (bits[i + word_shift] >> bit_shift) |\n                  (bits[i +\
    \ word_shift + 1] << (64 - bit_shift));\n      bits[n - word_shift - 1] = bits[n\
    \ - 1] >> bit_shift;\n    }\n    std::fill(bits.end() - word_shift, bits.end(),\
    \ 0);\n    return *this;\n  }\n\n  friend dbitset operator~(const dbitset &bs)\
    \ {\n    dbitset result(bs.bitsize);\n    for (size_t i = 0; i < bs.bits.size();\
    \ ++i)\n      result.bits[i] = ~bs.bits[i];\n    return result.trim_extra(), result;\n\
    \  }\n\n  friend dbitset operator&(const dbitset &a, const dbitset &b) {\n   \
    \ if (a.bitsize != b.bitsize)\n      throw std::invalid_argument(\"Bitset sizes\
    \ do not match for AND operation.\");\n    dbitset result(a.bitsize);\n    for\
    \ (size_t i = 0; i < a.bits.size(); ++i)\n      result.bits[i] = a.bits[i] & b.bits[i];\n\
    \    return result.trim_extra(), result;\n  }\n\n  friend dbitset operator|(const\
    \ dbitset &a, const dbitset &b) {\n    if (a.bitsize != b.bitsize)\n      throw\
    \ std::invalid_argument(\"Bitset sizes do not match for OR operation.\");\n  \
    \  dbitset result(a.bitsize);\n    for (size_t i = 0; i < a.bits.size(); ++i)\n\
    \      result.bits[i] = a.bits[i] | b.bits[i];\n    return result.trim_extra(),\
    \ result;\n  }\n\n  friend dbitset operator^(const dbitset &a, const dbitset &b)\
    \ {\n    if (a.bitsize != b.bitsize)\n      throw std::invalid_argument(\"Bitset\
    \ sizes do not match for XOR operation.\");\n    dbitset result(a.bitsize);\n\
    \    for (size_t i = 0; i < a.bits.size(); ++i)\n      result.bits[i] = a.bits[i]\
    \ ^ b.bits[i];\n    return result.trim_extra(), result;\n  }\n\n  friend dbitset\
    \ operator<<(const dbitset &bs, size_t shift) {\n    dbitset result = bs;\n  \
    \  return result <<= shift, result;\n  }\n\n  friend dbitset operator>>(const\
    \ dbitset &bs, size_t shift) {\n    dbitset result = bs;\n    return result >>=\
    \ shift, result;\n  }\n};\n} // namespace weilycoder\n\n\n"
  code: "#ifndef WEILYCODER_BITSET_HPP\n#define WEILYCODER_BITSET_HPP\n\n/**\n * @file\
    \ bitset.hpp\n * @brief Run-time sized bitset\n */\n\n#include <cstdint>\n#include\
    \ <stdexcept>\n#include <vector>\n\nnamespace weilycoder {\n/**\n * @class dbitset\n\
    \ * @brief Run-time sized bitset implementation\n */\nclass dbitset {\nprivate:\n\
    \  const size_t bitsize;\n  std::vector<uint64_t> bits;\n\n  size_t extra_size()\
    \ const { return bits.size() * 64 - bitsize; }\n\n  uint64_t extra_mask() const\
    \ {\n    size_t extra = extra_size();\n    return extra ? ((1ULL << (64 - extra))\
    \ - 1) : ~0ULL;\n  }\n\n  void trim_extra() { bits.back() &= extra_mask(); }\n\
    \npublic:\n  dbitset(size_t n) : bitsize(n), bits((n + 63) / 64, 0) {}\n  dbitset(const\
    \ dbitset &other) : bitsize(other.bitsize), bits(other.bits) {}\n\n  dbitset &operator=(const\
    \ dbitset &other) {\n    if (this != &other) {\n      if (bitsize != other.bitsize)\n\
    \        throw std::invalid_argument(\"Bitset sizes do not match for assignment.\"\
    );\n      bits = other.bits;\n    }\n    return *this;\n  }\n\n  struct reference\
    \ {\n    dbitset &bs;\n    size_t pos;\n\n    reference(dbitset &bs, size_t pos)\
    \ : bs(bs), pos(pos) {}\n\n    operator bool() const {\n      size_t idx = pos\
    \ / 64;\n      size_t bit = pos % 64;\n      return (bs.bits[idx] >> bit) & 1ULL;\n\
    \    }\n\n    reference &operator=(bool val) {\n      size_t idx = pos / 64;\n\
    \      size_t bit = pos % 64;\n      if (val)\n        bs.bits[idx] |= (1ULL <<\
    \ bit);\n      else\n        bs.bits[idx] &= ~(1ULL << bit);\n      return *this;\n\
    \    }\n  };\n\n  struct const_reference {\n    const dbitset &bs;\n    size_t\
    \ pos;\n\n    const_reference(const dbitset &bs, size_t pos) : bs(bs), pos(pos)\
    \ {}\n\n    operator bool() const {\n      size_t idx = pos / 64;\n      size_t\
    \ bit = pos % 64;\n      return (bs.bits[idx] >> bit) & 1ULL;\n    }\n  };\n\n\
    \  struct iterator {\n    dbitset &bs;\n    size_t pos;\n\n    iterator(dbitset\
    \ &bs, size_t pos) : bs(bs), pos(pos) {}\n    bool operator!=(const iterator &other)\
    \ const { return pos != other.pos; }\n    reference operator*() { return reference(bs,\
    \ pos); }\n    iterator &operator++() { return ++pos, *this; }\n    iterator operator++(int)\
    \ {\n      iterator temp = *this;\n      ++pos;\n      return temp;\n    }\n \
    \ };\n\n  struct const_iterator {\n    const dbitset &bs;\n    size_t pos;\n\n\
    \    const_iterator(const dbitset &bs, size_t pos) : bs(bs), pos(pos) {}\n   \
    \ bool operator!=(const const_iterator &other) const { return pos != other.pos;\
    \ }\n    const_reference operator*() const { return const_reference(bs, pos);\
    \ }\n    const_iterator &operator++() { return ++pos, *this; }\n    const_iterator\
    \ operator++(int) {\n      const_iterator temp = *this;\n      ++pos;\n      return\
    \ temp;\n    }\n  };\n\n  iterator begin() { return iterator(*this, 0); }\n  iterator\
    \ end() { return iterator(*this, bitsize); }\n  const_iterator begin() const {\
    \ return const_iterator(*this, 0); }\n  const_iterator end() const { return const_iterator(*this,\
    \ bitsize); }\n\n  reference operator[](size_t pos) { return reference(*this,\
    \ pos); }\n  const_reference operator[](size_t pos) const { return const_reference(*this,\
    \ pos); }\n\n  size_t size() const { return bitsize; }\n\n  size_t d_size() const\
    \ { return bits.size(); }\n  uint64_t &d_get_word(size_t idx) { return bits[idx];\
    \ }\n  const uint64_t &d_get_word(size_t idx) const { return bits[idx]; }\n\n\
    \  dbitset &operator&=(const dbitset &other) {\n    if (bitsize != other.bitsize)\n\
    \      throw std::invalid_argument(\"Bitset sizes do not match for AND operation.\"\
    );\n    for (size_t i = 0; i < bits.size(); ++i)\n      bits[i] &= other.bits[i];\n\
    \    return this->trim_extra(), *this;\n  }\n\n  dbitset &operator|=(const dbitset\
    \ &other) {\n    if (bitsize != other.bitsize)\n      throw std::invalid_argument(\"\
    Bitset sizes do not match for OR operation.\");\n    for (size_t i = 0; i < bits.size();\
    \ ++i)\n      bits[i] |= other.bits[i];\n    return this->trim_extra(), *this;\n\
    \  }\n\n  dbitset &operator^=(const dbitset &other) {\n    if (bitsize != other.bitsize)\n\
    \      throw std::invalid_argument(\"Bitset sizes do not match for XOR operation.\"\
    );\n    for (size_t i = 0; i < bits.size(); ++i)\n      bits[i] ^= other.bits[i];\n\
    \    return this->trim_extra(), *this;\n  }\n\n  dbitset &operator<<=(size_t shift)\
    \ {\n    if (shift >= bitsize) {\n      std::fill(bits.begin(), bits.end(), 0);\n\
    \      return *this;\n    }\n    size_t word_shift = shift / 64;\n    size_t bit_shift\
    \ = shift % 64;\n    if (bit_shift == 0) {\n      for (size_t i = bits.size()\
    \ - 1; i >= word_shift; --i)\n        bits[i] = bits[i - word_shift];\n    } else\
    \ {\n      for (size_t i = bits.size() - 1; i > word_shift; --i)\n        bits[i]\
    \ = (bits[i - word_shift] << bit_shift) |\n                  (bits[i - word_shift\
    \ - 1] >> (64 - bit_shift));\n      bits[word_shift] = bits[0] << bit_shift;\n\
    \    }\n    std::fill(bits.begin(), bits.begin() + word_shift, 0);\n    return\
    \ this->trim_extra(), *this;\n  }\n\n  dbitset &operator>>=(size_t shift) {\n\
    \    if (shift >= bitsize) {\n      std::fill(bits.begin(), bits.end(), 0);\n\
    \      return *this;\n    }\n    size_t word_shift = shift / 64;\n    size_t bit_shift\
    \ = shift % 64;\n    size_t n = bits.size();\n    if (bit_shift == 0) {\n    \
    \  for (size_t i = 0; i < n - word_shift; ++i)\n        bits[i] = bits[i + word_shift];\n\
    \    } else {\n      for (size_t i = 0; i < n - word_shift - 1; ++i)\n       \
    \ bits[i] = (bits[i + word_shift] >> bit_shift) |\n                  (bits[i +\
    \ word_shift + 1] << (64 - bit_shift));\n      bits[n - word_shift - 1] = bits[n\
    \ - 1] >> bit_shift;\n    }\n    std::fill(bits.end() - word_shift, bits.end(),\
    \ 0);\n    return *this;\n  }\n\n  friend dbitset operator~(const dbitset &bs)\
    \ {\n    dbitset result(bs.bitsize);\n    for (size_t i = 0; i < bs.bits.size();\
    \ ++i)\n      result.bits[i] = ~bs.bits[i];\n    return result.trim_extra(), result;\n\
    \  }\n\n  friend dbitset operator&(const dbitset &a, const dbitset &b) {\n   \
    \ if (a.bitsize != b.bitsize)\n      throw std::invalid_argument(\"Bitset sizes\
    \ do not match for AND operation.\");\n    dbitset result(a.bitsize);\n    for\
    \ (size_t i = 0; i < a.bits.size(); ++i)\n      result.bits[i] = a.bits[i] & b.bits[i];\n\
    \    return result.trim_extra(), result;\n  }\n\n  friend dbitset operator|(const\
    \ dbitset &a, const dbitset &b) {\n    if (a.bitsize != b.bitsize)\n      throw\
    \ std::invalid_argument(\"Bitset sizes do not match for OR operation.\");\n  \
    \  dbitset result(a.bitsize);\n    for (size_t i = 0; i < a.bits.size(); ++i)\n\
    \      result.bits[i] = a.bits[i] | b.bits[i];\n    return result.trim_extra(),\
    \ result;\n  }\n\n  friend dbitset operator^(const dbitset &a, const dbitset &b)\
    \ {\n    if (a.bitsize != b.bitsize)\n      throw std::invalid_argument(\"Bitset\
    \ sizes do not match for XOR operation.\");\n    dbitset result(a.bitsize);\n\
    \    for (size_t i = 0; i < a.bits.size(); ++i)\n      result.bits[i] = a.bits[i]\
    \ ^ b.bits[i];\n    return result.trim_extra(), result;\n  }\n\n  friend dbitset\
    \ operator<<(const dbitset &bs, size_t shift) {\n    dbitset result = bs;\n  \
    \  return result <<= shift, result;\n  }\n\n  friend dbitset operator>>(const\
    \ dbitset &bs, size_t shift) {\n    dbitset result = bs;\n    return result >>=\
    \ shift, result;\n  }\n};\n} // namespace weilycoder\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: weilycoder/ds/bitset.hpp
  requiredBy:
  - weilycoder/matrix.hpp
  timestamp: '2025-11-11 20:35:49+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/matrix_product_mod_2.test.cpp
  - test/matrix_product.test.cpp
documentation_of: weilycoder/ds/bitset.hpp
layout: document
redirect_from:
- /library/weilycoder/ds/bitset.hpp
- /library/weilycoder/ds/bitset.hpp.html
title: Run-time sized bitset
---
