#include <bits/stdc++.h>
using namespace std;

class DSU {
  public:
    explicit DSU(int size);
    int Find(int vertex) const;
    void Union(int first, int second, int id);
    int Cost(int vertex) const;

    mutable std::vector<int> parent_;
    std::vector<int> rank_, id_;
};

int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);    
  int n;
  cin >> n;
  vector<vector<int>> a(n, vector<int>(n));
  for (auto& ai : a) {
    for (auto& aij : ai) {
      cin >> aij;
    }
  }
  DSU dsu(n);
  vector<int> c(n);
  map<int, int> p;
  for (int i = 0; i < n; ++i) {
    c[i] = a[i][i];
  }
  vector<pair<int, pair<int, int>>> aa;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      aa.emplace_back(a[i][j], make_pair(i, j));
    }
  }
  sort(aa.begin(), aa.end());
  for (auto [aij, ij] : aa) {
    auto [i, j] = ij;
    auto ii = dsu.Find(i), jj = dsu.Find(j);
    if (ii != jj) {
      auto pi = dsu.id_[ii], pj = dsu.id_[jj];
      if (c[pi] == aij) {
        dsu.Union(ii, jj, pi);
        p[pj] = pi;
      } else if (c[pj] == aij) {
        dsu.Union(ii, jj, pj);
        p[pi] = pj;
      } else {
        int id = c.size();
        dsu.Union(ii, jj, id);
        c.push_back(aij);
        p[pi] = p[pj] = id;
      }
    }
  }
  int k = c.size();
  cout << k << "\n";
  for (auto ci : c) {
    std::cout << ci << " ";
  }
  std::cout << "\n";
  int r = dsu.id_[dsu.Find(0)];
  cout << r + 1 << "\n";
  for (auto i = 0; i < k; ++i) {
    if (i != r) {
      cout << i + 1 << " " << p[i] + 1 << "\n";
    }
  }
  return 0;
}

DSU::DSU(int size) {
  rank_.resize(size);
  parent_.resize(size);
  id_.resize(size);
  std::iota(parent_.begin(), parent_.end(), 0);
  std::iota(id_.begin(), id_.end(), 0);
}

int DSU::Find(int vertex) const {
  return (vertex == parent_[vertex]) ? vertex : (parent_[vertex] = Find(parent_[vertex]));
}

void DSU::Union(int first, int second, int id) {
  first = Find(first), second = Find(second);
  if (first != second) {
    if (rank_[first] < rank_[second]) {
      std::swap(first, second);
    }
    parent_[second] = first;
    if (rank_[first] == rank_[second]){
      ++rank_[first];
    }
    id_[first] = id;
  }
}
