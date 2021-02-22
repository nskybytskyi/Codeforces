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
    for (auto& ai : a)
      cin >> ai;
    map<int, int> f;
    for (auto ai : a)
      ++f[ai];
    set<int> v;
    for (auto [_, vi] : f)
      v.insert(vi);
    int ans = n;
    for (auto vi : v) {
      int curr = 0;
      for (auto [kj, vj] : f) {
        if (vj >= vi)
          curr += vj - vi;
        else
          curr += vj;
      }
      ans = min(ans, curr);
    }
    cout << ans << "\n";
  }
  return 0;
}
