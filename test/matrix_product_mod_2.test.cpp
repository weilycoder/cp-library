#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product_mod_2"

#include "../weilycoder/matrix.hpp"
#include <iostream>
using namespace std;
using namespace weilycoder;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin.exceptions(cin.failbit | cin.badbit);
  size_t N, M, K;
  cin >> N >> M >> K;
  BMatrix A(N, M), B(M, K);
  for (size_t i = 0; i < N; ++i) {
    string s;
    cin >> s;
    for (size_t j = 0; j < M; ++j)
      A(i, j) = s[j] - '0';
  }
  for (size_t i = 0; i < M; ++i) {
    string s;
    cin >> s;
    for (size_t j = 0; j < K; ++j)
      B(i, j) = s[j] - '0';
  }
  BMatrix C = A * B;
  for (size_t i = 0; i < N; ++i)
    for (size_t j = 0; j < K; ++j)
      cout << (C(i, j) ? 1 : 0) << (j + 1 == K ? "\n" : "");
  return 0;
}