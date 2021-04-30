#include <iostream>
#include <vector>
using namespace std;

int abs(const int x) {
  return (x < 0 ? -x : x);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int kInf = 1e9 + 10;

  int n, k;
  cin >> n >> k;
  vector<int> h(n);
  for (int &x : h) {
    cin >> x;
  }
  vector<int> dp(n, kInf);
  dp[n - 1] = 0;
  for (int i = n - 2; i >= 0; i--) {
    for (int jump = 1; i + jump < n and jump <= k; jump++) {
      dp[i] = min(dp[i], abs(h[i] - h[i + jump]) + dp[i + jump]);
    }
  }
  cout << dp[0] << "\n";
}