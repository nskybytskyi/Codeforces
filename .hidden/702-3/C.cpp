#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int64_t x;
    cin >> x;
    bool to_break = false;
    for (int64_t a = 1; a * a * a < x && !to_break; ++a) {
      int64_t b = cbrt(x - a * a * a);
      for (int64_t c = b - 1; c <= b + 1 && !to_break; ++c) {
        if (c >= 1 && c * c * c + a * a * a == x) {
          cout << "YES\n";
          to_break = true;
        }
      }
    }
    if (!to_break) {
      cout << "NO\n";
    }
  }
  return 0;
}
