#include <bits/stdc++.h>
#include "atcoder/all"
using namespace std;
using namespace atcoder;

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
constexpr int kMod = 1e9 + 7;

inline void solution() {
  const string s = read::String();
  const int n = s.size();
  vector<pair<int, int>> pos(n, {-1, -1});
  for (int i = 0; i < n - 1; i++) {
    if (s[i] == 'R' and s[i + 1] == 'L') {
      pos[i] = {i, i + 1};
    }
  }
  for (int i = 1; i < n; i++) {
    if (s[i] == 'L') {
      pos[i] = pos[i - 1];
      swap(pos[i].first, pos[i].second);
    }
  }
  for (int i = n - 2; i >= 0; i--) {
    if (s[i] == 'R') {
      pos[i] = pos[i + 1];
      swap(pos[i].first, pos[i].second);
    }
  }
  vector<int> ans(n);
  for (const auto &[p, _] : pos) {
    ans[p]++;
  }
  for (const int x : ans) {
    cout << x << ' ';
  }
  cout << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  // freopen(".in", "r", stdin);
  // freopen(".out", "w", stdout);

  cout << fixed << setprecision(10);

  int testcases = 1;
  //cin >> testcases;
  while (testcases--) {
    solution();
  }
}