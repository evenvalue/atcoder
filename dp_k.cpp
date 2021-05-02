#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for (int &x : a) {
    cin >> x;
  }
  vector<bool> dp(k + 1, false);
  for (int stones = 1; stones <= k; stones++) {
    for (const int &x : a) {
      if (stones < x) continue;
      dp[stones] = dp[stones] | (not dp[stones - x]);
    }
  }
  cout << (dp[k] ? "First" : "Second") << "\n";
}