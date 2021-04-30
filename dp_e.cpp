#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int kInf = 1e9 + 10;

  int n, capacity;
  cin >> n >> capacity;
  vector<int> w(n);
  vector<int> v(n);
  int value_sum = 0;
  for (int i = 0; i < n; i++) {
    cin >> w[i] >> v[i];
    value_sum += v[i];
  }
  vector<vector<int>> best(n, vector<int>(value_sum + 1, kInf));
  for (int i = 0; i < n; i++) {
    best[i][0] = 0;
  }
  best[0][v[0]] = w[0];
  for (int i = 1; i < n; i++) {
    for (int val = 1; val <= value_sum; val++) {
      best[i][val] = best[i - 1][val];
      if (val < v[i]) continue;
      best[i][val] = min(best[i][val], best[i - 1][val - v[i]] + w[i]);
    }
  }
  for (int val = value_sum; val >= 0; val--) {
    if (best[n - 1][val] <= capacity) {
      cout << val << "\n";
      return 0;
    }
  }
}