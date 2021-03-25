#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int64_t x, y;
    cin >> x >> y;
    // q = a / b = a % b = r
    // a = q * b + r
    // a = r * b + r
    // 0 < r < b
    // r * b + r <= x
    // r * (b + 1) <= x
    // b + 1 <= x / r
    // b <= x / r - 1
    // b <= y
    int64_t c = 0;
    for (int64_t r = 1; r * r + r <= x; ++r) {
      int64_t min_b = r + 1;
      int64_t max_b = min(y, x / r - 1);
      int64_t b_count = max(0ll, max_b - min_b + 1);
      c += b_count;
      if (!b_count) {
        break;
      }
    }
    cout << c << "\n"; 
  }
  return 0;
}
