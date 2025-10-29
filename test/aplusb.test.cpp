#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../weilycoder/fast-io.hpp"
using namespace weilycoder;

static FastIOMMap<true> io;

int main() {
  uint64_t a = io.read_u64();
  uint64_t b = io.read_u64();
  io.write_u64_line(a + b);
  return 0;
}