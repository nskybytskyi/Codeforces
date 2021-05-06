#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int64_t n, m, w;
  cin >> n >> m >> w;
  auto id = [&] (int64_t i, int64_t j) -> int64_t {
    return m * i + j;
  };
  auto rc = [&] (int64_t v) -> pair<int64_t, int64_t> {
    return {v / m, v % m};
  };
  vector<vector<int64_t>> a(n, vector<int64_t>(m));
  for (auto& row : a) {
    for (auto& val : row) {
      cin >> val;
    }
  }
  if (a[0][0] == -1) {
    cout << -1 << "\n";
    return 0;
  }
  vector<pair<int64_t, int64_t>> p;
  for (int64_t r = 0; r < n; ++r) {
    for (int64_t c = 0; c < m; ++c) {
      if (a[r][c] > 0) {
        p.emplace_back(id(r, c), a[r][c]);
      }
    }
  }
  vector<pair<int64_t, int64_t>> drc = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  const int64_t inf = numeric_limits<int64_t>::max();
  vector<int64_t> d(n * m + 1, inf);
  d[id(0, 0)] = 0;
  priority_queue<pair<int64_t, int64_t>, vector<pair<int64_t, int64_t>>, greater<>> dijkstra;
  dijkstra.emplace(0, id(0, 0));
  const auto z = n * m;
  while (!dijkstra.empty()) {
    auto [dv, v] = dijkstra.top();
    dijkstra.pop();
    if (v == id(n - 1, m - 1)) {
      break;
    }
    if (d[v] == dv) {
      // cout << "v = " << v << ", d[v] = " << d[v] << "\n";
      if (v == z) {
        for (auto [nei, c] : p) {
          if (c + dv < d[nei]) {
            d[nei] = c + dv;
            dijkstra.emplace(d[nei], nei);
          }
        }
      } else {
        auto [r, c] = rc(v);
        // cout << "v = " << v << ", r = " << r << ", c = " << c << "\n";
        if (a[r][c] > 0) {
          if (a[r][c] + dv < d[z]) {
            d[z] = a[r][c] + dv;
            dijkstra.emplace(d[z], z);
          }
        }
        for (auto [dr, dc] : drc) {
          if (0 <= r + dr && r + dr < n &&
              0 <= c + dc && c + dc < m &&
              a[r + dr][c + dc] != -1) {
            // cout << "nr = " << r + dr << ", nc = " << c + dc << "\n";
            const int64_t nei = id(r + dr, c + dc);
            if (w + dv < d[nei]) {
              d[nei] = w + dv;
              dijkstra.emplace(d[nei], nei);
            }
          }
        }
      }
    }
  }
  if (d[id(n - 1, m - 1)] != inf) {
    cout << d[id(n - 1, m - 1)] << "\n";
  } else {
    cout << -1 << "\n";
  }
  return 0;
}