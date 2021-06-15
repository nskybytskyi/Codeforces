#include <bits/stdc++.h>
using namespace std;
int64_t weight(vector<int>& a, int l, int r) {
  int64_t ans = 0;
  for (int i = l; i <= r; ++i) {
    for (int j = i + 1; j <= r; ++j) {
      if (a[i] == a[j]) {
        ++ans;
      }
    }
  }
  return ans;
}
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
    int64_t ans = 0;
    for (int l = 0; l < n; ++l) {
      for (int r = l + 1; r < n; ++r) {
        ans += weight(a, l, r);
      }
    }
    cout << ans << "\n";
  }
  return 0;
}
