#include <functional>
#include <iostream>
#include <vector>
using namespace std;

#define int64 int64_t

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int kMod = 1e9 + 7;

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
  vector<int64> white(n, 1);
  vector<int64> black(n, 1);
  function<void(int, int)> dfs = [&](const int x, const int p) {
    for (const int y : g[x]) {
      if (y == p) continue;
      dfs(y, x);
      white[x] *= white[y] + black[y];
      white[x] %= kMod;
      black[x] *= white[y];
      black[x] %= kMod;
    }
  };
  dfs(0, -1);
  cout << (white[0] + black[0]) % kMod << "\n";
}