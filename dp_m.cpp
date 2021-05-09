#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int kMod = 1e9 + 7;

  int n, k;
  cin >> n >> k;
  vector<int> ways(k + 1);
  vector<int> pref(k + 1);
  int upto;
  cin >> upto;
  fill(ways.begin(), ways.begin() + upto + 1, 1);
  for (int child = 1; child < n; child++) {
    pref[0] = ways[0];
    for (int candy = 1; candy <= k; candy++) {
      pref[candy] = (pref[candy - 1] + ways[candy]);
      pref[candy] -= (pref[candy] > kMod ? kMod : 0);
    }
    cin >> upto;
    for (int candy = 0; candy <= upto; candy++) {
      ways[candy] = pref[candy];
    }
    for (int candy = upto + 1; candy <= k; candy++) {
      ways[candy] = pref[candy] - pref[candy - upto - 1];
      ways[candy] += (ways[candy] < 0 ? kMod : 0);
    }
  }
  cout << ways[k] << "\n";
}