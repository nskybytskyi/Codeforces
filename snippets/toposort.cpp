vector<int> toposort(vector<vector<int>> g) {
  const int n = g.size();
 
  deque<int> bfs;
  vector<int> deg(n);
  vector<vector<int>> rg(n);
 
  for (int u = 0; u < n; ++u) {
    deg[u] = g[u].size();
    if (!deg[u]) {
      bfs.push_back(u);
    }
    for (auto v : g[u]) {
      rg[v].push_back(u);
    }
  }
 
  vector<int> order;
  while (!bfs.empty()) {
    auto v = bfs.front();
    bfs.pop_front();
    order.push_back(v);
 
    for (auto u : rg[v]) {
      --deg[u];
      if (!deg[u]) {
        bfs.push_back(u);
      }
    }
  }
 
  return order;
}
