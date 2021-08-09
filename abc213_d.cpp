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
  int n;
  cin >> n;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    x--, y--;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  for (vector<int> &nbr : g) {
    sort(nbr.begin(), nbr.end());
  }
  vector<int> ans;
  function<void(int, int)> dfs = [&](const int x, const int p) {
    ans.push_back(x);
    for (const int y : g[x]) {
      if (y == p) continue;
      dfs(y, x);
      ans.push_back(x);
    }
  };
  dfs(0, -1);
  for (const int x : ans) {
    cout << x + 1 << ' ';
  }
  cout << '\n';
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