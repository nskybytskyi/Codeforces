#include <bits/stdc++.h>
using namespace std;
const int kInfinity = std::numeric_limits<int>::max();
using Edge = std::pair<int, int>;
using Graph = std::vector<std::vector<Edge>>;
vector<int> DijkstraHeap(const Graph& graph, int source);
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int n, m;
  cin >> n >> m;
  Graph g(51 * n);
  // i + n * (w of prev edge or 0 if full step)
  while (m--) {
    int vi, ui, wi;
    cin >> vi >> ui >> wi;
    --vi, --ui;
    // second edge
    for (int wab = 1, wbc = wi; wab <= 50; ++wab) {
      g[vi + wab * n].emplace_back(ui, (wi + wab) * (wi + wab) - wab * wab);
      g[ui + wab * n].emplace_back(vi, (wi + wab) * (wi + wab) - wab * wab);
    }
    // first edge
    g[vi].emplace_back(ui + wi * n, wi * wi);
    g[ui].emplace_back(vi + wi * n, wi * wi);
  }
  auto distance = DijkstraHeap(g, 0);
  for (int i = 0; i < n; ++i) {
    if (distance[i] == kInfinity) {
      cout << "-1 ";
    } else {
      cout << distance[i] << " ";
    }
  }
  cout << "\n";
  return 0;
}
vector<int> DijkstraHeap(const Graph& graph, int source) {
  const int vertex_count = graph.size();
  std::vector<int> distance(vertex_count, kInfinity);
  distance[source] = 0;
  std::priority_queue<std::pair<int, int>,
                      std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>> heap;
  heap.emplace(0, source);
  while (!heap.empty()) {
    // extract closest unused vertex in O(log n)
    const auto [closest_distance, closest_vertex] = heap.top();
    heap.pop();
    if (closest_distance < kInfinity) {
      if (distance[closest_vertex] == closest_distance) {
        // process all outgoing edges from it
        for (const auto& [adjacent, edge_length] : graph[closest_vertex]) {
          if (distance[adjacent] > closest_distance + edge_length) {
            // std::cout << "Updating distance[" << adjacent << "] from " << distance[adjacent] <<
            //   " to " << closest_distance + edge_length << " via " << closest_vertex << "\n";
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