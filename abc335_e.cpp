#include <bits/stdc++.h>
using namespace std;

#ifdef evenvalue
  #include "debug.h"
#else
  #define debug(...)
#endif

using int64 = long long;
using ld = long double;

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using max_heap = priority_queue<T, vector<T>, less<T>>;

namespace Read {
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
}//namespace Read

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;
constexpr int kMaxN = 2e5 + 10;

class dsu {
  int n;
  std::vector<int> e;

  int pfind(const int x) {
    return (e[x] < 0 ? x : e[x] = pfind(e[x]));
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
    comp--;
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
        res.end()
    );
    return res;
  }
};

inline void solution() {
  const int n = Read::Int();
  const int m = Read::Int();

  const vector<int> a = Read::Vec<int>(n);

  dsu d(n);
  vector<vector<int>> g(n);

  for (int i = 0; i < m; i++) {
    const int x = Read::Int() - 1;
    const int y = Read::Int() - 1;

    if (a[x] < a[y]) {
      g[x].push_back(y);
    } else if (a[x] > a[y]) {
      g[y].push_back(x);
    } else {
      d.unite(x, y);
    }
  }

  vector<int> order(n);
  iota(order.begin(), order.end(), 0);

  sort(order.begin(), order.end(), [&](const int i, const int j) {
    return a[i] < a[j];
  });

  vector<int> dp(n, -kInf);
  dp[d.find(0)] = 1;

  for (const int x : order) {
    for (const int y : g[x]) {
      dp[d.find(y)] = max(dp[d.find(y)], dp[d.find(x)] + 1);
    }
  }

  const int ans = dp[d.find(n - 1)];
  cout << max(0, ans) << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);

  cout << fixed << setprecision(10);

  int testcases = 1;
  //cin >> testcases;
  while (testcases--) {
    solution();
  }
}