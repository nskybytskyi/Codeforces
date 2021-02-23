#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int64_t p, a, b, c;
    cin >> p >> a >> b >> c;
    auto f = [&] (int64_t x, int64_t p) -> int64_t {
      p %= x;
      if (!p) {
        return 0;
      } else {
        return x - p;
      }
    };
    cout << min({f(a, p), f(b, p), f(c, p)}) << "\n";
  }
  return 0;
}
