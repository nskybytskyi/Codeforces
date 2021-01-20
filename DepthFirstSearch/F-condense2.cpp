#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_set>
#include <vector>

using DirectedGraph = std::vector<std::vector<int>>;

DirectedGraph ReadDirectedGraphEdgeList(int vertex_count = 0, int edge_count = 0,
  std::istream& in_stream = std::cin);

DirectedGraph GetTransposedGraph(const DirectedGraph& directed_graph);

std::vector<int> ComputeTopologicalOrder(const DirectedGraph& directed_graph);

void ComputeTopologicalOrderDepthFirstSearch(const DirectedGraph& directed_graph,
  int vertex, std::vector<int>* order_ptr, std::vector<int8_t>* visited_ptr);

using Component = std::vector<int>;

std::vector<Component>
GetStronglyConnectedComponents(const DirectedGraph& directed_graph);

void GetStronglyConnectedComponentsDepthFirstSearch(
  const DirectedGraph& directed_graph, int vertex,
  std::vector<int8_t>* visted_ptr, std::vector<Component>* components_ptr);

DirectedGraph BuildCondensationGraph(const DirectedGraph& directed_graph);

int GetEdgeCount(const DirectedGraph& directed_graph);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("condense2.in", "r", stdin);
  std::freopen("condense2.out", "w", stdout);

  const auto directed_graph = ReadDirectedGraphEdgeList();
  const auto condensation = BuildCondensationGraph(directed_graph);
  std::cout << GetEdgeCount(condensation) << "\n";

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

DirectedGraph GetTransposedGraph(const DirectedGraph& directed_graph) {
  const int vertex_count = directed_graph.size();
  DirectedGraph transposed_graph(vertex_count);
  for (int vertex = 0; vertex < vertex_count; ++vertex) {
    for (auto adjacent : directed_graph[vertex]) {
      transposed_graph[adjacent].push_back(vertex);
    }
  }
  return transposed_graph;
}

std::vector<int> ComputeTopologicalOrder(const DirectedGraph& directed_graph) {
  std::vector<int> order;
  const int vertex_count = directed_graph.size();
  std::vector<int8_t> visited(vertex_count);
  for (int vertex = 0; vertex < vertex_count; ++vertex) {
    if (!visited[vertex]) {
      ComputeTopologicalOrderDepthFirstSearch(directed_graph, vertex,
        &order, &visited);
    }
  }
  return order;
}

void ComputeTopologicalOrderDepthFirstSearch(const DirectedGraph& directed_graph,
    int vertex, std::vector<int>* order_ptr, std::vector<int8_t>* visited_ptr) {
  (*visited_ptr)[vertex] = true;
  for (auto adjacent : directed_graph[vertex]) {
    if (!(*visited_ptr)[adjacent]) {
      ComputeTopologicalOrderDepthFirstSearch(directed_graph, adjacent,
        order_ptr, visited_ptr);
    }
  }
  order_ptr->push_back(vertex);
}

std::vector<Component>
GetStronglyConnectedComponents(const DirectedGraph& directed_graph) {
  auto order = ComputeTopologicalOrder(directed_graph);
  std::reverse(order.begin(), order.end());
  const int vertex_count = directed_graph.size();
  std::vector<int8_t> visited(vertex_count);
  const auto transposed_graph = GetTransposedGraph(directed_graph);
  std::vector<Component> components;
  for (auto vertex : order) {
    if (!visited[vertex]) {
      components.emplace_back();
      GetStronglyConnectedComponentsDepthFirstSearch(transposed_graph,
        vertex, &visited, &components);
    }
  }
  return components;
}

void GetStronglyConnectedComponentsDepthFirstSearch(
    const DirectedGraph& directed_graph, int vertex,
    std::vector<int8_t>* visited_ptr, std::vector<Component>* components_ptr) {
  (*visited_ptr)[vertex] = true;
  components_ptr->back().push_back(vertex);
  for (auto adjacent : directed_graph[vertex]) {
    if (!(*visited_ptr)[adjacent]) {
      GetStronglyConnectedComponentsDepthFirstSearch(directed_graph,
        adjacent, visited_ptr, components_ptr);
    }
  }
}

DirectedGraph BuildCondensationGraph(const DirectedGraph& directed_graph) {
  const auto components = GetStronglyConnectedComponents(directed_graph);
  const int vertex_count = directed_graph.size();
  std::vector<int> component_ids(vertex_count);
  int component_id = 0;
  for (const auto& component : components) {
    for (auto vertex : component) {
      component_ids[vertex] = component_id;
    }
    ++component_id;
  }
  const int component_count = component_id;
  std::vector<std::unordered_set<int>> pre_condensation(component_count);
  for (int vertex = 0; vertex < vertex_count; ++vertex) {
    for (auto adjacent : directed_graph[vertex]) {
      if (component_ids[vertex] != component_ids[adjacent]) {
        pre_condensation[component_ids[vertex]].insert(component_ids[adjacent]);
      }
    }
  }
  DirectedGraph condensation(component_count);
  for (int i = 0; i < component_count; ++i) {
    condensation[i] = {pre_condensation[i].begin(), pre_condensation[i].end()};
  }
  return condensation;
}

int GetEdgeCount(const DirectedGraph& directed_graph) {
  int edge_count = 0;
  for (const auto& adjacency_list : directed_graph) {
    edge_count += adjacency_list.size();
  }
  return edge_count;
}
