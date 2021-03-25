#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

  int t;
  cin >> t;
  while (t--) {
    int64_t n, m, x;
    cin >> n >> m >> x;
    auto [c, r] = div(x - 1, n);
    cout << r * m + c + 1 << "\n";
  }

  return 0;
}
