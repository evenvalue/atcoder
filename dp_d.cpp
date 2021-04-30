#include <iostream>
#include <vector>
using namespace std;

#define int64 int64_t

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, capacity;
  cin >> n >> capacity;
  vector<int> w(n);
  vector<int> v(n);
  for (int i = 0; i < n; i++) {
    cin >> w[i] >> v[i];
  }
  vector<vector<int64>> best(n, vector<int64>(capacity + 1));
  for (int wt = w[0]; wt <= capacity; wt++) {
    best[0][wt] = v[0];
  }
  for (int i = 1; i < n; i++) {
    for (int wt = 1; wt <= capacity; wt++) {
      best[i][wt] = best[i - 1][wt];
      if (w[i] > wt) continue;
      best[i][wt] = max(best[i][wt], best[i - 1][wt - w[i]] + v[i]);
    }
  }
  cout << best[n - 1][capacity] << "\n";
}