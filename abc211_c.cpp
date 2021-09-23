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

void solve(const int TestCase) {
  map<int, char> m;
  string chokudai = "-chokudai";
  for (int i = 1; i <= 8; i++) {
    m[i] = chokudai[i];
  }
  string s;
  cin >> s;
  const int n = s.size();
  s = "-" + s;
  vector<vector<int>> ways(n + 1, vector<int>(9));
  for (int i = 0; i <= n; i++) ways[i][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= 8; j++) {
      ways[i][j] = ways[i - 1][j];
      if (s[i] == chokudai[j]) {
        ways[i][j] += ways[i - 1][j - 1];
        ways[i][j] -= (ways[i][j] > kMod ? kMod : 0);
      }
    }
  }
  cout << ways[n][8] << '\n';
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