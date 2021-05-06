#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int n, m, w;
  cin >> n >> m >> w;
  vector<vector<int>> a(n, vector<int>(m));
  for (auto& ai : a) {
    for (auto& aij : ai) {
      cin >> aij;
    }
  }
  if (a[0][0] == -1 || a[n - 1][m - 1] == -1) {
    cout << -1 << "\n";
  } else {
    const int64_t inf = numeric_limits<int64_t>::max();
    auto nei = [&] (int i, int j) -> vector<pair<int, int>> {
      return {{i - 1, j}, {i + 1, j}, {i, j - 1}, {i, j + 1}};
    };
    auto bfs = [&] (int sx, int sy) -> vector<vector<int64_t>> {
      vector<vector<int64_t>> d(n, vector<int64_t>(m, inf / 2));
      deque<pair<int, int>> q;
      q.emplace_back(sx, sy);
      d[sx][sy] = 0;
      while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop_front();
        for (auto [ni, nj] : nei(i, j)) {
          if (0 <= ni && ni < n && 0 <= nj && nj < m && a[ni][nj] != -1) {
            if (d[ni][nj] > d[i][j] + w) {
              d[ni][nj] = d[i][j] + w;
              q.emplace_back(ni, nj);
            }
          }
        }
      }
      return d;
    };
    auto d0 = bfs(0, 0), d1 = bfs(n - 1, m - 1);
    int64_t min0 = inf / 3, min1 = inf / 3;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (a[i][j] > 0) {
          min0 = min(min0, d0[i][j] + a[i][j]);
          min1 = min(min1, d1[i][j] + a[i][j]);
        }
      }
    }
    auto ans = min(d0[n - 1][m - 1], min0 + min1);
    if (ans > inf / 4) {
      cout << -1 << "\n";
    } else {
      cout << ans << "\n";
    }
  }
  return 0;
}