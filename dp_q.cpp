#include <iostream>
#include <vector>
using namespace std;

#define int64 int64_t

class SegTree {
  vector<int64> t;

  static int64 unite(const int64 l, const int64 r) {
    return max(l, r);
  }

public:
  explicit SegTree(const int n) : t(2 * n - 1) {}

  void update(const int x, const int l, const int r, const int pos, const int64 upd) {
    if (l == r) {
      t[x] = upd;
      return;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (pos <= mid) {
      update(x + 1, l, mid, pos, upd);
    } else {
      update(y, mid + 1, r, pos, upd);
    }
    t[x] = unite(t[x + 1], t[y]);
  }

  int64 query(const int x, const int l, const int r, const int ql, const int qr) {
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
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  vector<int> h(n);
  vector<int> b(n);
  for (int &flower : h) {
    cin >> flower;
  }
  for (int &flower : b) {
    cin >> flower;
  }
  SegTree st(n + 1);
  for (int flower = 0; flower < n; flower++) {
    const int64 kPrev = st.query(0, 0, n, 0, h[flower] - 1);
    st.update(0, 0, n, h[flower], kPrev + b[flower]);
  }
  int64 ans = 0;
  for (int height = 1; height <= n; height++) {
    ans = max(ans, st.query(0, 0, n, height, height));
  }
  cout << ans << "\n";
}