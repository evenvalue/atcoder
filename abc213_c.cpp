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
  int h, w, n;
  cin >> h >> w >> n;
  vector<pair<int, int>> cells(n);
  vector<int> row(n), col(n);
  for (auto &[r, c] : cells) {
    cin >> r >> c;
    row.push_back(r);
    col.push_back(c);
  }
  sort(row.begin(), row.end()), row.erase(unique(row.begin(), row.end()), row.end());
  sort(col.begin(), col.end()), col.erase(unique(col.begin(), col.end()), col.end());
  for (auto &[r, c] : cells) {
    int idx_r = distance(row.begin(), lower_bound(row.begin(), row.end(), r));
    int idx_c = distance(col.begin(), lower_bound(col.begin(), col.end(), c));
    r -= r - idx_r;
    c -= c - idx_c;
  }
  for (const auto &[r, c] : cells) {
    cout << r << ' ' << c << '\n';
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