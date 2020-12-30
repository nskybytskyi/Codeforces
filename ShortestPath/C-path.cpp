#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

const int64_t kInfinity = std::numeric_limits<int64_t>::max();
const int64_t kMinusInfinity = std::numeric_limits<int64_t>::min();

using Edge = std::pair<int, int64_t>;

using Graph = std::vector<std::vector<Edge>>;

Graph ReadGraphEdgeList(int vertex_count, int edge_count, std::istream& in_stream = std::cin);

std::vector<int64_t> FordBellman(const Graph& graph, int source);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("path.in", "r", stdin);
  std::freopen("path.out", "w", stdout);

  int vertex_count, edge_count, source;
  std::cin >> vertex_count >> edge_count >> source;
  --source;  // convert to 0-based

  assert(0 <= source && source < vertex_count);

  const auto graph = ReadGraphEdgeList(vertex_count, edge_count);
  const auto distances = FordBellman(graph, source);

  for (int destination = 0; destination < vertex_count; ++destination) {
    if (distances[destination] == kInfinity) {
      std::cout << "*" << "\n";
    } else if (distances[destination] == kMinusInfinity) {
      std::cout << "-" << "\n";
    } else {
      std::cout << distances[destination] << "\n";
    }
  }

  return 0;
}

Graph ReadGraphEdgeList(int vertex_count, int edge_count, std::istream& in_stream) {
  Graph graph(vertex_count);
  for (int edge_id = 0; edge_id < edge_count; ++edge_id) {
    int source, destination; int64_t weight;
    in_stream >> source >> destination >> weight; 
    --source, --destination;  // convert to 0-based
    graph[source].emplace_back(destination, weight);
  }
  return graph;
}

std::vector<int64_t> FordBellman(const Graph& graph, int source) {
  const int vertex_count = graph.size();
  std::vector<int64_t> distance(vertex_count, kInfinity);
  distance[source] = 0;

  // first phase - regular distances
  const int iteration_count = vertex_count - 1;
  for (int iteration = 0; iteration < iteration_count; ++iteration) {
    for (int vertex = 0; vertex < vertex_count; ++vertex) {
      if (distance[vertex] < kInfinity) {
        for (const auto& [adjacent, edge_length] : graph[vertex]) {
          distance[adjacent] = std::min(distance[adjacent], distance[vertex] + edge_length);
        }
      }
    }
  }

  // second phase - negative cycles
  for (int iteration = 0; iteration < iteration_count; ++iteration) {
    for (int vertex = 0; vertex < vertex_count; ++vertex) {
      if (distance[vertex] < kInfinity) {
        for (const auto& [adjacent, edge_length] : graph[vertex]) {
          if (distance[adjacent] > distance[vertex] + edge_length ||
              distance[vertex] == kMinusInfinity) {
            distance[adjacent] = kMinusInfinity;
          }
        }
      }
    }
  }

  return distance;
}
