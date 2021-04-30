#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  vector<vector<int>> hobby(n, vector<int>(3));
  for (int day = 0; day < n; day++) {
    cin >> hobby[day][0] >> hobby[day][1] >> hobby[day][2];
  }
  vector<vector<int>> happy(n, vector<int>(3));
  happy[0] = hobby[0];
  for (int day = 1; day < n; day++) {
    for (int task = 0; task < 3; task++) {
      const int next = (task + 1) % 3;
      const int prev = (task + 2) % 3;
      happy[day][task] = hobby[day][task] + max(happy[day - 1][next], happy[day - 1][prev]);
    }
  }
  cout << *max_element(happy[n - 1].begin(), happy[n - 1].end()) << "\n";
}