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
  vector<double> p(n);
  for (double &x : p) {
    cin >> x;
  }
  vector<vector<double>> prob(n + 1, vector<double>(n + 1, 0.0));
  //prob[x][h] -> probability of having x coins with exactly h heads.

  prob[0][0] = 1;
  for (int x = 1; x <= n; x++) {
    prob[x][0] = prob[x - 1][0] * (1 - p[x - 1]);
    for (int h = 1; h <= x; h++) {
      prob[x][h] = (prob[x - 1][h - 1] * p[x - 1]) + (prob[x - 1][h] * (1 - p[x - 1]));
    }
  }
  double ans = 0.0;
  for (int h = n / 2 + 1; h <= n; h++) {
    ans += prob[n][h];
  }
  cout << setprecision(10) << ans << "\n";
}