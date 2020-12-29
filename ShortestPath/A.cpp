#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <vector>

const int kInfinity = std::numeric_limits<int>::max();

using Graph = std::vector<std::vector<int>>;

Graph ReadGraphAdjacencyMatrix(int vertex_count, std::istream& in_stream = std::cin);

std::vector<int> DijkstraArray(const Graph& graph, int source);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("dijkstra.in", "r", stdin);
  std::freopen("dijkstra.out", "w", stdout);

  int vertex_count, source, destination;
  std::cin >> vertex_count >> source >> destination;
  --source, --destination;  // convert to 0-based

  assert(0 <= source && source < vertex_count);
  assert(0 <= destination && destination < vertex_count);

  const auto graph = ReadGraphAdjacencyMatrix(vertex_count);
  const auto distances = DijkstraArray(graph, source);

  if (distances[destination] < kInfinity) {
    std::cout << distances[destination] << "\n";
  } else {  // unreachable
    std::cout << -1 << "\n";
  }

  return 0;
}

Graph ReadGraphAdjacencyMatrix(int vertex_count, std::istream& in_stream) {
  Graph graph(vertex_count, std::vector<int>(vertex_count));
  for (auto& vertex_neighbourhood : graph) {
    for (auto& edge_weight : vertex_neighbourhood) {
      in_stream >> edge_weight;
    }
  }
  return graph;
}

std::vector<int> DijkstraArray(const Graph& graph, int source) {
  const int vertex_count = graph.size();
  std::vector<int> distance(vertex_count, kInfinity);
  std::vector<bool> used(vertex_count, false);
  distance[source] = 0;
  const int iteration_count = vertex_count;

  for (int iteration = 0; iteration < iteration_count; ++iteration) {
    // select the closest unused vertex in O(n)
    int closest_vertex = -1, closest_distance = kInfinity;
    for (int vertex = 0; vertex < vertex_count; ++vertex) {
      if (!used[vertex] && distance[vertex] < closest_distance) {
        closest_distance = distance[vertex];
        closest_vertex = vertex;
      }
    }

    // process all outgoing edges from it
    if (closest_distance < kInfinity) {
      for (int adjacent_vertex = 0; adjacent_vertex < vertex_count; ++adjacent_vertex) {
        const int edge_length = graph[closest_vertex][adjacent_vertex];
        if (edge_length != -1) {
          distance[adjacent_vertex] = \
            std::min(distance[adjacent_vertex], edge_length + closest_distance);
        }
      }
      used[closest_vertex] = true;
    } else {  // no more iterations needed, remaining vertices are unreachable
      break;
    }
  }

  return distance;
}
