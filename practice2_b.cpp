#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;

#define debug(x) cerr << #x << ": " << x << '\n'
using int64 = int64_t;

const int64 kInfL = 1e15 + 10;
const int kInf = 1e9 + 10;
const int kMod = 1e9 + 7;

ifstream fin("input.txt");
ofstream fout("output.txt");

//Takes a monoid as a template.
template<typename T, T e, class F = function<T(const T &, const T &)>>
class SegTree {
  vector<T> t;
  const F unite;
  const int n;

  void build(const int x, const int l, const int r, const vector<T> &a) {
    if (l == r) {
      t[x] = a[l];
      return;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    build(x + 1, l, mid, a);
    build(y, mid + 1, r, a);
    t[x] = unite(t[x + 1], t[y]);
  }

  void update(const int x, const int l, const int r, const int pos, const T &val) {
    if (l == r) {
      t[x] = val;
      return;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (pos <= mid) {
      update(x + 1, l, mid, pos, val);
    } else {
      update(y, mid + 1, r, pos, val);
    }
    t[x] = unite(t[x + 1], t[y]);
  }

  T query(const int x, const int l, const int r, const int ql, const int qr) {
    if (ql <= l and r <= qr) {
      return t[x];
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (qr <= mid) {
      return query(x + 1, l, mid, ql, qr);
    } else if (mid < ql) {
      return query(y, mid + 1, r, ql, qr);
    } else {
      return unite(query(x + 1, l, mid, ql, qr), query(y, mid + 1, r, ql, qr));
    }
  }

  int find_first(const int x, const int l, const int r, const function<bool(T &)> &f) {
    if (l == r) {
      return l;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (f(t[x + 1])) {
      return find_first(x + 1, l, mid, f);
    } else {
      return find_first(y, mid + 1, r, f);
    }
  }

  int find_last(const int x, const int l, const int r, const function<bool(T &)> &f) {
    if (l == r) {
      return l;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (not f(t[y])) {
      return find_last(x + 1, l, mid, f);
    } else {
      return find_last(y, mid + 1, r, f);
    }
  }

public:
  [[maybe_unused]] explicit SegTree(const int n, F f) : t(2 * n - 1, e), n(n), unite(move(f)) {}
  [[maybe_unused]] explicit SegTree(const vector<T> &a, F f) : n(static_cast<int>(a.size())), unite(move(f)) {
    t.resize(2 * n - 1);
    build(0, 0, n - 1, a);
  }

  //Updates the value of a[pos] to val.
  //Complexity: O(log2 n)
  void set(const int pos, const T &val) {
    assert(0 <= pos and pos < n);
    update(0, 0, n - 1, pos, val);
  }

  //Finds unite(a[ql], a[ql + 1], ... , q[qr]).
  //Complexity: O(log2 n)
  T get(const int ql, const int qr) {
    assert(0 <= ql and ql <= qr and qr < n);
    return query(0, 0, n - 1, ql, qr);
  }

  //Finds the first i such that (0 <= i and i < n) and f(a[i]) returns true. If none, returns -1.
  //Complexity: O(log2 n)
  int first(const function<bool(T &)> f) {
    if (not f(t[0])) return -1;
    return find_first(0, 0, n - 1, f);
  }

  //Finds the last i such that (0 <= i and i < n) and f(a[i]) returns true. If none, returns -1.
  //Complexity: O(log2 n)
  int last(const function<bool(T &)> f) {
    if (not f(t[0])) return -1;
    return find_last(0, 0, n - 1, f);
  }
};

void solve(const int TestCase) {
  int n, q;
  cin >> n >> q;
  vector<int64> a(n);
  for (int64 &x : a) cin >> x;
  SegTree<int64, 0> st(a, [](const int64 l, const int64 r) {
    return l + r;
  });
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      int p, x;
      cin >> p >> x;
      st.set(p, st.get(p, p) + x);
    } else {
      int l, r;
      cin >> l >> r;
      cout << st.get(l, r - 1) << '\n';
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const auto begin = std::chrono::high_resolution_clock::now();

  int t = 1;
  //cin >> t;
  for (int tc = 1; tc <= t; tc++) {
    solve(tc);
  }

  const auto end = std::chrono::high_resolution_clock::now();
  const auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
  cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n";
}