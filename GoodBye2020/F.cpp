#include <bits/stdc++.h>

using namespace std;

const int mod = 1'000'000'007;

const int max_len = 500'500;

vector<int> pow2 = {1};

void init() {
  for (int i = 0; i < max_len; ++i) {
    pow2.push_back(pow2.back() << 1);
    if (pow2.back() >= mod) pow2.back() -= mod;
  }
}

class DSU {
  public:
    explicit DSU(int vertex_count);
    int FindSet(int vertex);
    void UnionSets(int first, int second);

  private:
    std::vector<int> parent_, rank_;
};

DSU::DSU(int vertex_count) {
  parent_.resize(vertex_count);
  rank_.resize(vertex_count);
  std::iota(parent_.begin(), parent_.end(), 0);
}

int DSU::FindSet(int vertex) {
  return (vertex == parent_[vertex]) ? vertex : (parent_[vertex] = FindSet(parent_[vertex]));
}

void DSU::UnionSets(int first, int second) {
  first = FindSet(first), second = FindSet(second);
  if (first != second) {
    if (rank_[first] < rank_[second]) {
      std::swap(first, second);
    }
    parent_[second] = first;
    if (rank_[first] == rank_[second]){
      ++rank_[first];
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  init();

  int n, m;
  cin >> n >> m;

  DSU dsu(m + 1);

  vector<int> s_prime;
  for (int i = 0; i < n; ++i) {
    int k;
    cin >> k;
    if (k == 1) {
      int x1;
      cin >> x1;
      if (dsu.FindSet(x1) != dsu.FindSet(0)) {
        s_prime.push_back(i + 1);
        dsu.UnionSets(x1, 0);
      }
    } else {
      int x1, x2;
      cin >> x1 >> x2;
      if (dsu.FindSet(x1) != dsu.FindSet(x2)) {
        s_prime.push_back(i + 1);
        dsu.UnionSets(x1, x2);
      }
    }
  }

  cout << pow2[s_prime.size()] << " " << s_prime.size() << "\n";
  for (auto x : s_prime)
    cout << x << " ";
  cout << "\n";

  return 0;
}
