#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

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

  vector<vector<vector<double>>> dp(n + 1, vector<vector<double>>(n + 1, vector<double>(n + 1, 0.0)));
  for (int sum = 1; sum <= n; sum++) {
    const auto convert = (double) sum;
    const double empty = ((n - sum) / convert);
    for (int z = 0; z <= sum; z++) {
      for (int y = 0; y <= sum - z; y++) {
        const int x = sum - z - y;
        dp[x][y][z] = empty;
        if (x != 0) {
          dp[x][y][z] += (x / convert) * (dp[x - 1][y][z] + 1);
        }
        if (y != 0) {
          dp[x][y][z] += (y / convert) * (dp[x + 1][y - 1][z] + 1);
        }
        if (z != 0) {
          dp[x][y][z] += (z / convert) * (dp[x][y + 1][z - 1] + 1);
        }
      }
    }
  }
  const int x = count(a.begin(), a.end(), 1);
  const int y = count(a.begin(), a.end(), 2);
  const int z = count(a.begin(), a.end(), 3);
  cout << setprecision(16) << dp[x][y][z] << "\n";
}