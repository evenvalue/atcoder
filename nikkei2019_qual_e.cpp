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
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;
using mint = atcoder::static_modint<kMod>;

class dsu {
  int n;
  std::vector<int> e;

  int pfind(const int x) {
    return (e[x] < 0 ? x : pfind(e[x]));
  }

public:
  dsu() : n(0), comp(0) {}
  explicit dsu(const int n, const vector<int64> &weights) : n(n), comp(n), e(n, -1), w(weights) {}

  int comp;
  std::vector<int64> w;

  int find(const int x) {
    assert(0 <= x and x < n);
    return pfind(x);
  }

  bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    if (e[x] > e[y]) swap(x, y);
    w[x] += w[y];
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

struct edge {
  int x;
  int y;
  int cost;

  bool operator<(const edge &other) const {
    return cost < other.cost;
  }
};

template<typename T>
void concatenate(vector<T> &x, const vector<T> &y) {
  for (const auto &a : y) {
    x.push_back(a);
  }
}

inline void solution() {
  const int n = read::Int(), m = read::Int();
  vector<int64> weights = read::Vec<int64>(n);
  vector<edge> edges(m);
  for (auto &e : edges) {
    e.x = read::Int() - 1;
    e.y = read::Int() - 1;
    e.cost = read::Int();
  }
  sort(edges.begin(), edges.end());
  dsu d(n, weights);
  vector<vector<edge>> rem(n);
  for (edge &e : edges) {
    e.x = d.find(e.x);
    e.y = d.find(e.y);
    d.unite(e.x, e.y);
    const int leader = d.find(e.x);
    if (d.w[leader] < e.cost) {
      if (e.x != e.y) concatenate(rem[leader], rem[leader ^ e.x ^ e.y]);
      rem[leader].push_back(e);
    } else {
      rem[e.x].clear();
      rem[e.y].clear();
    }
  }
  cout << rem[d.find(0)].size() << '\n';
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