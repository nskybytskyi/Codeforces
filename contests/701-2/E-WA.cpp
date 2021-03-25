#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int64_t t;
  cin >> t;
  while (t--) {
    int64_t n;
    cin >> n;
    vector<vector<int64_t>> graph(n);
    for (int64_t i = 1; i < n; ++i) {
      int64_t vi;
      cin >> vi;
      --vi;
      graph[i].push_back(vi);
      graph[vi].push_back(i);
    }
    vector<vector<int64_t>> groups(n), tree(n);
    vector<int64_t> dist(n, -1), parent(n);
    dist[0] = 0;
    function<void(int64_t)> dfs = [&] (int64_t v) -> void {
      groups[dist[v]].push_back(v);
      for (auto w : graph[v]) {
        if (dist[w] == -1) {
          tree[v].push_back(w);
          parent[w] = v;
          dist[w] = dist[v] + 1;
          dfs(w);
        }
      }
    };
    dfs(0);
    vector<int64_t> a(n);
    for (int64_t i = 1; i < n; ++i) {
      cin >> a[i];
    }
    vector<int64_t> dp(n);
    int64_t prev_layer_min_index = -1, prev_layer_max_index = -1;
    reverse(groups.begin(), groups.end());
    for (auto& group : groups) {
      int64_t this_layer_min = 2e18ll, this_layer_max = -2e18ll,
        this_layer_min_index = -1, this_layer_max_index = -1;
      for (int64_t v : group) {
        if (this_layer_min > a[v]) {
          this_layer_min = a[v];
          this_layer_min_index = v;
        }
        if (this_layer_max < a[v]) {
          this_layer_max = a[v];
          this_layer_max_index = v;
        }
      }
      for (int64_t v : group) {
        for (int64_t w : tree[v]) {
          dp[v] = max(dp[v], dp[w]);
        }
        dp[v] += max(a[v] - this_layer_min, this_layer_max - a[v]);
        if (prev_layer_min_index != -1) {
          dp[v] = max(dp[v], dp[prev_layer_min_index] +
            abs(a[v] - a[parent[prev_layer_min_index]]));
        }
        if (prev_layer_max_index != -1) {
          dp[v] = max(dp[v], dp[prev_layer_max_index] +
            abs(a[v] - a[parent[prev_layer_max_index]]));
        }
      }
      prev_layer_min_index = this_layer_min_index;
      prev_layer_max_index = this_layer_max_index;
    }
    cout << dp[0] << "\n";
  }
  return 0;
}
