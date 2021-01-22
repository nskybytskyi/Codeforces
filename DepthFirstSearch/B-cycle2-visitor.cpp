#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

template <class Iterator>
class IteratorRange {
  public:
    IteratorRange(Iterator begin, Iterator end) : begin_(begin), end_(end) {}

    Iterator begin() const {  // NOLINT
      return begin_;
    }

    Iterator end() const {  // NOLINT
      return end_;
    }

  private:
    Iterator begin_, end_;
};

template <class Vertex>
struct IEdge {
  Vertex source, destination;
};

template <class Vertex, class Edge>
class IGraph {
  public:
    using VertexIterator = typename std::vector<Vertex>::const_iterator;
    virtual IteratorRange<VertexIterator> GetVertices() const = 0;

    using EdgeIterator = typename std::vector<Edge>::const_iterator;
    virtual IteratorRange<EdgeIterator> GetOutgoingEdges([[maybe_unused]] Vertex vertex) const = 0;
};

template <class Vertex, class Edge>
class IDFSVisitor {
  public:
    virtual void InitializeVertex([[maybe_unused]] Vertex vertex) {}
    virtual void DiscoverVertex([[maybe_unused]] Vertex vertex) {}
    virtual void StartVertex([[maybe_unused]] Vertex vertex) {}
    virtual void ExamineEdge([[maybe_unused]] const Edge& edge) {}
    virtual void TreeEdge([[maybe_unused]] const Edge& edge) {}
    virtual void BackEdge([[maybe_unused]] const Edge& edge) {}
    virtual void ForwardOrCrossEdge([[maybe_unused]] const Edge& edge) {}
    virtual void FinishEdge([[maybe_unused]] const Edge& edge) {}
    virtual void FinishVertex([[maybe_unused]] Vertex vertex) {}
};

template <class Vertex, class Edge, class Graph, class DFSVisitor>
class DFS {
  public:
    enum class Color {
      kWhite = 0,
      kGray = 1,
      kBlack = 2
    };

    std::unordered_map<Vertex, Color> color;

    void DepthFirstSearch(const Graph& graph, DFSVisitor& visitor, Vertex start = -1);

  private:
    void DepthFirstSearchVisit(const Graph& graph, Vertex vertex, DFSVisitor& visitor);
};

using Vertex = int;

using Edge = IEdge<Vertex>;

class Graph : IGraph<Vertex, Edge> {
  public:
    explicit Graph(int vertex_count) : kVertexCount(vertex_count) {
      vertices_.resize(kVertexCount);
      std::iota(vertices_.begin(), vertices_.end(), 0);
      outgoing_edges_.resize(kVertexCount);
    }

    void AddEdge(const Edge& edge);

    using VertexIterator = typename std::vector<Vertex>::const_iterator;
    IteratorRange<VertexIterator> GetVertices() const override;

    using EdgeIterator = typename std::vector<Edge>::const_iterator;
    IteratorRange<EdgeIterator> GetOutgoingEdges(Vertex vertex) const override;

  private:
    const int kVertexCount;
    std::vector<Vertex> vertices_;
    std::vector<std::vector<Edge>> outgoing_edges_;
};

struct CycleDFSVisitor : IDFSVisitor<Vertex, Edge> {
  bool found_cycle = false;
  std::vector<Vertex> cycle;

  void DiscoverVertex(Vertex vertex) override;
  void BackEdge(const Edge& edge) override;
  void FinishVertex(Vertex vertex) override;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("cycle2.in", "r", stdin);
  std::freopen("cycle2.out", "w", stdout);

  int vertex_count, edge_count;
  std::cin >> vertex_count >> edge_count;
  Graph graph(vertex_count);
  while (edge_count --> 0) {
    int source, destination;
    std::cin >> source >> destination;
    --source, --destination;
    graph.AddEdge({source, destination});
  }

  DFS<Vertex, Edge, Graph, CycleDFSVisitor> dfs;
  CycleDFSVisitor cycle_dfs_visitor;
  dfs.DepthFirstSearch(graph, cycle_dfs_visitor);

  if (cycle_dfs_visitor.found_cycle) {
    std::cout << "YES\n";
    for (auto vertex : cycle_dfs_visitor.cycle) {
      std::cout << vertex + 1 << " ";
    }
    std::cout << "\n";
  } else {
    std::cout << "NO\n";
  } 

  return 0;
}

template <class Vertex, class Edge, class Graph, class DFSVisitor>
void DFS<Vertex, Edge, Graph, DFSVisitor>::DepthFirstSearch(const Graph& graph, DFSVisitor& visitor, Vertex start) {
  for (const auto& vertex : graph.GetVertices()) {
    color[vertex] = Color::kWhite;
    visitor.InitializeVertex(vertex);
  }
  if (start != -1) {
    visitor.StartVertex(start);
    DepthFirstSearchVisit(graph, start, visitor);
  }
  for (const auto& vertex : graph.GetVertices()) {
    if (color[vertex] == Color::kWhite) {
      DepthFirstSearchVisit(graph, vertex, visitor);
    }
  }
}

template <class Vertex, class Edge, class Graph, class DFSVisitor>
void DFS<Vertex, Edge, Graph, DFSVisitor>::DepthFirstSearchVisit(const Graph& graph, Vertex vertex, DFSVisitor& visitor) {
  color[vertex] = Color::kGray;
  visitor.DiscoverVertex(vertex);
  for (const auto& outgoing_edge : graph.GetOutgoingEdges(vertex)) {
    visitor.ExamineEdge(outgoing_edge);
    const auto destination = outgoing_edge.destination;
    if (color[destination] == Color::kWhite) {
      DepthFirstSearchVisit(graph, destination, visitor);
      visitor.TreeEdge(outgoing_edge);
    } else if (color[destination] == Color::kGray) {
      visitor.BackEdge(outgoing_edge);
    } else {
      visitor.ForwardOrCrossEdge(outgoing_edge);
    }
    visitor.FinishEdge(outgoing_edge);
  }
  color[vertex] = Color::kBlack;
  visitor.FinishVertex(vertex);
}

void Graph::AddEdge(const Edge& edge) {
  outgoing_edges_[edge.source].push_back(edge);
}

using VertexIterator = typename std::vector<Vertex>::const_iterator;
IteratorRange<VertexIterator> Graph::GetVertices() const {
  return {vertices_.begin(), vertices_.end()};
}

using EdgeIterator = typename std::vector<Edge>::const_iterator;
IteratorRange<EdgeIterator> Graph::GetOutgoingEdges([[maybe_unused]] Vertex vertex) const {
  return {outgoing_edges_[vertex].begin(), outgoing_edges_[vertex].end()};
}

void CycleDFSVisitor::DiscoverVertex(Vertex vertex) {
  if (!found_cycle) { 
    cycle.push_back(vertex);
  }
}

void CycleDFSVisitor::BackEdge(const Edge& edge) {
  if (!found_cycle) { 
    found_cycle = true;
    const auto it = std::find(cycle.begin(), cycle.end(), edge.destination);
    cycle.erase(cycle.begin(), it);
  }
}

void CycleDFSVisitor::FinishVertex(Vertex vertex) {
  if (!found_cycle) { 
    cycle.pop_back();
  }
}
