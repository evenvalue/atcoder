#include <iostream>
#include <vector>
using namespace std;

int abs(const int x) {
  return x < 0 ? -x : x;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  vector<int> h(n);
  for (int &x : h) {
    cin >> x;
  }
  vector<int> dp(n);
  dp[n - 2] = abs(h[n - 2] - h[n - 1]);
  for (int i = n - 3; i >= 0; i--) {
    dp[i] = min(abs(h[i] - h[i + 1]) + dp[i + 1], abs(h[i] - h[i + 2]) + dp[i + 2]);
  }
  cout << dp[0] << "\n";
}