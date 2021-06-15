#include <bits/stdc++.h>
using namespace std;
// library code goes here

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    g[a].push_back(b);
  }

  int minimum = numeric_limits<int>::max();
  for (int center = 0; center < n; ++center) {
    BipartiteGraph bipartite_graph({n, n});
    int around_center = g[center].size();
    for (int i = 0; i < n; ++i)
      if (i != center)
        for (auto j : g[i])
          if (j != center)
            bipartite_graph.AddEdge({i, j});
          else
            ++around_center;
    minimum = min(minimum, 3 * n + m - 2 * (around_center + Kuhn(bipartite_graph).Size() + 1));
  }
  cout << minimum << "\n";

  return 0;
}
