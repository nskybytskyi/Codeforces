#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using Edge = std::pair<int, int>;

using Graph = std::vector<std::vector<Edge>>;

Graph ReadGraphEdgeList(int vertex_count = 0, int edge_count = 0,
  std::istream& in_stream = std::cin);

std::pair<std::vector<int>, std::vector<int>> ComputeTimes(const Graph& graph);

void ComputeTimesDepthFirstSearch(const Graph& graph, int vertex,
  int* timer_ptr, std::pair<std::vector<int>, std::vector<int>>* times_ptr,
  std::vector<int8_t>* visited_ptr);

using Bridge = Edge;

std::vector<Bridge> FindBridges(const Graph& graph);

void FindBridgesDepthFirstSearch(const Graph& graph, int vertex, int parent,
  const std::vector<int>& times, std::vector<int>* min_back_in_time_ptr,
  std::vector<int8_t>* visited_ptr, std::vector<Bridge>* bridges_ptr);

void PrintBridges(const std::vector<Bridge>& bridges,
  std::ostream& out_stream = std::cout);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("bridges.in", "r", stdin);
  std::freopen("bridges.out", "w", stdout);

  const auto graph = ReadGraphEdgeList();
  const auto bridges = FindBridges(graph);
  PrintBridges(bridges);

  return 0;
}

Graph ReadGraphEdgeList(int vertex_count, int edge_count,
    std::istream& in_stream) {
  if (!vertex_count) {
    in_stream >> vertex_count;
  }
  Graph graph(vertex_count);
  if (!edge_count) {
    in_stream >> edge_count;
  }
  for (int edge_id = 0, first, second; edge_id < edge_count; ++edge_id) {
    in_stream >> first >> second;
    --first, --second;
    graph[first].emplace_back(second, edge_id);
    graph[second].emplace_back(first, edge_id);
  }
  return graph;
}

std::pair<std::vector<int>, std::vector<int>> ComputeTimes(const Graph& graph) {
  int timer = 0;
  const int vertex_count = graph.size();
  std::pair<std::vector<int>, std::vector<int>> times;
  times.first.resize(vertex_count);
  times.second.resize(vertex_count);
  std::vector<int8_t> visited(vertex_count);
  for (int vertex = 0; vertex < vertex_count; ++vertex) {
    if (!visited[vertex]) {
      ComputeTimesDepthFirstSearch(graph, vertex, &timer, &times, &visited);
    }
  }
  return times;
}

void ComputeTimesDepthFirstSearch(const Graph& graph, int vertex,
    int* timer_ptr, std::pair<std::vector<int>, std::vector<int>>* times_ptr,
    std::vector<int8_t>* visited_ptr) {
  (*visited_ptr)[vertex] = true;
  times_ptr->first[vertex] = *timer_ptr;
  ++(*timer_ptr);
  for (auto [adjacent, _] : graph[vertex]) {
    if (!(*visited_ptr)[adjacent]) {
      ComputeTimesDepthFirstSearch(graph, adjacent,
        timer_ptr, times_ptr, visited_ptr);
    }
  }
  times_ptr->second[vertex] = *timer_ptr;
  ++(*timer_ptr);
}

std::vector<Bridge> FindBridges(const Graph& graph) {
  const auto time_in = ComputeTimes(graph).first;
  std::vector<Bridge> bridges;
  const int vertex_count = graph.size();
  std::vector<int8_t> visited(vertex_count);
  std::vector<int> min_back_in_time(vertex_count);
  for (int vertex = 0; vertex < vertex_count; ++vertex) {
    if (!visited[vertex]) {
      FindBridgesDepthFirstSearch(graph, vertex, -1, time_in,
        &min_back_in_time, &visited, &bridges);
    }
  }
  std::sort(bridges.begin(), bridges.end(),
    [] (const Bridge& first, const Bridge& second) -> bool {
      return first.second < second.second;
    });
  return bridges;
}

void FindBridgesDepthFirstSearch(const Graph& graph, int vertex, int parent,
    const std::vector<int>& time_in, std::vector<int>* min_back_in_time_ptr,
    std::vector<int8_t>* visited_ptr, std::vector<Bridge>* bridges_ptr) {
  (*visited_ptr)[vertex] = true;
  (*min_back_in_time_ptr)[vertex] = time_in[vertex];
  for (auto [adjacent, edge_id] : graph[vertex]) {
    if (adjacent != parent) {
      if ((*visited_ptr)[adjacent]) {
        (*min_back_in_time_ptr)[vertex] = 
          std::min((*min_back_in_time_ptr)[vertex], time_in[adjacent]);
      } else {
        FindBridgesDepthFirstSearch(graph, adjacent, vertex,
          time_in, min_back_in_time_ptr, visited_ptr, bridges_ptr);
        (*min_back_in_time_ptr)[vertex] =
          std::min((*min_back_in_time_ptr)[vertex],
            (*min_back_in_time_ptr)[adjacent]);
        if ((*min_back_in_time_ptr)[adjacent] > time_in[vertex]) {
          bridges_ptr->emplace_back(adjacent, edge_id);
        }
      }
    }
  }
}

void PrintBridges(const std::vector<Bridge>& bridges, std::ostream& out_stream) {
  out_stream << bridges.size() << "\n";
  for (auto bridge : bridges) {
    out_stream << bridge.second + 1 << " ";
  }
  out_stream << "\n";
}
