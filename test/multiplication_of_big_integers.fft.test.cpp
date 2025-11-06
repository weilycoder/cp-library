#define PROBLEM "https://judge.yosupo.jp/problem/multiplication_of_big_integers"

#include "../weilycoder/poly/fft_convolve.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace weilycoder;

static void solve() {
  string a, b;
  cin >> a >> b;

  reverse(a.begin(), a.end()), reverse(b.begin(), b.end());

  bool negative = false;
  if (a.back() == '-')
    negative = !negative, a.pop_back();
  if (b.back() == '-')
    negative = !negative, b.pop_back();

  vector<double> A, B;
  for (char c : a)
    A.push_back(c - '0');
  for (char c : b)
    B.push_back(c - '0');

  vector<double> C = fft_convolve_real(A, B);
  vector<int> result;
  int carry = 0;
  for (double x : C) {
    int val = static_cast<int>(x + 0.5) + carry;
    result.push_back(val % 10);
    carry = val / 10;
  }
  while (carry) {
    result.push_back(carry % 10);
    carry /= 10;
  }
  while (!result.empty() && result.back() == 0)
    result.pop_back();
  if (result.empty()) {
    cout << 0 << '\n';
  } else {
    if (negative)
      cout << '-';
    for (auto it = result.rbegin(); it != result.rend(); ++it)
      cout << *it;
    cout << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin.exceptions(cin.failbit | cin.badbit);
  size_t t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}