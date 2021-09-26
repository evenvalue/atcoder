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
#include <vector>
using namespace std;

#define debug(x) cerr << #x << ": " << x << '\n'
using int64 = int64_t;

const int64 kInfL = 1e15 + 10;
const int kInf = 1e9 + 10;
const int kMod = 1e9 + 7;

ifstream fin("input.txt");
ofstream fout("output.txt");

class dsu {
  const int n;
  vector<int> e;
  int comp = 0;

  int pri_find(const int x) {
    return e[x] < 0 ? x : (e[x] = find(e[x]));
  }

public:
  explicit dsu(const int n) : n(n), e(n, -1), comp(n) {}

  int find(const int x) {
    assert(0 <= x and x < n);
    return pri_find(x);
  }

  bool unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return false;
    if (e[x] > e[y]) swap(x, y);
    e[x] += e[y];
    e[y] = x;
    comp--;
    return true;
  }

  bool same(int x, int y) {
    return (find(x) == find(y));
  }

  int size(const int x) {
    return -e[find(x)];
  }

  int operator[](const int x) {
    assert(0 <= x and x < n);
    return e[x];
  }
};

void solve(const int TestCase) {
  int n, q;
  cin >> n >> q;
  dsu d(n);
  while (q--) {
    int type, x, y;
    cin >> type >> x >> y;
    if (type == 0) {
      d.unite(x, y);
    } else {
      cout << (int)d.same(x, y) << '\n';
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