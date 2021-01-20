#include <iostream>
#include <vector>

using DirectedGraph = std::vector<std::vector<int>>;

DirectedGraph ReadDirectedGraphEdgeList(int vertex_count = 0, int edge_count = 0,
  std::istream& in_stream = std::cin);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("firesafe.in", "r", stdin);
  std::freopen("firesafe.out", "w", stdout);

  const auto directed_graph = ReadDirectedGraphEdgeList();

  // todo

  return 0;
}

DirectedGraph ReadDirectedGraphEdgeList(int vertex_count, int edge_count, 
    std::istream& in_stream) {
  if (!vertex_count) {
    in_stream >> vertex_count;
  }
  DirectedGraph directed_graph(vertex_count);
  if (!edge_count) {
    in_stream >> edge_count;
  }
  for (int edge_id = 0, first, second; edge_id < edge_count; ++edge_id) {
    in_stream >> first >> second;
    --first, --second;
    directed_graph[first].push_back(second);
  }
  return directed_graph;
}
