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
  struct node {
    int64 val = kInf64;
    int64 lazy = kInf64;
  };

  const int n;
  vector<node> t;

  static node unite(const node &l, const node &r) {
    node ret = {min(l.val, r.val), kInf64};
    return ret;
  }

  void push(const int x, const int l, const int r) {
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;

    //left child
    t[x + 1].val = min(t[x + 1].val, t[x].lazy);
    t[x + 1].lazy = min(t[x + 1].lazy, t[x].lazy);

    //right child
    t[y].val = min(t[y].val, t[x].lazy);
    t[y].lazy = min(t[y].lazy, t[x].lazy);
  }

  void update(const int x, const int l, const int r, const int ql, const int qr, const int64 v) {
    if (ql <= l and r <= qr) {
      t[x].val = min(t[x].val, v);
      t[x].lazy = min(t[x].lazy, v);
      return;
    }
    push(x, l, r);
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (ql <= mid) {
      update(x + 1, l, mid, ql, qr, v);
    }
    if (mid < qr) {
      update(y, mid + 1, r, ql, qr, v);
    }
    t[x] = unite(t[x + 1], t[y]);
  }

  node query(const int x, const int l, const int r, const int pos) {
    if (l == r) {
      return t[x];
    }
    push(x, l, r);
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (pos <= mid) {
      return query(x + 1, l, mid, pos);
    } else {
      return query(y, mid + 1, r, pos);
    }
  }

public:
  explicit segtree(const int n) : n(n), t(2 * n - 1) {
    set(0, 0, 0);
  }

  void set(const int l, const int r, const int64 v) {
    update(0, 0, n - 1, l, r, v);
  }

  int64 get(const int pos) {
    return query(0, 0, n - 1, pos).val;
  }
};
} //namespace cp

void solution() {
  const int n = readInt(), m = readInt();
  vector<vector<pair<int, int>>> start(n);
  for (int i = 0; i < m; i++) {
    const int l = readInt() - 1, r = readInt() - 1, w = readInt();
    start[l].push_back({r, w});
  }
  cp::segtree st(n);
  for (int l = 0; l < n; l++) {
    const int64 ans_l = st.get(l);
    for (const auto &[r, w] : start[l]) {
      st.set(l, r, ans_l + w);
    }
  }
  const int64 ans = st.get(n - 1);
  cout << (ans == kInf64 ? -1 : ans) << '\n';
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