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

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

  int n, m;
  cin >> n >> m;
  vector<tuple<int, int, int>> e(m);
  for (auto& [d, u, v] : e) {
    cin >> u >> v >> d;
    --u, --v;
  }
  sort(e.begin(), e.end());

  int lo = 0, hi = m;
  auto cannot = [&] (int mi) -> bool {
    BipartiteGraph bipartite_graph({n, n});
    for (int i = 0; i < mi; ++i)
      bipartite_graph.AddEdge({get<1>(e[i]), get<2>(e[i])});
    return HopcroftKarp(bipartite_graph).Size() < n;
  };

  if (cannot(hi))
    cout << -1 << "\n";
  else
    cout << get<0>(e[BinarySearch<int>(lo, hi, cannot)]) << "\n";

  return 0;
}
