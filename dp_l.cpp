#include <iostream>
#include <vector>
using namespace std;

#define int64 int64_t

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  vector<int> a(n);
  for (int &x : a) {
    cin >> x;
  }
  vector<vector<int64>> first(n, vector<int64>(n));
  vector<vector<int64>> second(n, vector<int64>(n));
  for (int x = 0; x < n; x++) {
    first[x][x] = a[x];
    second[x][x] = -a[x];
  }
  for (int len = 2; len <= n; len++) {
    for (int l = 0, r = l + len - 1; l < n and r < n; l++, r++) {
      first[l][r] = max(second[l + 1][r] + a[l], second[l][r - 1] + a[r]);
      second[l][r] = min(first[l + 1][r] - a[l], first[l][r - 1] - a[r]);
    }
  }
  cout << first[0][n - 1];
}