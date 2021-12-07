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

class segtree {
  const int n;
  vector<int> t;

  static int unite(const int l, const int r) {
    return max(l, r);
  }

  void update(const int x, const int l, const int r, const int p, const int v) {
    if (l == r) {
      t[x] = v;
      return;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (p <= mid) {
      update(x + 1, l, mid, p, v);
    } else {
      update(y, mid + 1, r, p, v);
    }
    t[x] = unite(t[x + 1], t[y]);
  }

  [[nodiscard]] int find_first(const int x, const int l, const int r, const int v) const {
    if (l == r) {
      return l;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (t[x + 1] > v) {
      return find_first(x + 1, l, mid, v);
    } else {
      return find_first(y, mid + 1, r, v);
    }
  }

  [[nodiscard]] int find_last(const int x, const int l, const int r, const int v) const {
    if (l == r) {
      return l;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (t[y] > v) {
      return find_last(y, mid + 1, r, v);
    } else {
      return find_last(x + 1, l, mid, v);
    }
  }

public:
  explicit segtree(const int n) : n(n), t(2 * n - 1) {}

  void set(const int p, const int v) {
    update(0, 0, n - 1, p, v);
  }

  [[nodiscard]] int find_first(const int v) const {
    return find_first(0, 0, n - 1, v);
  }

  [[nodiscard]] int find_last(const int v) const {
    return find_last(0, 0, n - 1, v);
  }
};

void solution() {
  const int n = readInt();
  const vector<int> &a = readVec<int>(n);
  segtree left(n + 1), right(n + 1);
  left.set(0, kInf), right.set(n, kInf);
  vector<int> ans(n);
  for (int i = 0; i < n; i++) {
    ans[i] = i - left.find_last(a[i]);
    left.set(i + 1, a[i]);
  }
  for (int i = n - 1; i >= 0; i--) {
    ans[i] += right.find_first(a[i]) - i - 1;
    right.set(i, a[i]);
  }
  for (const int x : ans) {
    cout << x << '\n';
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
