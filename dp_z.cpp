#include <bits/stdc++.h>
#include "atcoder/all"
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
constexpr int64 kInf64 = 1e18 + 10;
constexpr int kMod = 1e9 + 7;
using mint = atcoder::static_modint<kMod>;

struct Line {
  int64 m, c;
  mutable int64 p;
  bool operator<(const Line &other) const {
    return m < other.m;
  }
  bool operator<(int64 x) const {
    return p < x;
  }
};

struct LineContainer : std::multiset<Line, std::less<>> {
private:
  static const int64 kInfinity = LLONG_MAX;

  static int64 div(int64 a, int64 b) {
    return a / b - ((a ^ b) < 0 and a % b);
  }

  bool isect(iterator x, iterator y) const {
    if (y == end()) {
      x->p = kInfinity;
      return false;
    } else if (x->m == y->m) {
      x->p = x->c > y->c ? kInfinity : -kInfinity;
    } else {
      x->p = div(y->c - x->c, x->m - y->m);
    }
    return x->p >= y->p;
  }

public:
  void add(int64 m, int64 c) {
    auto z = insert({m, c, 0});
    auto y = z++;
    auto x = y;
    while (isect(y, z)) {
      z = erase(z);
    }
    if (x != begin() and isect(--x, y)) {
      isect(x, y = erase(y));
    }
    while ((y = x) != begin() and (--x)->p >= y->p) {
      isect(x, erase(y));
    }
  }

  [[nodiscard]] int64 query(int64 x) const {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.m * x + l.c;
  }
};

inline void solution() {
  const int n = read::Int();
  const int64 c = read::Int64();

  const vector<int64> h = read::Vec<int64>(n);

  auto square = [&](const int64 x) {
    return x * x;
  };

  LineContainer cht;

  vector<int64> dp(n, kInf64);
  dp[0] = 0;
  cht.add(2 * h[0], -square(h[0]));
  for (int i = 1; i < n; i++) {
    dp[i] = cht.query(h[i]) - square(h[i]) - c;
    cht.add(2 * h[i], dp[i] - square(h[i]));
  }

  cout << -dp[n - 1] << '\n';
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