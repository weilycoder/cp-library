#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include "../weilycoder/fast-io.hpp"
using namespace weilycoder;

static FastIOMMap<> io;

int main() {
  size_t t = io.read_u64();
  while (t--) {
    uint64_t a = io.read_u64();
    uint64_t b = io.read_u64();
    uint64_t c = a + b;
    io.write_u64_line(c);
  }
  return 0;
}