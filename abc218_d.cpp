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

  bool operator<(const point &other) const {
    return (x != other.x ? x < other.x : y < other.y);
  }

  point operator+(const point &other) const {
    return point(x + other.x, y + other.y);
  }

  point& operator+=(const point &other) {
    x += other.x;
    y += other.y;
    return *this;
  }

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

  bool operator==(const point &other) const {
    return (x == other.x and y == other.y);
  }
};

void solve(const int TestCase) {
  int n;
  cin >> n;
  vector<point> points(n);
  for (point &p : points) {
    cin >> p.x >> p.y;
  }
  points.emplace_back(1e9 + 1, 1e9 + 1);
  sort(points.begin(), points.end());
  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (points[i].x == points[j].x or points[i].y == points[j].y) continue;
      const point c1 = *lower_bound(points.begin(), points.end(), point(points[i].x, points[j].y));
      const point c2 = *lower_bound(points.begin(), points.end(), point(points[j].x, points[i].y));
      ans += (c1 == point(points[i].x, points[j].y) and c2 == point(points[j].x, points[i].y));
    }
  }
  cout << ans / 2 << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  auto begin = std::chrono::high_resolution_clock::now();

  int t = 1;
  //cin >> t;
  for (int tc = 1; tc <= t; tc++) {
    solve(tc);
  }

  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
  cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n";
}