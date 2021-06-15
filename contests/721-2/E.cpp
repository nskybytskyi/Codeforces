#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for (auto& ai : a) {
    cin >> ai;
    --ai;
  }
  const int64_t kInfinity = numeric_limits<int64_t>::max();
  vector<vector<int64_t>> dp(n + 1, vector<int64_t>(k + 1, kInfinity));
  dp[0][0] = 0;
  for (int r = 0; r < n; ++r) {
    vector<int> p(n, -1);
    int64_t cost = 0;
    for (int l = r; l >= 0; --l) {
      if (p[a[l]] != -1) {
        cost += p[a[l]] - l;
      }
      p[a[l]] = l;
      for (int i = 0; i < k; ++i) {
        if (dp[l][i] < kInfinity && dp[r][i + 1] > dp[l][i] + cost) {
          dp[r + 1][i + 1] = dp[l][i] + cost;
        }
      }
    }
  }
  cout << dp[n][k] << "\n";
  return 0;
}
