#include <bits/stdc++.h>
#include "atcoder/all"
using namespace std;

#define int long long

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
using mint = atcoder::static_modint<kMod>;

template<typename T, class F = function<T(const T &, const T &)>>
class SparseTable {
  const int n;
  vector<vector<T>> table;
  const F unite;

public:
  explicit SparseTable(const vector<T> &a, const F &f) : n(static_cast<int>(a.size())), unite(f) {
    int log = 32 - __builtin_clz(n);
    table.resize(log);
    table[0] = a;
    for (int j = 1; j < log; j++) {
      table[j].resize(n - (1 << j) + 1);
      for (int i = 0; i <= n - (1 << j); i++) {
        table[j][i] = unite(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  T get(const int l, const int r) const {
    assert(0 <= l && l <= r && r <= n - 1);
    const int log = 32 - __builtin_clz(r - l + 1) - 1;
    return unite(table[log][l], table[log][r - (1 << log) + 1]);
  }
};

inline void solution() {
  const int n = read::Int();
  const int m = read::Int();

  vector<int> a = read::Vec<int>(n);
  vector<int> c = read::Vec<int>(n);
  vector<int> b = read::Vec<int>(m);

  a.insert(a.begin(), 0);
  c.insert(c.begin(), 0);

  SparseTable<int> st(c, [&](const int x, const int y) {
    return min(x, y);
  });

  vector<bool> want(n + 1);
  for (int i = 0; i < m; i++) want[b[i]] = true;

  vector<vector<int64>> dp(n + 1, vector<int64>(n + 1, kInf64));
  dp[0][0] = 0;
  for (int i = 1; i <= n; i++) {
    if (not want[i]) dp[i][0] = dp[i - 1][0];
    for (int take = 1; take <= i; take++) {
      dp[i][take] = dp[i - 1][take - 1] + st.get(i - take + 1, i) + a[i];
      if (not want[i]) {
        dp[i][take] = min(dp[i - 1][take], dp[i][take]);
      }
    }
  }

  cout << *min_element(dp[n].begin(), dp[n].end()) << '\n';
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