#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#ifdef evenvalue
  #include "debug.h"
  #define debug(...) print(#__VA_ARGS__, __VA_ARGS__)
#else
  #define debug(...)
#endif

using int64 = int64_t;
using ld = long double;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

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

class dsu {
  int n;
  std::vector<int> e;

  int pfind(const int x) {
    return (e[x] < 0 ? x : pfind(e[x]));
  }

public:
  dsu() : n(0), comp(0) {}
  explicit dsu(const int n) : n(n), comp(n), e(n, -1) {}

  int comp;

  int find(const int x) {
    assert(0 <= x and x < n);
    return pfind(x);
  }

  bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    if (e[x] > e[y]) swap(x, y);
    e[x] += e[y];
    e[y] = x;
    return true;
  }

  bool same(const int x, const int y) {
    return (find(x) == find(y));
  }

  int size(const int x) {
    return -e[find(x)];
  }

  std::vector<std::vector<int>> components() {
    std::vector<std::vector<int>> res(n);
    for (int x = 0; x < n; x++) {
      res[pfind(x)].push_back(x);
    }
    res.erase(
        std::remove_if(res.begin(), res.end(), [&](const std::vector<int> &v) { return v.empty(); }),
        res.end());
    return res;
  }
};

inline void solution() {
  const int n = read::Int(), k = read::Int();
  vector<vector<int>> a = read::VecVec<int>(n, n);

  dsu columns(n), rows(n);
  for (int r1 = 0; r1 < n; r1++) {
    for (int r2 = r1 + 1; r2 < n; r2++) {
      bool unite = true;
      for (int i = 0; i < n; i++) {
        unite &= (a[r1][i] + a[r2][i] <= k);
      }
      if (unite) rows.unite(r1, r2);
    }
  }

  for (int c1 = 0; c1 < n; c1++) {
    for (int c2 = 0; c2 < n; c2++) {
      bool unite = true;
      for (int i = 0; i < n; i++) {
        unite &= (a[i][c1] + a[i][c2] <= k);
      }
      if (unite) columns.unite(c1, c2);
    }
  }

  vector<int> fact(n + 10);
  fact[0] = fact[1] = 1;
  for (int i = 2; i <= n; i++) {
    fact[i] = (fact[i - 1] * 1LL * i) % kMod;
  }

  int64 ans_rows = 1, ans_columns = 1;
  const auto comp_rows = rows.components(), comp_columns = columns.components();
  for (const auto &comp : comp_rows) {
    ans_rows *= fact[comp.size()];
    ans_rows %= kMod;
  }
  for (const auto &comp : comp_columns) {
    ans_columns *= fact[comp.size()];
    ans_columns %= kMod;
  }
  cout << (ans_rows * 1LL * ans_columns) % kMod << '\n';
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