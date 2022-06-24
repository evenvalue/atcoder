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

using int64 = long long;
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
constexpr int kMod = 1e9 + 7;

struct key {
  int cost = 0;
  int unlock = 0;
};

inline void solution() {
  const int n = read::Int(), m = read::Int(), max_mask = (1 << n) - 1;
  vector<key> keys(m + 1);
  for (int i = 1; i <= m; i++) {
    const int a = read::Int(), b = read::Int();
    for (int j = 0; j < b; j++) {
      const int lock = read::Int() - 1;
      keys[i].unlock += (1 << lock);
    }
    keys[i].cost = a;
  }

  vector<vector<int>> dp(max_mask + 1, vector<int>(m + 1, kInf));
  vector<int> cheapest(max_mask + 1, kInf);

  dp[0][0] = 0;
  cheapest[0] = 0;

  for (int mask = 0; mask <= max_mask; mask++) {
    for (int i = 1; i <= m; i++) {
      dp[mask][i] = cheapest[mask & (~keys[i].unlock)] + keys[i].cost;
      cheapest[mask] = min(cheapest[mask], dp[mask][i]);
    }
  }

  cout << (cheapest[max_mask] == kInf ? -1 : cheapest[max_mask]) << '\n';
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