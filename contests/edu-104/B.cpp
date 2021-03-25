#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

  int t;
  cin >> t;
  while (t--) {
    int64_t n, k;
    cin >> n >> k;

    if (n & 1) {  // odd
      --k;
      int64_t m = n >> 1;
      auto [q, r] = div(k, m);
      k = q * (m + 1) + r;
      ++k;
    }

    k %= n;
    if (!k) {
      k = n;
    }
    cout << k << "\n";
  }

  return 0;
}
