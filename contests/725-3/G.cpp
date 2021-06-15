#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t; cin >> t; while (t--) {
    int64_t x, y, a, b; cin >> x >> y >> a >> b;
    if (a == b) {
      cout << min(x, y) / a << "\n";
    } else {
      if (x < y) swap(x, y);  // wlog assume x >= y
      if (a < b) swap(a, b);  // wlog assume a >= b
      int64_t c = a + b;
      auto valid = [&] (int64_t d) -> bool {
        return 0 <= d && d <= min(x, y) / c;
      };
      int64_t maximum_d = min(x, y) / c;
      int64_t optimal_d = (a * y - b * x) / (a * c - b * c);
      const int64_t heuristic_magic = 10'000 / 4;
      auto e = [&] (int64_t d) -> int64_t {
        return min((x - d * c) / a, (y - d * c) / b);
      };
      int64_t best = 0;
      for (int64_t d = 0; d <= heuristic_magic; ++d) {
        if (valid(d)) {
          best = max(best, d * 2 + e(d));
        }
      }
      for (int64_t d = optimal_d - heuristic_magic; d <= optimal_d + heuristic_magic; ++d) {
        if (valid(d)) {
          best = max(best, d * 2 + e(d));
        }
      }
      for (int64_t d = maximum_d - heuristic_magic; d <= maximum_d; ++d) {
        if (valid(d)) {
          best = max(best, d * 2 + e(d));
        }
      }
      cout << best << "\n";
    }
  }
  return 0;
}
