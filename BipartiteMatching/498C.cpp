#include <bits/stdc++.h>
using namespace std;
// library code goes here

vector<int> factorize(int n) {
  vector<int> factors;
  for (int d = 2; d * d <= n; ++d) {
    while (n % d == 0) {
      factors.push_back(d);
      n /= d;
    }
  }
  if (n > 1)
    factors.push_back(n);
  return factors;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (auto& ai : a)
    cin >> ai;
  vector<pair<int, int>> ij(m);
  for (auto& ijk : ij) {
    cin >> ijk.first >> ijk.second;
    --ijk.first, --ijk.second;
  }

  vector<vector<int>> factors(n);
  vector<int> offset(n);
  pair<int, int> s;
  for (int i = 0; i < n; ++i) {
    factors[i] = factorize(a[i]);
    if (i & 1)
      s.second += factors[i].size();
    else
      s.first += factors[i].size();
    if (i >= 2)
      offset[i] = offset[i - 2] + factors[i - 2].size();
  }

  BipartiteGraph bipartite_graph(s);
  for (auto [i, j] : ij)
    for (int k = 0; k < (int)factors[i].size(); ++k)
      for (int l = 0; l < (int)factors[j].size(); ++l)
        if (factors[i][k] == factors[j][l])
          if (i & 1)
            bipartite_graph.AddEdge({offset[j] + l, offset[i] + k});
          else
            bipartite_graph.AddEdge({offset[i] + k, offset[j] + l});

  cout << Kuhn(bipartite_graph).Size() << "\n";

  return 0;
}
