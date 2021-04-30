#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

#define int64 int64_t

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int64 kInf = 1e15;

  int n, capacity;
  cin >> n >> capacity;
  vector<int> w(n);
  vector<int> v(n);
  for (int i = 0; i < n; i++) {
    cin >> w[i] >> v[i];
  }
  const int value_sum = accumulate(v.begin(), v.end(), 0);
  vector<int64> small(value_sum + 1, kInf);
  small[0] = 0;
  for (int item = 0; item < n; item++) {
    for (int value = value_sum; value >= v[item]; value--) {
      small[value] = min(small[value], small[value - v[item]] + w[item]);
    }
  }
  const auto it = find_if(small.rbegin(), small.rend(), [&capacity](const int64 x) {
    return x <= capacity;
  });
  cout << value_sum - distance(small.rbegin(), it) << "\n";
}