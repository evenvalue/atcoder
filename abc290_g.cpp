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
constexpr int64 kInf64 = 4e18 + 10;
constexpr int kMod = 1e9 + 7;
using mint = atcoder::static_modint<kMod>;

inline void solution() {
  const int d = read::Int();
  const int64 k = read::Int64();
  const int64 x = read::Int64();

  vector<int64> nodes(d + 2);
  for (int depth = d; depth >= 0; depth--) {
    nodes[depth] = k * nodes[depth + 1] + 1;
  }

  function<int64(int, int64)> calc_cuts = [&](const int depth, const int64 req) {
    if (nodes[depth] == req) return 0LL;
    const int64 remove = nodes[depth] - req;
    const int64 need_to_cut = nodes[depth + 1] - (remove % nodes[depth + 1]);
    const int64 cuts = calc_cuts(depth + 1, need_to_cut) + (remove / nodes[depth + 1]);
    return cuts;
  };

  int64 ans = kInf64;
  for (int depth = d; depth >= 0; depth--) {
    if (nodes[depth] < x) continue;
    ans = min(ans, calc_cuts(depth, x) + (depth != 0));
  }

  cout << ans << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cout << fixed << setprecision(10);

  int testcases = 1;
  cin >> testcases;
  while (testcases--) {
    solution();
  }
}