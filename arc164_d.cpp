#include "atcoder/all"
#include <bits/stdc++.h>
using namespace std;

#ifdef evenvalue
  #include "debug.h"
  #define debug(...) print(#__VA_ARGS__, __VA_ARGS__)
#else
  #define debug(...)
#endif

using int64 = long long;
using ld = long double;

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using max_heap = priority_queue<T, vector<T>, less<T>>;

namespace read {
int Int() {
  int x;
  cin >> x;
  return x;
}
int64 Int64() {
  int64 x;
  cin >> x;
  return x;
}
char Char() {
  char c;
  cin >> c;
  return c;
}
string String() {
  string s;
  cin >> s;
  return s;
}
double Double() {
  return stod(String());
}
ld LongDouble() {
  return stold(String());
}
template<typename T1, typename T2>
pair<T1, T2> Pair() {
  pair<T1, T2> p;
  cin >> p.first >> p.second;
  return p;
}
template<typename T>
vector<T> Vec(const int n) {
  vector<T> v(n);
  for (T &x : v) {
    cin >> x;
  }
  return v;
}
template<typename T>
vector<vector<T>> VecVec(const int n, const int m) {
  vector<vector<T>> v(n);
  for (vector<T> &vec : v) {
    vec = Vec<T>(m);
  }
  return v;
}
}//namespace read

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 998244353;
using mint = atcoder::static_modint<kMod>;

inline void solution() {
  const int n = read::Int();
  const string s = "-" + read::String();

  vector<vector<mint>> ways(n + 1, vector<mint>(n + 1));
  ways[0][0] = 1;
  for (int pos = 0; pos <= n; pos++) {
    for (int neg = 0; neg <= n; neg++) {
      if (pos != 0 and s[pos + neg] != '-') {
        ways[pos][neg] += ways[pos - 1][neg];
      }
      if (neg != 0 and s[pos + neg] != '+') {
        ways[pos][neg] += ways[pos][neg - 1];
      }
    }
  }

  vector<vector<mint>> dp(n + 1, vector<mint>(n + 1));
  dp[0][0] = 0;

  for (int i = 1; i <= n; i++) {
    dp[i][0] = (dp[i - 1][0] + i) * ways[i][0];
    dp[0][i] = (dp[0][i - 1] + i) * ways[0][i];
  }

  for (int pos = 1; pos <= n; pos++) {
    for (int neg = 1; neg <= n; neg++) {
      if (ways[pos][neg] == 0) continue;
      if (s[pos + neg] != '-') {
        dp[pos][neg] += dp[pos - 1][neg];
      }
      if (s[pos + neg] != '+') {
        dp[pos][neg] += dp[pos][neg - 1];
      }
      dp[pos][neg] += ways[pos][neg] * abs(pos - neg);
    }
  }

  cout << dp[n][n].val() << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cout << fixed << setprecision(10);

  int testcases = 1;
  //cin >> testcases;
  while (testcases--) {
    solution();
  }
}