#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

class DSU {
  public:
    explicit DSU(int vertex_count);
    int FindSet(int vertex);
    void UnionSets(int first, int second);

  private:
    std::vector<int> parent_, rank_;
};

using Edge = std::pair<int, int>;

using Graph = std::vector<Edge>;

Graph ReadGraphEdgeList(int edge_count, std::istream& in_stream = std::cin);

std::vector<int> KruskalMST(int vertex_count, const Graph& graph);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("maxincycle.in", "r", stdin);
  std::freopen("maxincycle.out", "w", stdout);

  int vertex_count, edge_count;
  std::cin >> vertex_count >> edge_count;

  const auto graph = ReadGraphEdgeList(edge_count);
  const auto mst = KruskalMST(vertex_count, graph);

  const int mst_edge_count = mst.size();
  assert(mst_edge_count == vertex_count - 1 || !vertex_count);
  std::cout << mst_edge_count << "\n";

  for (auto edge : mst) {
    // convert back to 1-indexed
    std::cout << edge + 1 << " ";
  }
  std::cout << "\n";

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

Graph ReadGraphEdgeList(int edge_count, std::istream& in_stream) {
  Graph graph(edge_count);
  for (auto& edge : graph) {
    in_stream >> edge.first >> edge.second;
    --edge.first, --edge.second;
  }
  return graph;
}

std::vector<int> KruskalMST(int vertex_count, const Graph& graph) {
  DSU dsu(vertex_count);
  const int edge_count = graph.size();
  std::vector<int> mst;

  for (int edge_id = 0; edge_id < edge_count; ++edge_id) {
    const auto [first, second] = graph[edge_id];
    if (dsu.FindSet(first) != dsu.FindSet(second)) {
      mst.push_back(edge_id);
      dsu.UnionSets(first, second);
    }
  }

  return mst;
}
