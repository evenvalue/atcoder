#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

using int64 = int64_t;
using ld = long double;

[[maybe_unused]] int readInt() {
  int x;
  cin >> x;
  return x;
}
[[maybe_unused]] int64 readInt64() {
  int64 x;
  cin >> x;
  return x;
}
[[maybe_unused]] string readString() {
  string s;
  cin >> s;
  return s;
}
[[maybe_unused]] double readDouble() {
  return stod(readString());
}
[[maybe_unused]] ld readLongDouble() {
  return stold(readString());
}
template<typename T1, typename T2>
[[maybe_unused]] pair<T1, T2> readPair() {
  pair<T1, T2> p;
  cin >> p.first >> p.second;
  return p;
}
template<typename T>
[[maybe_unused]] vector<T> readVec(const int sz) {
  vector<T> v(sz);
  for (T &x : v) {
    cin >> x;
  }
  return v;
}
template<typename T>
[[maybe_unused]] vector<vector<T>> readVecVec(const int n, const int m) {
  vector<vector<T>> a(n);
  for (vector<T> &v : a) {
    v = readVec<T>(m);
  }
  return a;
}

const int64 kInf64 = 2e18 + 10;
const int kInf = 1e9 + 10;
const int kMod = 1e9 + 7;

namespace cp {
class dsu {
  int n;
  std::vector<int> e;

  int find_leader(const int x) {
    return (e[x] < 0 ? x : e[x] = find_leader(e[x]));
  }

public:
  int comp;

  explicit dsu(const int n = 0) : n(n), comp(n), e(n, -1) {}

  int find(const int x) {
    assert(0 <= x and x < n);
    return find_leader(x);
  }

  int unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return x;
    if (-e[x] < -e[y]) std::swap(x, y);
    e[x] += e[y];
    e[y] = x;
    comp--;
    return x;
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
      res[find_leader(x)].push_back(x);
    }
    res.erase(
        std::remove_if(res.begin(), res.end(), [&](const std::vector<int> &v) { return v.empty(); }),
        res.end());
    return res;
  }
};
}// namespace cp

struct edge {
  int x, y, w;

  bool operator<(const edge &other) const {
    return w < other.w;
  }
};

void solution() {
  const int n = readInt(), m = readInt();
  vector<edge> edges(m);
  for (edge &e : edges) {
    e.x = readInt() - 1, e.y = readInt() - 1, e.w = readInt();
  }
  sort(edges.begin(), edges.end());
  cp::dsu d(n);
  int64 reward = 0;
  for (const auto &[x, y, w] : edges) {
    if (d.same(x, y)) {
      reward += max(0, w);
    } else {
      d.unite(x, y);
    }
  }
  cout << reward << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const auto begin = std::chrono::high_resolution_clock::now();

  //  freopen(".in", "r", stdin);
  //  freopen(".out", "w", stdout);

  int t = 1;
  //cin >> t;
  for (int tc = 1; tc <= t; tc++) {
    solution();
  }

  const auto end = std::chrono::high_resolution_clock::now();
  const auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
  cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n";
}