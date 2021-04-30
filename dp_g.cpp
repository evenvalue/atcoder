#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n);
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    g[x - 1].push_back(y - 1);
  }
  vector<int> topsort;
  vector<bool> visit(n, false);
  function<void(int)> dfs = [&](const int x) {
    visit[x] = true;
    for (const int &y : g[x]) {
      if (visit[y]) continue;
      dfs(y);
    }
    topsort.push_back(x);
  };
  for (int x = 0; x < n; x++) {
    if (visit[x]) continue;
    dfs(x);
  }
  reverse(topsort.begin(), topsort.end());
  vector<int> dist(n, 0);
  for (const int &x : topsort) {
    for (int &y : g[x]) {
      dist[y] = max(dist[y], dist[x] + 1);
    }
  }
  cout << *max_element(dist.begin(), dist.end()) << "\n";
}