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

namespace Read {
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
}//namespace Read

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;
using mint = atcoder::static_modint<kMod>;

template <class Heap>
class PQ {
  Heap pq;
  Heap dpq;

public:
  template<typename T>
  void insert(const T x) {
    pq.push(x);
  }

  template<typename T>
  void erase(const T x) {
    dpq.push(x);
  }

  auto top() {
    while (not dpq.empty() and pq.top() == dpq.top()) {
      pq.pop();
      dpq.pop();
    }
    if (pq.empty()) assert(false);
    return pq.top();
  }

  bool empty() {
    return pq.size() == dpq.size();
  }

  size_t size() {
    return pq.size() - dpq.size();
  }
};

class SegTree {
  const int n;
  vector<PQ<max_heap<int>>> t;

  void insert(const int x, const int l, const int r, const int ql, const int qr, const int v) {
    if (ql <= l and r <= qr) {
      t[x].insert(v);
      return;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (ql <= mid) {
      insert(x + 1, l, mid, ql, qr, v);
    }
    if (mid < qr) {
      insert(y, mid + 1, r, ql, qr, v);
    }
  }

  void erase(const int x, const int l, const int r, const int ql, const int qr, const int v) {
    if (ql <= l and r <= qr) {
      t[x].erase(v);
      return;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (ql <= mid) {
      erase(x + 1, l, mid, ql, qr, v);
    }
    if (mid < qr) {
      erase(y, mid + 1, r, ql, qr, v);
    }
  }

  int query(const int x, const int l, const int r, const int p, int val = 0) {
    if (not t[x].empty()) val = max(t[x].top(), val);
    if (l == r) {
      return val;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (p <= mid) {
      return query(x + 1, l, mid, p, val);
    } else {
      return query(y, mid + 1, r, p, val);
    }
  }

public:
  explicit SegTree(const vector<int> &a) : n(a.size()), t(2 * n - 1) {
    for (int i = 0; i < n; i++) {
      insert(0, 0, n - 1, i, i, a[i]);
    }
  }

  void insert(const int l, const int r, const int x) {
    insert(0, 0, n - 1, l, r, x);
  }

  void erase(const int l, const int r, const int x) {
    erase(0, 0, n - 1, l, r, x);
  }

  int query(const int p) {
    return query(0, 0, n - 1, p);
  }
};

inline void solution() {
  const int n = Read::Int();
  const vector<int> a = Read::Vec<int>(n);

  SegTree st(a);

  struct query {
    int l;
    int r;
    int x;
  };

  vector<query> queries(Read::Int());

  for (auto &[l, r, x] : queries) {
    const int type = Read::Int();
    if (type == 1) {
      l = Read::Int() - 1;
      r = Read::Int() - 1;
      x = Read::Int();
      st.insert(l, r, x);
    } else if (type == 2) {
      const auto [ql, qr, v] = queries[Read::Int() - 1];
      st.erase(ql, qr, v);
    } else {
      cout << st.query(Read::Int() - 1) << '\n';
    }
  }
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cout << fixed << setprecision(10);

  int testcases = 1;
  //cin >> testcases;
  while (testcases--) {
    solution();
  }
}