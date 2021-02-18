#include <bits/stdc++.h>
using namespace std;
int cost(int a, int b) {
  int c = 0;
  while (a) {
    a /= b;
    ++c;
  }
  return c;
}
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int a, b, c = 1e9, one = 0;
    cin >> a >> b;
    if (b == 1) {
      one = 1;
      ++b;
    }
    for (int d = 0; d <= 100; ++d) {
      c = min(c, d + cost(a, b + d));
    }
    cout << c + one << "\n";
  }
  return 0;
}
