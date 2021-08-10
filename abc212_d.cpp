#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <vector>
using namespace std;

#define debug(x) cerr << #x << ": " << x << '\n'
using int64 = int64_t;

const int64 kInfL = 1e15 + 10;
const int kInf = 1e9 + 10;
const int kMod = 1e9 + 7;

void solve() {
  int q;
  cin >> q;
  multiset<int64> m;
  int64 add = 0;
  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int x;
      cin >> x;
      m.insert(x - add);
    } else if (type == 2) {
      int x;
      cin >> x;
      add += x;
    } else {
      const auto it = m.begin();
      cout << *it + add << '\n';
      m.erase(it);
    }
  }
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