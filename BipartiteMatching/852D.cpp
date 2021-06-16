#include <bits/stdc++.h>
using namespace std;
// library code goes here

template <typename T>
T BinarySearch(T lower_bound, T upper_bound, std::function<bool(T)> unary_predicate, T precision = 1) {
  while (lower_bound + precision < upper_bound) {
    T middle = lower_bound + (upper_bound - lower_bound) / 2;
    if (unary_predicate(middle)) {
      lower_bound = middle;
    } else {
      upper_bound = middle;
    }
  }
  return lower_bound;
}

vector<vector<int64_t>> FloydWarshall(const vector<vector<pair<int, int>>>& g) {
  const int64_t kUnreachable = numeric_limits<int64_t>::max();
  int n = g.size();
  vector<vector<int64_t>> d(n, vector<int64_t>(n, kUnreachable));
  for (int i = 0; i < n; ++i)
    d[i][i] = 0;
  for (int i = 0; i < n; ++i)
    for (auto [j, k] : g[i])
      d[i][j] = min(d[i][j], (int64_t)k);
  for (int k = 0; k < n; ++k)
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        if (d[i][k] < kUnreachable && d[k][j] < kUnreachable)
          d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
  return d;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

  int v, e, n, k;
  cin >> v >> e >> n >> k;
  vector<int> s(n);
  for (auto& si : s) {
    cin >> si;
    --si;
  }
  vector<vector<pair<int, int>>> g(v);
  for (int i = 0; i < e; ++i) {
    int a, b, t;
    cin >> a >> b >> t;
    --a, --b;
    g[a].emplace_back(b, t);
    g[b].emplace_back(a, t);
  }

  auto apsp = FloydWarshall(g);

  int lo = -1, hi = 1'731'312;
  auto cannot = [&] (int mi) -> bool {
    BipartiteGraph bipartite_graph({n, v});
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < v; ++j)
        if (apsp[s[i]][j] <= mi)
          bipartite_graph.AddEdge({i, j});
    return Kuhn(bipartite_graph).Size() < k;
  };

  if (cannot(hi))
    cout << -1 << "\n";
  else
    cout << BinarySearch<int>(lo, hi, cannot) + 1 << "\n";

  return 0;
}
