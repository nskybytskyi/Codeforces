#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <queue>
#include <utility>
#include <vector>

const int kInfinity = std::numeric_limits<int>::max();

using Edge = std::pair<int, int>;

using Graph = std::vector<std::vector<Edge>>;

Graph ReadGraphEdgeList(int vertex_count, int edge_count, std::istream& in_stream = std::cin);

std::pair<std::vector<int>, std::vector<int>> DijkstraHeapParent(const Graph& graph, int source);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("distance.in", "r", stdin);
  std::freopen("distance.out", "w", stdout);

  int vertex_count, edge_count, source, destination;
  std::cin >> vertex_count >> edge_count >> source >> destination;
  --source, --destination;  // convert to 0-based

  assert(0 <= source && source < vertex_count);
  assert(0 <= destination && destination < vertex_count);

  const auto graph = ReadGraphEdgeList(vertex_count, edge_count);
  const auto [distances, parents] = DijkstraHeapParent(graph, source);

  if (distances[destination] < kInfinity) {
    std::cout << distances[destination] << "\n";
    std::vector<int> path = {destination};
    while (path.back() != source) {
      path.push_back(parents[path.back()]);
    }
    std::reverse(path.begin(), path.end());
    for (const auto vertex : path) {
      std::cout << vertex + 1 << " ";  // convert back to 1-indexed
    }
    std::cout << "\n";
  } else {  // unreachable
    std::cout << -1 << "\n";
  }

  return 0;
}

Graph ReadGraphEdgeList(int vertex_count, int edge_count, std::istream& in_stream) {
  Graph graph(vertex_count);
  for (int edge_id = 0; edge_id < edge_count; ++edge_id) {
    int first, second, weight;
    in_stream >> first >> second >> weight; 
    --first, --second;  // convert to 0-based
    graph[first].emplace_back(second, weight);
    graph[second].emplace_back(first, weight);
  }
  return graph;
}

std::pair<std::vector<int>, std::vector<int>> DijkstraHeapParent(const Graph& graph, int source) {
  const int vertex_count = graph.size();
  std::vector<int> distance(vertex_count, kInfinity);
  std::vector<int> parent(vertex_count, -1);
  distance[source] = 0;
  std::priority_queue<std::pair<int, int>,
                      std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>> heap;
  heap.emplace(0, source);

  while (!heap.empty()) {
    // select closest unused vertex in O(log n)
    const auto [closest_distance, closest_vertex] = heap.top();
    heap.pop();
    if (closest_distance < kInfinity) {
      if (distance[closest_vertex] == closest_distance) {
        // process all outgoing edges from it
        for (const auto& [adjacent, edge_length] : graph[closest_vertex]) {
          if (distance[adjacent] > closest_distance + edge_length) {
            // std::cout << "Updating distance[" << adjacent << "] from " << distance[adjacent] <<
            //   " to " << closest_distance + edge_length << " via " << closest_vertex << "\n";
            parent[adjacent] = closest_vertex;
            distance[adjacent] = closest_distance + edge_length;
            heap.emplace(distance[adjacent], adjacent);
          }
        }
      }  // else this is a fake pair
    } else {  // no more iterations needed, remaining vertices are unreachable
      break;
    }
  }

  return {distance, parent};
}
