#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb_128bit"

#include "../weilycoder/fast-io.hpp"
using namespace weilycoder;

static FastIOFile<> io;

int main() {
  size_t t = io.read_u64();
  while (t--) {
    auto a = io.read_i128();
    auto b = io.read_i128();
    io.write_i128_line(a + b);
  }
  return 0;
}