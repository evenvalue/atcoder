#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

#define int64 int64_t

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int kMod = 1e9 + 7;

  int n;
  string s;
  cin >> n >> s;
  vector<int> ways(n);
  vector<int> pref(n + 1);
  ways[0] = 1;
  for (int i = 1; i < n; i++) {
    for (int j = 1; j <= n; j++) {
      pref[j] = (pref[j - 1] + ways[j - 1]) % kMod;
    }
    for (int num = 0; num <= i; num++) {
      const int l = (s[i - 1] == '<' ? 0 : num);
      const int r = (s[i - 1] == '<' ? num - 1 : i);
      ways[num] = (pref[r + 1] - pref[l] + kMod) % kMod;
    }
  }
  cout << accumulate(ways.begin(), ways.end(), 0LL) % kMod;
}