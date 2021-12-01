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
class segtree {
  const int n;
  vector<int> t;

  static int unite(const int l, const int r) {
    return l + r;
  }

  void flip(const int x, const int l, const int r, const int p) {
    if (l == r) {
      t[x] = 1 - t[x];
      return;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (p <= mid) {
      flip(x + 1, l, mid, p);
    } else {
      flip(y, mid + 1, r, p);
    }
    t[x] = unite(t[x + 1], t[y]);
  }

  int remove(const int x, const int l, const int r, const int k) {
    if (l == r) {
      flip(0, 0, n - 1, l);
      return l;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (k <= t[x + 1]) {
      return remove(x + 1, l, mid, k);
    } else {
      return remove(y, mid + 1, r, k - t[x + 1]);
    }
  }

public:
  explicit segtree(const int n) : n(n), t(2 * n - 1) {}

  void add(const int x) {
    assert(0 <= x and x < n);
    flip(0, 0, n - 1, x);
  }

  int del(const int x) {
    assert(0 <= x and x <= t[0]);
    return remove(0, 0, n - 1, x);
  }
};
}// namespace cp

void solution() {
  const int q = readInt();
  set<int> to_compress;
  map<int, int> m1, m2;
  vector<pair<int, int>> queries(q);
  for (int i = 0; i < q; i++) {
    const int type = readInt(), x = readInt();
    queries[i] = {type, x};
    if (type == 1) {
      to_compress.insert(x);
    }
  }
  for (int i = 0; not to_compress.empty(); i++) {
    const int x = *to_compress.begin();
    m1[x] = i, m2[i] = x;
    to_compress.erase(to_compress.begin());
  }
  cp::segtree st(m1.size());
  for (const auto &[t, x] : queries) {
    if (t == 1) {
      st.add(m1[x]);
    } else {
      cout << m2[st.del(x)] << '\n';
    }
  }
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