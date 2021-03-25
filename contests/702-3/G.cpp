#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    vector<int64_t> a(n);
    for (auto& ai : a) {
      cin >> ai;
    }
    vector<pair<int64_t, int>> ps = {{0, 0}};
    int64_t cs = 0;
    for (int i = 0; i < n; ++i) {
      cs += a[i];
      if (cs > ps.back().first) {
        ps.emplace_back(cs, i + 1);
      }
    }
    int64_t mps = ps.back().first;
    while (m--) {
      int64_t x, p = 0, q = 0;
      cin >> x;
      x -= mps;
      if (x > 0) {
        if (cs <= 0) {
          cout << "-1 ";
          continue;
        } else {
          p = (x + cs - 1) / cs;
          q = p * n;
          x -= p * cs;
        }
      }
      x += mps;
      auto it = lower_bound(ps.begin(), ps.end(), make_pair(x, -1));
      cout << it->second + q - 1 << " ";
    }
    cout << "\n";
  }
  return 0;
}
