#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0);
  int t; cin >> t; while (t--) {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& ai : a) {
      cin >> ai;
    }
    vector<vector<int>> dp(n + 1, vector<int>(n + 1));
    for (int i = 0; i < n; ++i) {
      // keep last
      for (int j = 0; j < i; ++j) {
        dp[i + 1][j] = dp[i][j]; 
      }
      // last gets into its place
      if (i + 1 - a[i] >= 0) {
        ++dp[i + 1][i + 1 - a[i]];
      }
      // delete last
      for (int j = 0; j < i; ++j) {
        dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j]); 
      }
    }
    int j = 0;
    while (j <= n && dp[n][j] < k) {
      ++j;
    }
    if (j > n) {
      cout << -1 << "\n";
    } else {
      cout << j << "\n";
    }
  }
  return 0;
}