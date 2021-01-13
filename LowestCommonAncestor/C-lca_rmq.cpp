#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
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
    std::vector<std::vector<int>> sparse_table_;
    static const int kRoot = 0;

    std::vector<int> first_, order_, depth_;
    Graph graph_;

    void DepthFirstSearch(int vertex = kRoot, int depth = 0);
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("lca_rmq.in", "r", stdin);
  std::freopen("lca_rmq.out", "w", stdout);

  int vertex_count, query_count;
  std::cin >> vertex_count >> query_count;

  LCAComputer lca_computer(vertex_count);

  for (int vertex = 1, parent; vertex < vertex_count; ++vertex) {
    std::cin >> parent;
    lca_computer.AppendVertex(parent, vertex);
  }

  lca_computer.Initialize();

  int64_t first, second, x, y, z, temporary, answer = 0, answers_sum = 0; 
  std::cin >> first >> second >> x >> y >> z;

  while (query_count --> 0) {
    temporary = (first + answer) % vertex_count;
    answer = lca_computer.ComputeLCA(temporary, second);
    first = (x * first + y * second + z) % vertex_count;
    second = (x * second + y * first + z) % vertex_count;
    answers_sum += answer;
  }

  std::cout << answers_sum << "\n";

  return 0;
}

LCAComputer::LCAComputer(int size)
    : size_(size), max_power_(33 - __builtin_clz(size)) {
  sparse_table_.resize(max_power_);
  for (auto& sparse_layer : sparse_table_) {
    sparse_layer.resize((size_ << 1) - 1);
  }

  graph_.resize(size_);
  first_.resize(size_);
  depth_.resize(size_);
}

void LCAComputer::AppendVertex(int parent, int vertex) {
  graph_[parent].push_back(vertex);
}

void LCAComputer::Initialize() {
  DepthFirstSearch();

  std::iota(sparse_table_[0].begin(), sparse_table_[0].end(), 0);

  for (int power = 1; power < max_power_; ++power) {
    for (int i = 0; i < (size_ << 1) - 1; ++i) {
      const int l = sparse_table_[power - 1][i];
      sparse_table_[power][i] = l;
      const int j = i + (1 << (power - 1));
      if (j < (size_ << 1) - 1) {
        const int k = sparse_table_[power - 1][j];
        if (depth_[order_[k]] < depth_[order_[l]]) {
          sparse_table_[power][i] = k;
        }
      }
    }
  }
}

int LCAComputer::ComputeLCA(int first, int second) const {
  const int left = std::min(first_[first], first_[second]);
  const int right = std::max(first_[first], first_[second]);

  const int power = 31 - __builtin_clz(right + 1 - left);

  const int left_answer = sparse_table_[power][left];
  const int right_answer = sparse_table_[power][right + 1 - (1 << power)];

  if (depth_[order_[left_answer]] < depth_[order_[right_answer]]) {
    return order_[left_answer];
  } else {
    return order_[right_answer];
  }
}

void LCAComputer::DepthFirstSearch(int vertex, int depth) {
  depth_[vertex] = depth;
  first_[vertex] = order_.size();
  order_.push_back(vertex);

  for (auto child : graph_[vertex]) {
    DepthFirstSearch(child, depth + 1);
    order_.push_back(vertex);
  }
}
