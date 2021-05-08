#include <iostream>
#include <vector>
using namespace std;

#define int64 int64_t

const int kMod = 1e9 + 7;

struct matrix {
  int n;
  vector<vector<int>> a;

  explicit matrix(const int n) : n(n), a(n, vector<int>(n)) {}

  matrix operator*(const matrix &other) const {
    matrix ret(n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
          ret.a[i][k] = (ret.a[i][k] + ((int64) a[i][j] * other.a[j][k])) % kMod;
        }
      }
    }
    return ret;
  }
};

matrix binpow(const int n, matrix &m, int64 pow) {
  matrix product(n);
  for (int i = 0; i < n; i++) {
    product.a[i][i] = 1;
  }
  while (pow) {
    if (pow & 1) {
      product = product * m;
    }
    m = m * m;
    pow /= 2;
  }
  return product;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  int64 k;
  cin >> n >> k;
  matrix adj(n);
  for (auto &x : adj.a) {
    for (int &y : x) {
      cin >> y;
    }
  }
  const matrix mat = binpow(n, adj, k);
  int ans = 0;
  for (const auto &x : mat.a) {
    for (const int y : x) {
      ans += y;
      ans -= (ans > kMod ? kMod : 0);
    }
  }
  cout << ans << "\n";
}