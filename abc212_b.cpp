#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

#define debug(x) cerr << #x << ": " << x << '\n'
using int64 = int64_t;

const int64 kInfL = 1e15 + 10;
const int kInf = 1e9 + 10;
const int kMod = 1e9 + 7;

void solve() {
  array<int, 4> p{};
  for (const int i : {0, 1, 2, 3}) {
    char c;
    cin >> c;
    p[i] = c - '0';
  }
  bool weak = true;
  for (int i = 0; i < 3; i++) {
    weak &= ((p[i] + 1) % 10 == p[i + 1]);
  }
  cout << (weak or count(p.begin(), p.end(), p[0]) == 4 ? "Weak" : "Strong") << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t = 1;
  //cin >> t;
  while (t--) {
    solve();
  }
}