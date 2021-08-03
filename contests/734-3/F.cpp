#include <bits/stdc++.h>
using namespace std;
const int mod = 1'000'000'007;
int main() {
  ios::sync_with_stdio(0),cin.tie(0);
  int t; cin >> t; while (t--) {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> g(n);
    for (int e = 1; e < n; ++e) {
      int u, v;
      cin >> u >> v;
      --u, --v;
      g[u].push_back(v);
      g[v].push_back(u);
    }
    int cnt = 0;
    if (k == 2) {
      cnt = (n * (n - 1)) / 2;
    } else {
      for (int r = 0; r < n; ++r) {
        vector<int> d(n, n);
        vector<int> p(n);
        d[r] = 0;
        deque<int> bfs = {r};
        while (!bfs.empty()) {
          auto v = bfs.front();
          bfs.pop_front();
          for (auto w : g[v]) {
            if (v == r) {
              p[w] = w;
            } else {
              p[w] = p[v];
            }
            if (d[w] == n) {
              d[w] = d[v] + 1;
              bfs.push_back(w);
            }
          }
        }
        map<pair<int, int>, int> pf;
        for (int i = 0; i < n; ++i) {
          ++pf[{d[i], p[i]}];
        }
        for (int l = 0; l < n; ++l) {
          vector<int> pfl;
          for (int v : g[r]) {
            pfl.push_back(pf[{l, v}]);
          }
          const int m = pfl.size();
          if (m >= k) {
            vector<vector<int>> dp(m + 1, vector<int>(m + 1));
            dp[0][0] = 1;
            for (int i = 0; i < m; ++i) {
              // skip
              for (int j = 0; j <= i; ++j) {
                dp[i + 1][j] = dp[i][j];
              }
              // take
              for (int j = 0; j <= i; ++j) {
                dp[i + 1][j + 1] += (dp[i][j] * 1ll * pfl[i]) % mod;
                dp[i + 1][j + 1] %= mod;
              }
            }
            cnt += dp[m][k];
            cnt %= mod;
          }
        }
      }
    }
    cout << cnt << "\n";
  }
  return 0;
}