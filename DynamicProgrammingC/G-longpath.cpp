#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

template <typename T = int>
std::vector<T> ReadArray(int size = 0, std::istream& in_stream = std::cin);

struct Edge {
  int source, destination;
  friend std::istream& operator>>(std::istream& in_stream, Edge& edge);
};

using Graph = std::vector<std::vector<int>>;

int DFS(const Graph& graph, std::vector<int>* max_path_length_from_vertex_ptr, int vertex);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("longpath.in", "r", stdin);
  std::freopen("longpath.out", "w", stdout);

  int vertex_count;
  std::cin >> vertex_count;

  const auto edges = ReadArray<Edge>();

  Graph graph(vertex_count);
  for (const auto& edge : edges) {
    graph[edge.source].push_back(edge.destination);
  }

  std::vector<int> max_path_length_from_vertex(vertex_count, -1);
  for (int vertex = 0; vertex < vertex_count; ++vertex) {
    if (max_path_length_from_vertex[vertex] == -1) {
      DFS(graph, &max_path_length_from_vertex, vertex);
    }
  }

  const int max_path_length = *std::max_element(max_path_length_from_vertex.begin(),
    max_path_length_from_vertex.end());
  if (max_path_length == -1) {
    std::cout << 0 << "\n";
  } else {
    std::cout << max_path_length << "\n";
  }

  return 0;
}

std::istream& operator>>(std::istream& in_stream, Edge& edge) {
  in_stream >> edge.source >> edge.destination;
  --edge.source, --edge.destination;
  return in_stream;
}

template <typename T>
std::vector<T> ReadArray(int size, std::istream& in_stream) {
  if (!size) {
    in_stream >> size;
  }
  std::vector<T> array(size);
  for (auto& element : array) {
    in_stream >> element;
  }
  return array;
}

int DFS(const Graph& graph, std::vector<int>* max_path_length_from_vertex_ptr, int vertex) {
  int max_son_path_length = -1;
  for (const auto adjacent : graph[vertex]) {
    if ((*max_path_length_from_vertex_ptr)[adjacent] == -1) {
      max_son_path_length = std::max(max_son_path_length,
        DFS(graph, max_path_length_from_vertex_ptr, adjacent));
    } else {
      max_son_path_length = std::max(max_son_path_length,
        (*max_path_length_from_vertex_ptr)[adjacent]);
    }
  }
  return (*max_path_length_from_vertex_ptr)[vertex] = max_son_path_length + 1;
}
