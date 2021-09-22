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

struct lunch_box {
  int takoyaki;
  int taiyaki;
};

void solve(const int TestCase) {
  int n, x, y;
  cin >> n >> x >> y;
  vector<lunch_box> boxes(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> boxes[i].takoyaki >> boxes[i].taiyaki;
  }
  vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(x + 1, vector<int>(y + 1, kInf)));
  dp[0][0][0] = 0;
  for (int i = 1; i <= n; i++) {
    for (int tako = 0; tako <= x; tako++) {
      for (int tai = 0; tai <= y; tai++) {
        dp[i][tako][tai] = min(dp[i - 1][tako][tai],
                               dp[i - 1][max(0, tako - boxes[i].takoyaki)][max(0, tai - boxes[i].taiyaki)] + 1);
      }
    }
  }
  cout << (dp[n][x][y] == kInf ? -1 : dp[n][x][y]) << '\n';

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