#include <iostream>
#include <vector>
using namespace std;

int bitcount(int x) {
  int cnt = 0;
  while (x) {
    cnt += x & 1;
    x /= 2;
  }
  return cnt;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int kMod = 1e9 + 7;

  int n;
  cin >> n;
  vector<vector<int>> pair(n, vector<int>(n));
  for (auto &man : pair) {
    for (int &woman : man) {
      cin >> woman;
    }
  }
  const int N = (1 << n);
  vector<int> ways(N);
  ways[0] = 1;
  for (int mask = 1; mask < N; mask++) {
    const int man = bitcount(mask) - 1;
    for (int woman = 0; woman < n; woman++) {
      if (pair[man][woman] and (mask & (1 << woman))) {
        ways[mask] += ways[mask ^ (1 << woman)];
        ways[mask] -= (ways[mask] > kMod ? kMod : 0);
      }
    }
  }
  cout << ways[N - 1] << "\n";
}