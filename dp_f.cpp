#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void solve(const string &s, const string &t) {
  const int n = s.size();
  const int m = t.size();
  assert(0 <= n and 0 <= m);

  vector<vector<int>> best(n, vector<int>(m));
  best[0][0] = (s[0] == t[0] ? 1 : 0);
  for (int r = 1; r < n; r++) {
    best[r][0] = (s[r] == t[0]) ? 1 : best[r - 1][0];
  }
  for (int c = 1; c < m; c++) {
    best[0][c] = (s[0] == t[c]) ? 1 : best[0][c - 1];
  }
  for (int r = 1; r < n; r++) {
    for (int c = 1; c < m; c++) {
      if (s[r] == t[c]) {
        best[r][c] = best[r - 1][c - 1] + 1;
      } else {
        best[r][c] = max(best[r][c - 1], best[r - 1][c]);
      }
    }
  }
  string ans;
  for (int r = n - 1, c = m - 1; r >= 0 and c >= 0;) {
    if (s[r] == t[c]) {
      ans += s[r];
      r--;
      c--;
    } else if (r > 0 and best[r][c] == best[r - 1][c]) {
      r--;
    } else if (c > 0 and best[r][c] == best[r][c - 1]) {
      c--;
    } else {
      break;
    }
  }
  reverse(ans.begin(), ans.end());
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  string s, t;
  cin >> s >> t;
  solve(s, t);
}