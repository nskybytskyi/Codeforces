#include <bits/stdc++.h>
using namespace std;
// library code goes here

vector<vector<int64_t>> FloydWarshall(const vector<vector<int>>& g) {
  const int64_t kUnreachable = numeric_limits<int64_t>::max();
  int n = g.size();
  vector<vector<int64_t>> d(n, vector<int64_t>(n, kUnreachable));
  for (int i = 0; i < n; ++i)
    d[i][i] = 0;
  for (int i = 0; i < n; ++i)
    for (auto j : g[i])
      d[i][j] = 1;
  for (int k = 0; k < n; ++k)
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
  return d;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  int s, b, k, h;
  cin >> s >> b >> k >> h;
  vector<tuple<int, int, int>> xaf(s);
  for (auto& [x, a, f] : xaf) {
    cin >> x >> a >> f;
    --x;
  }
  vector<pair<int, int>> xd(b);
  for (auto& [x, d] : xd) {
    cin >> x >> d;
    --x;
  }

  auto apsp = FloydWarshall(g);
  BipartiteGraph bipartite_graph({s, b});
  for (int i = 0; i < s; ++i)
    for (int j = 0; j < b; ++j)
      if (get<1>(xaf[i]) >= get<1>(xd[j]) &&
          get<2>(xaf[i]) >= apsp[get<0>(xaf[i])][get<0>(xd[j])])
        bipartite_graph.AddEdge({i, j});
  cout << min(s * 1ll * h, Kuhn(bipartite_graph).Size() * 1ll * k) << "\n";

  return 0;
}
