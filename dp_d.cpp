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
  vector<int64> best(capacity + 1);
  for (int item = 0; item < n; item++) {
    for (int wt = capacity; wt >= w[item]; wt--) {
      best[wt] = max(best[wt], best[wt - w[item]] + v[item]);
    }
  }
  cout << best[capacity] << "\n";
}