#include <algorithm>
#include <iostream>
#include <vector>

using DirectedGraph = std::vector<std::vector<int>>;

DirectedGraph ReadDirectedGraphEdgeList(int vertex_count = 0, int edge_count = 0,
  std::istream& in_stream = std::cin);

using Cycle = std::vector<int>;

Cycle FindCycle(const DirectedGraph& directed_graph);

bool FindCycleDepthFirstSearch(const DirectedGraph& directed_graph, 
  int vertex, std::vector<int8_t>* color_ptr, std::vector<int>* cycle_ptr);

void PrintCycle(const Cycle& cycle, std::ostream& out_stream = std::cout);

void PrintAnswer(const Cycle& cycle, std::ostream& out_stream = std::cout);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("cycle2.in", "r", stdin);
  std::freopen("cycle2.out", "w", stdout);

  const auto directed_graph = ReadDirectedGraphEdgeList();
  const auto cycle = FindCycle(directed_graph);
  PrintAnswer(cycle);

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

Cycle FindCycle(const DirectedGraph& directed_graph) {
  const int vertex_count = directed_graph.size();
  std::vector<int8_t> color(vertex_count, 0);
  std::vector<int> cycle;
  for (int vertex = 0; vertex < vertex_count; ++vertex) {
    if (!color[vertex]) {
      const bool found = FindCycleDepthFirstSearch(directed_graph, vertex,
        &color, &cycle);
      if (found) {
        return cycle;
      } else {
        cycle.clear();
      }
    }
  }
  return cycle;
}

bool FindCycleDepthFirstSearch(const DirectedGraph& directed_graph,
    int vertex, std::vector<int8_t>* color_ptr, std::vector<int>* cycle_ptr) {
  (*color_ptr)[vertex] = 1;
  cycle_ptr->push_back(vertex);
  for (auto adjacent : directed_graph[vertex]) {
    if (!(*color_ptr)[adjacent]) {
      const bool found = FindCycleDepthFirstSearch(directed_graph, adjacent, 
        color_ptr, cycle_ptr);
      if (found) {
        return true;
      }
    } else if ((*color_ptr)[adjacent] == 1) {
      const auto it = std::find(cycle_ptr->begin(), cycle_ptr->end(), adjacent);
      cycle_ptr->erase(cycle_ptr->begin(), it);
      return true;
    }
  }
  (*color_ptr)[vertex] = 2;
  cycle_ptr->pop_back();
  return false;
}

void PrintCycle(const Cycle& cycle, std::ostream& out_stream) {
  for (auto vertex : cycle) {
    out_stream << vertex + 1 << " ";
  }
}

void PrintAnswer(const Cycle& cycle, std::ostream& out_stream) {
  if (cycle.empty()) {
    out_stream << "NO\n";
  } else {
    out_stream << "YES\n";
    PrintCycle(cycle, out_stream);
    out_stream << "\n";
  }
}
