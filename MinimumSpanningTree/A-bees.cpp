#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

inline int VertexID(int row, int column, int column_count);

using Edge = std::pair<int, int>;

using Graph = std::vector<std::vector<Edge>>;

Graph BuildGraph(int row_count, int column_count, int first_prime, int second_prime);

class DSU {
  public:
    explicit DSU(int vertex_count);
    int FindSet(int vertex);
    void UnionSets(int first, int second);

  private:
    std::vector<int> parent_, rank_;
};

int KruskalMST(int vertex_count, const Graph& graph);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("bees.in", "r", stdin);
  std::freopen("bees.out", "w", stdout);

  int row_count, column_count, first_prime, second_prime;
  std::cin >> row_count >> column_count >> first_prime >> second_prime;

  const auto graph = BuildGraph(row_count, column_count, first_prime, second_prime);
  std::cout << KruskalMST(row_count * column_count, graph) << "\n";

  return 0;
}

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

inline int VertexID(int row, int column, int column_count) {
  --row, --column;
  return row * column_count + column;
}

Graph BuildGraph(int row_count, int column_count, int first_prime, int second_prime) {
  Graph graph(second_prime);
  for (int row = 1; row <= row_count; ++row) {
    for (int column = 1; column <= column_count; ++column) {
      if (row + 1 <= row_count) {
        const int length = (row * (row + 1) + column * column * first_prime) % second_prime;
        graph[length].emplace_back(VertexID(row, column, column_count),
                                   VertexID(row + 1, column, column_count));
      }
      if (column + 1 <= column_count) {
        const int length = (row * row + column * (column + 1) * first_prime) % second_prime;
        graph[length].emplace_back(VertexID(row, column, column_count),
                                   VertexID(row, column + 1, column_count));
      }
      if (row + 1 <= row_count && column + 1 <= column_count) {
        const int length = (row * (row + 1) + column * (column + 1) * first_prime) % second_prime;
        graph[length].emplace_back(VertexID(row, column, column_count),
                                   VertexID(row + 1, column + 1, column_count));
      }
    }
  }
  return graph;
}

int KruskalMST(int vertex_count, const Graph& graph) {
  int mst_length = 0;
  const int max_edge_length = graph.size();
  DSU dsu(vertex_count);

  for (int edge_length = 0; edge_length < max_edge_length; ++edge_length) {
    for (const auto& [first, second] : graph[edge_length]) {
      if (dsu.FindSet(first) != dsu.FindSet(second)) {
        mst_length += edge_length;
        dsu.UnionSets(first, second);
      }
    }
  }

  return mst_length;
}
