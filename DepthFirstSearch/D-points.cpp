#include <algorithm>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

using Edge = int;

using Graph = std::vector<std::vector<Edge>>;

Graph ReadGraphEdgeList(int vertex_count = 0, int edge_count = 0,
  std::istream& in_stream = std::cin);

std::pair<std::vector<int>, std::vector<int>> ComputeTimes(const Graph& graph);

void ComputeTimesDepthFirstSearch(const Graph& graph, int vertex,
  int* timer_ptr, std::pair<std::vector<int>, std::vector<int>>* times_ptr,
  std::vector<int8_t>* visited_ptr);

using Cutpoint = int;

std::set<Cutpoint> FindCutpoints(const Graph& graph);

void FindCutpointsDepthFirstSearch(const Graph& graph, int vertex, int parent,
  const std::vector<int>& times, std::vector<int>* min_back_in_time_ptr,
  std::vector<int8_t>* visited_ptr, std::set<Cutpoint>* cutpoints_ptr);

void PrintCutpoints(const std::set<Cutpoint>& cutpoints,
  std::ostream& out_stream = std::cout);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("points.in", "r", stdin);
  std::freopen("points.out", "w", stdout);

  const auto graph = ReadGraphEdgeList();
  const auto cutpoints = FindCutpoints(graph);
  PrintCutpoints(cutpoints);

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
    graph[first].push_back(second);
    graph[second].push_back(first);
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
  for (auto adjacent : graph[vertex]) {
    if (!(*visited_ptr)[adjacent]) {
      ComputeTimesDepthFirstSearch(graph, adjacent,
        timer_ptr, times_ptr, visited_ptr);
    }
  }
  times_ptr->second[vertex] = *timer_ptr;
  ++(*timer_ptr);
}

std::set<Cutpoint> FindCutpoints(const Graph& graph) {
  const auto time_in = ComputeTimes(graph).first;
  std::set<Cutpoint> cutpoints;
  const int vertex_count = graph.size();
  std::vector<int8_t> visited(vertex_count);
  std::vector<int> min_back_in_time(vertex_count);
  for (int vertex = 0; vertex < vertex_count; ++vertex) {
    if (!visited[vertex]) {
      FindCutpointsDepthFirstSearch(graph, vertex, -1, time_in,
        &min_back_in_time, &visited, &cutpoints);
    }
  }
  return cutpoints;
}

void FindCutpointsDepthFirstSearch(const Graph& graph, int vertex, int parent,
    const std::vector<int>& time_in, std::vector<int>* min_back_in_time_ptr,
    std::vector<int8_t>* visited_ptr, std::set<Cutpoint>* cutpoints_ptr) {
  (*visited_ptr)[vertex] = true;
  (*min_back_in_time_ptr)[vertex] = time_in[vertex];
  int children = 0;
  for (auto adjacent : graph[vertex]) {
    if (adjacent != parent) {
      if ((*visited_ptr)[adjacent]) {
        (*min_back_in_time_ptr)[vertex] = 
          std::min((*min_back_in_time_ptr)[vertex], time_in[adjacent]);
      } else {
        FindCutpointsDepthFirstSearch(graph, adjacent, vertex,
          time_in, min_back_in_time_ptr, visited_ptr, cutpoints_ptr);
        (*min_back_in_time_ptr)[vertex] =
          std::min((*min_back_in_time_ptr)[vertex],
            (*min_back_in_time_ptr)[adjacent]);
        if ((*min_back_in_time_ptr)[adjacent] >= time_in[vertex] && parent != -1) {
          cutpoints_ptr->insert(vertex);
        }
        ++children;
      }
    }
  }
  if (parent == -1 && children > 1) {
    cutpoints_ptr->insert(vertex);
  }
}

void PrintCutpoints(const std::set<Cutpoint>& cutpoints,
    std::ostream& out_stream) {
  out_stream << cutpoints.size() << "\n";
  for (auto cutpoint : cutpoints) {
    out_stream << cutpoint + 1 << " ";
  }
  out_stream << "\n";
}
