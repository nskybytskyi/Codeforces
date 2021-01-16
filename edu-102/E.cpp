#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <limits>
#include <vector>

const int64_t kInfinity = std::numeric_limits<int64_t>::max();

using Edge = std::pair<int, int>;

using Graph = std::vector<std::vector<Edge>>;

std::vector<int64_t> DijkstraHeap(const Graph& graph, int source = 0);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int vertex_count, edge_count;
  std::cin >> vertex_count >> edge_count;

  Graph graph(vertex_count << 2);

  while (edge_count --> 0) {
    int first, second, weight;
    std::cin >> first >> second >> weight;
    --first, --second;

    
    // bitmask rows meanings:
    // 1 0 only max
    // 1 1 min and max 
    // 0 1 only min
    // 0 0 no min, no max 
    
    for (int bitmask : {0, 1, 2, 3}) {  // use edge as not min and not max
      graph[first + bitmask * vertex_count].emplace_back(second + bitmask * vertex_count, weight);
      graph[second + bitmask * vertex_count].emplace_back(first + bitmask * vertex_count, weight);
    }

    for (int bitmask : {0, 2}) {  // use edge as min, only possible if no edge was used as min yet
      graph[first + bitmask * vertex_count].emplace_back(second + (bitmask|1) * vertex_count, 0);
      graph[second + bitmask * vertex_count].emplace_back(first + (bitmask|1) * vertex_count, 0);
    }

    for (int bitmask : {0, 1}) {  // use edge as max, only possible if no edge was used as max yet
      graph[first + bitmask * vertex_count].emplace_back(second + (bitmask|2) * vertex_count, 2 * weight);
      graph[second + bitmask * vertex_count].emplace_back(first + (bitmask|2) * vertex_count, 2 * weight);
    }
  }

  const auto shortest_distances = DijkstraHeap(graph);
  for (int vertex = 1; vertex < vertex_count; ++vertex) {
    // shortest_distances[vertex] is taken to cover path length 1 
    // for instance from A to B according to defined path it will be
    // dist(a, b) + max - min = dist(a, b) + dist(a, b) - dist(a, b) = dist(a, b)
    // this falls back to the normal case
    // also shortest_distances[vertex + 3 * vertex_count] is always smaller than
    // shortest_distances[vertex] . Hence taking min works !
    std::cout << std::min(shortest_distances[vertex],
      shortest_distances[vertex + 3 * vertex_count]) << " ";
  }
  std::cout << "\n";

  return 0;
}

std::vector<int64_t> DijkstraHeap(const Graph& graph, int source) {
  const int vertex_count = graph.size();
  std::vector<int64_t> distance(vertex_count, kInfinity);
  distance[source] = 0;
  std::priority_queue<std::pair<int64_t, int>,
                      std::vector<std::pair<int64_t, int>>,
                      std::greater<std::pair<int64_t, int>>> heap;
  heap.emplace(0, source);

  while (!heap.empty()) {
    // select closest unused vertex in O(1)
    const auto [closest_distance, closest_vertex] = heap.top();
    // removes closest unused vertex in O(log vertex_count)
    heap.pop();
    if (closest_distance < kInfinity) {
      if (distance[closest_vertex] == closest_distance) {
        // process all outgoing edges from it
        for (const auto& [adjacent, edge_length] : graph[closest_vertex]) {
          if (distance[adjacent] > closest_distance + edge_length) {
            distance[adjacent] = closest_distance + edge_length;
            heap.emplace(distance[adjacent], adjacent);
          }
        }
      }  // else this is a fake pair
    } else {  // no more iterations needed, remaining vertices are unreachable
      break;
    }
  }

  return distance;
}
