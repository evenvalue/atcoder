#include <iostream>
#include <vector>
using namespace std;

#define int64 int64_t

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int64 kInf = 1e13;

  int n;
  cin >> n;
  vector<int> a(n);
  for (int &x : a) {
    cin >> x;
  }
  auto sum = [&a](const int l, const int r) -> int64 {
    int64 s = 0;
    for (int i = l; i <= r; i++) {
      s += a[i];
    }
    return s;
  };
  vector<vector<int64>> best(n, vector<int64>(n, kInf));
  for (int x = 0; x < n; x++) {
    best[x][x] = 0;
  }
  for (int len = 2; len <= n; len++) {
    for (int l = 0, r = len + l - 1; l < n and r < n; l++, r++) {
      const int64 cost = sum(l, r);
      for (int cut = l; cut < r; cut++) {
        best[l][r] = min(best[l][r], best[l][cut] + best[cut + 1][r] + cost);
      }
    }
  }
  cout << best[0][n - 1] << "\n";
}