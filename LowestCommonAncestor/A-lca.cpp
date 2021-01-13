#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class LCAComputer {
  public:
    explicit LCAComputer(int size);
    void AppendVertex(int parent, int vertex);
    int ComputeLCA(int first, int second) const;

private:
  int size_;
  std::vector<int> parent_;
  const int kRoot = 0;

  std::vector<int> GetAncestors(int vertex) const;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("lca.in", "r", stdin);
  std::freopen("lca.out", "w", stdout);

  int query_count;
  std::cin >> query_count;

  LCAComputer lca_computer(1'000);

  while (query_count --> 0) {
    std::string query_type;
    std::cin >> query_type;

    if (query_type == "ADD") {
      int parent, vertex;
      std::cin >> parent >> vertex;
      --parent, --vertex;
      lca_computer.AppendVertex(parent, vertex);
    } else {
      int first, second;
      std::cin >> first >> second;
      --first, --second;
      std::cout << lca_computer.ComputeLCA(first, second) + 1 << "\n";
    }
  }

  return 0;
}

LCAComputer::LCAComputer(int size) : size_(size) {
  parent_.resize(size_);
}

void LCAComputer::AppendVertex(int parent, int vertex) {
  parent_[vertex] = parent;
}

int LCAComputer::ComputeLCA(int first, int second) const {
  const auto first_ancestors = GetAncestors(first);
  const int first_ancestors_count = first_ancestors.size();
  const auto second_ancestors = GetAncestors(second);
  const int second_ancestors_count = second_ancestors.size();
  int lowest_common_ancestor = kRoot;
  const int min_ancestors_count \
    = std::min(first_ancestors_count, second_ancestors_count);
  for (int i = 0; i < min_ancestors_count; ++i) {
    if (first_ancestors[i] == second_ancestors[i]) {
      lowest_common_ancestor = first_ancestors[i];
    }
  }
  return lowest_common_ancestor;
}

std::vector<int> LCAComputer::GetAncestors(int vertex) const {
  std::vector<int> ancestors = {vertex};
  while (vertex != kRoot) {
    vertex = parent_[vertex];
    ancestors.push_back(vertex);
  }
  return {ancestors.rbegin(), ancestors.rend()};
}
