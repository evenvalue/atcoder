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
constexpr int kMod = 1e9 + 7;
using mint = atcoder::static_modint<kMod>;

inline void solution() {
  const int n = read::Int();
  const int m = read::Int();

  const vector<int> c = read::Vec<int>(n);

  auto hash = [&](const int x, const int y) {
    return x * n + y;
  };

  auto unhash = [&](const int a) {
    const int x = a / n;
    const int y = a % n;
    return make_pair(x, y);
  };

  const int nodes = hash(n, n);

  vector<vector<int>> zero(nodes);
  vector<vector<int>> ones(nodes);
  for (int i = 0; i < m; i++) {
    const int x = read::Int() - 1;
    const int y = read::Int() - 1;
    (c[y] ? ones[x] : zero[x]).push_back(y);
    (c[x] ? ones[y] : zero[y]).push_back(x);
  }

  if (c[0] == c[n - 1]) {
    cout << -1 << '\n';
    return;
  }


  for (int x = 0; x < n; x++) {
    sort(zero[x].begin(), zero[x].end());
    sort(ones[x].begin(), ones[x].end());
  }

  auto check = [&](const int x, const vector<int> &foo) {
    const auto it = lower_bound(foo.begin(), foo.end(), x);
    return (it != foo.end() and *it == x);
  };

  auto bfs = [&](const int source) {
    vector<int> dist(nodes, kInf);
    queue<int> q;
    vector<int> to_push;

    dist[source] = 0;
    q.push(source);

    while (not q.empty()) {
      const auto cur = q.front();
      const auto [x, y] = unhash(cur);
      q.pop();

      const int foo1 = ones[x].size() * zero[y].size();
      const int foo2 = zero[x].size() * ones[y].size();
      const int foo = foo1 + foo2;

      for (const int u : zero[x]) {
        for (const int v : ones[y]) {
          const int other = hash(u, v);
          if (dist[other] <= dist[cur] + 1) continue;
          to_push.push_back(other);
        }
      }
      for (const int u : ones[x]) {
        for (const int v : zero[y]) {
          const int other = hash(u, v);
          if (dist[other] <= dist[cur] + 1) continue;
          to_push.push_back(other);
        }
      }

      for (const int other : to_push) {
        dist[other] = dist[cur] + 1;
        q.push(other);
      }

      to_push.clear();
    }

    return dist;
  };

  const vector<int> dist = bfs(n - 1);
  const int final = hash(n - 1, 0);

  cout << (dist[final] == kInf ? -1 : dist[final]) << '\n';
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