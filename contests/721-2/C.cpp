#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& ai : a) {
      cin >> ai;
    }
    map<int, vector<int>> pos;
    for (int i = 0; i < n; ++i) {
      pos[a[i]].push_back(i);
    }
    int64_t ans = 0;
    for (auto& [k, v] : pos) {
      int m = v.size();
      vector<int64_t> ss(m + 1);
      for (int i = m - 1; i >= 0; --i) {
        ss[i] = ss[i + 1] + n - v[i];
      }
      for (int i = 0; i < m; ++i) {
        ans += (v[i] + 1) * ss[i + 1];
      }
    }
    cout << ans << "\n";
  }
  return 0;
}
