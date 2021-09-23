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
  string alpha;
  cin >> alpha;
  map<char, int> dist;
  for (int i = 0; i < 26; i++) dist[alpha[i]] = i;
  int n;
  cin >> n;
  vector<string> v(n);
  for (string &s : v) cin >> s;
  sort(v.begin(), v.end(), [&](const string &s1, const string &s2) {
    const int n = min(s1.size(), s2.size());
    for (int i = 0; i < n; i++) {
      if (s1[i] == s2[i]) continue;
      return dist[s1[i]] < dist[s2[i]];
    }
    return s1.size() < s2.size();
  });
  for (const string &s : v) {
    cout << s << '\n';
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