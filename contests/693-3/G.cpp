#include <algorithm>
#include <deque>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
  int source, destination;
};

std::vector<Edge> ReadArray(int size = 0, std::istream& in_stream = std::cin) {
  if (!size) {
    in_stream >> size;
  }
  std::vector<Edge> edges(size);
  for (auto& edge : edges) {
    in_stream >> edge.source >> edge.destination;
    --edge.source, --edge.destination;  // convert vertex ids to 0-based
  }
  return edges;
}

using Graph = std::vector<std::vector<int>>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int vertex_count;
    cin >> vertex_count;
    Graph graph(vertex_count);
    Graph reverse_graph(vertex_count);
    const auto edges = ReadArray();
    for (const auto& edge : edges) {
      graph[edge.source].push_back(edge.destination);
      reverse_graph[edge.destination].push_back(edge.source);
    }

    vector<int> distance(vertex_count, numeric_limits<int>::max());
    deque<int> bfs = {0};
    vector<int> order;
    distance[0] = 0;
    while (!bfs.empty()) {
      const int vertex = bfs.front();
      order.push_back(vertex);
      bfs.pop_front();
      for (const int adjacent : graph[vertex]) {
        if (distance[adjacent] > distance[vertex] + 1) {
          distance[adjacent] = distance[vertex] + 1;
          bfs.push_back(adjacent);
        }
      }
    }
    reverse(order.begin(), order.end());

    vector<pair<int, int>> dp(vertex_count);
    for (int vertex = 0; vertex < vertex_count; ++vertex) {
      dp[vertex].first = distance[vertex];
      dp[vertex].second = distance[vertex];
    }
    dp[0] = {0, 0};
    for (const auto vertex : order) {
      for (const auto adjacent : graph[vertex]) {
        if (distance[vertex] >= distance[adjacent]) {
          dp[vertex].second = min(dp[vertex].second, dp[adjacent].first);
        } else {
          dp[vertex].first = min(dp[vertex].first, dp[adjacent].first);
          dp[vertex].second = min(dp[vertex].second, dp[adjacent].second);
        }
      }
    }

    for (int vertex = 0; vertex < vertex_count; ++vertex) {
      const auto& [first, second] = dp[vertex];
      cout << min(first, second) << " ";
    }
    cout << "\n";
  }

  return 0;
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
