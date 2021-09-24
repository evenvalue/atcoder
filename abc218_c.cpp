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

struct point {
  int x{}, y{};

  explicit point() = default;
  explicit point(const int x, const int y) : x(x), y(y) {}

  point up() const {
    return *this + point(0, 1);
  }

  point down() const {
    return *this + point(0, -1);
  }

  point left() const {
    return *this + point(-1, 0);
  }

  point right() const {
    return *this + point(1, 0);
  }

  point clockwise90() const {
    return point(y, -x);
  }

  point anticlockwise90() const {
    return point(-y, x);
  }

  point operator+(const point &other) const {
    return point(x + other.x, y + other.y);
  }

  point& operator+=(const point &other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  point operator-(const point &other) const {
    return point(x - other.x, y - other.y);
  }

  point& operator-=(const point &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  bool operator<(const point &other) const {
    return (x != other.x ? x < other.x : y < other.y);
  }

  bool operator==(const point &other) const {
    return (x == other.x and y == other.y);
  }

  bool operator!=(const point &other) const {
    return not (*this == other);
  }
};

void rotate(vector<string> &mat) {
  const int n = mat.size();
  vector<string> rotate(n, string(n, '.'));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      rotate[j][n - i - 1] = mat[i][j];
    }
  }
  mat = rotate;
}

bool check(const vector<string> &s, const vector<string> &t) {
  const int n = s.size();
  point s_tr, t_tr;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (s[i][j] == '#') {
        s_tr = point(i, j);
        break;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (t[i][j] == '#') {
        t_tr = point(i, j);
        break;
      }
    }
  }
  const point diff = t_tr - s_tr;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (s[i][j] == '#') {
        point pos = point(i, j) + diff;
        if (pos.x < 0 or pos.x >= n or pos.y < 0 or pos.y >= n) return false;
        if (t[pos.x][pos.y] != '#') return false;
      }
    }
  }
  return true;
}

void solve(const int TestCase) {
  int n;
  cin >> n;
  vector<string> a(n), b(n);
  for (string &s : a) cin >> s;
  for (string &s : b) cin >> s;
  int a_cnt = 0, b_cnt = 0;
  for (string &s : a) a_cnt += count(s.begin(), s.end(), '#');
  for (string &s : b) b_cnt += count(s.begin(), s.end(), '#');
  if (a_cnt != b_cnt) {
    cout << "No" << '\n';
    return;
  }
  bool ans = false;
  for (int i = 0; i < 4; i++) {
    ans |= check(a, b);
    rotate(a);
  }
  cout << (ans ? "Yes" : "No") << '\n';
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