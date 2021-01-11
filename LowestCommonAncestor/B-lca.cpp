#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using Graph = std::vector<std::vector<int>>;

class LCAComputer {
  public:
    explicit LCAComputer(int size);
    void AppendVertex(int parent, int vertex);
    void Initialize();
    int ComputeLCA(int first, int second) const;

  private:
    int size_, max_power_;
    std::vector<std::vector<int>> parent_;
    static const int kRoot = 0;

    int timer_ = 0;
    std::vector<int> time_in_, time_out_;
    Graph graph_;

    void DepthFirstSearch(int vertex = kRoot);
    inline bool IsAncestor(int first, int second) const;
};

using GetQuery = std::pair<int, int>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("lca.in", "r", stdin);
  std::freopen("lca.out", "w", stdout);

  int query_count;
  std::cin >> query_count;

  LCAComputer lca_computer(500'000);

  std::vector<GetQuery> get_queries;
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
      get_queries.emplace_back(first, second);
    }
  }

  lca_computer.Initialize();

  for (const auto& get_query : get_queries) {
    std::cout << lca_computer.ComputeLCA(get_query.first, get_query.second) + 1 << "\n";
  }

  return 0;
}

LCAComputer::LCAComputer(int size) : size_(size), max_power_(31 - __builtin_clz(size)) {
  parent_.resize(max_power_);
  for (auto& parent_layer : parent_) {
    parent_layer.resize(size_);
  }
  for (int power = 0; power < max_power_; ++power) {
    parent_[power][kRoot] = kRoot;
  }

  graph_.resize(size_);
  time_in_.resize(size_);
  time_out_.resize(size_);
}

void LCAComputer::AppendVertex(int parent, int vertex) {
  parent_[0][vertex] = parent;
  for (int power = 1; power < max_power_; ++power) {
    parent_[power][vertex] = parent_[power - 1][parent_[power - 1][vertex]];
  }

  graph_[parent].push_back(vertex);
}

void LCAComputer::Initialize() {
  DepthFirstSearch();
}

int LCAComputer::ComputeLCA(int first, int second) const {
  if (IsAncestor(first, second)) {
    return first;
  } else if (IsAncestor(second, first)) {
    return second;
  } else {
    for (int power = max_power_ - 1; power >= 0; --power) {
      if (!IsAncestor(parent_[power][first], second)) {
        first = parent_[power][first];
      }
    }
    return parent_[0][first];
  }
}

void LCAComputer::DepthFirstSearch(int vertex) {
  time_in_[vertex] = timer_++;
  for (auto successor : graph_[vertex]) {
    DepthFirstSearch(successor);
  }
  time_out_[vertex] = timer_++;
}

inline bool LCAComputer::IsAncestor(int first, int second) const {
  return time_in_[first] <= time_in_[second] && time_out_[second] <= time_out_[first];
}
