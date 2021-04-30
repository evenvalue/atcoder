#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int kMod = 1e9 + 7;

  int h, w;
  cin >> h >> w;
  vector<vector<bool>> wall(h, vector<bool>(w));
  for (vector<bool> &r : wall) {
    for (int i = 0; i < w; i++) {
      char c;
      cin >> c;
      r[i] = (c == '#');
    }
  }
  vector<vector<int>> ways(h, vector<int>(w));
  ways[0][0] = 1;
  for (int c = 1; c < w; c++) {
    if (wall[0][c]) break;
    ways[0][c] = 1;
  }
  for (int r = 1; r < h; r++) {
    if (wall[r][0]) break;
    ways[r][0] = 1;
  }
  for (int r = 1; r < h; r++) {
    for (int c = 1; c < w; c++) {
      if (wall[r][c]) continue;
      ways[r][c] = (ways[r - 1][c] + ways[r][c - 1]) % kMod;
    }
  }
  cout << ways[h - 1][w - 1] << "\n";
}