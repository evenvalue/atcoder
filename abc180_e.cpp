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
constexpr int kMod = 1e9 + 7;

struct coordinate {
  int64 x, y, z;
};

int64 travel_time(const coordinate &c1, const coordinate &c2) {
  return abs(c2.x - c1.x) + abs(c2.y - c1.y) + max((int64)0, c2.z - c1.z);
}

inline void solution() {
  const int n = read::Int(), max_mask = (1 << n) - 1;
  vector<coordinate> coordinates(n);
  for (coordinate &c : coordinates) {
    cin >> c.x >> c.y >> c.z;
  }

  vector<vector<int64>> dp(max_mask + 1, vector<int64>(n, kInf64));
  dp[1][0] = 0;

  for (int mask = 0; mask <= max_mask; mask++) {
    for (int this_city = 0; this_city < n; this_city++) {
      if (mask & (1 << this_city)) continue;
      const int new_mask = mask + (1 << this_city);
      for (int last_city = 0; last_city < n; last_city++) {
        if ((mask & (1 << last_city)) == 0) continue;
        dp[new_mask][this_city] = min(dp[mask][last_city] + travel_time(coordinates[last_city], coordinates[this_city]),
                                      dp[new_mask][this_city]);
      }
    }
  }

  int64 ans = kInf64;
  for (int i = 1; i < n; i++) {
    const int64 t_t = travel_time(coordinates[i], coordinates[0]);
    const int64 d_p = dp[max_mask][i];
    ans = min(ans,
              d_p + t_t);
  }
  cout << ans << '\n';
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