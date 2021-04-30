#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  struct day {
    int a, b, c;
  };

  int n;
  cin >> n;
  vector<day> hobby(n);
  for (day &today : hobby) {
    cin >> today.a >> today.b >> today.c;
  }
  vector<day> happy(n);
  happy[0] = hobby[0];
  for (int today = 1; today < n; today++) {
    happy[today].a = hobby[today].a + max(happy[today - 1].b, happy[today - 1].c);
    happy[today].b = hobby[today].b + max(happy[today - 1].c, happy[today - 1].a);
    happy[today].c = hobby[today].c + max(happy[today - 1].a, happy[today - 1].b);
  }
  cout << max({happy[n - 1].a, happy[n - 1].b, happy[n - 1].c}) << "\n";
}