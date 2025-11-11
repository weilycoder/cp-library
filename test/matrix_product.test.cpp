#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"

#include "../weilycoder/matrix.hpp"
#include "../weilycoder/number_theory/modint.hpp"
#include <cstdint>
#include <iostream>
using namespace std;
using namespace weilycoder;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin.exceptions(cin.failbit | cin.badbit);
  size_t N, M, K;
  cin >> N >> M >> K;
  NMatrix<modint<998244353>> A(N, M), B(M, K);
  for (size_t i = 0; i < N; ++i)
    for (size_t j = 0; j < M; ++j)
      cin >> A(i, j);
  for (size_t i = 0; i < M; ++i)
    for (size_t j = 0; j < K; ++j)
      cin >> B(i, j);
  auto C = A * B;
  for (size_t i = 0; i < N; ++i)
    for (size_t j = 0; j < K; ++j)
      cout << C(i, j) << " \n"[j + 1 == K];
  return 0;
}