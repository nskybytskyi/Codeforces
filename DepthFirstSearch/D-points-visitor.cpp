#include <algorithm>
#include <iostream>
#include <set>
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

    size_t size() const {  // NOLINT
      return std::distance(begin_, end_);
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
    virtual IteratorRange<EdgeIterator> GetOutgoingEdges(Vertex /* vertex */) const = 0;
};

template <class Vertex, class Edge>
class IDFSVisitor {
  public:
    virtual void InitializeVertex(Vertex /* vertex */) {}
    virtual void DiscoverVertex(Vertex /* vertex */) {}
    virtual void StartVertex(Vertex /* vertex */) {}
    virtual void ExamineEdge(const Edge& /* edge */) {}
    virtual void TreeEdge(const Edge& /* edge */) {}
    virtual void BackEdge(const Edge& /* edge */) {}
    virtual void ForwardOrCrossEdge(const Edge& /* edge */) {}
    virtual void FinishEdge(const Edge& /* edge */) {}
    virtual void FinishVertex(Vertex /* vertex */) {}
};

enum class Color {
  kWhite = 0,
  kGray = 1,
  kBlack = 2
};

template <class Vertex>
class IColormap {
  public:
    virtual Color GetColor(Vertex /* vertex */) const = 0;
    virtual void SetColor(Vertex /* vertex */, Color /* color */) = 0;
};

template <class Vertex, class Graph, class Colormap, class DFSVisitor>
void DepthFirstSearch(const Graph& graph, DFSVisitor& visitor, Vertex start = -1);

template <class Vertex, class Graph, class Colormap, class DFSVisitor>
void DepthFirstSearchVisit(const Graph& graph, Colormap& colormap, DFSVisitor& visitor, Vertex vertex);

using Vertex = int;

using Edge = IEdge<Vertex>;

class Graph : IGraph<Vertex, Edge> {
  public:
    explicit Graph(int vertex_count) {
      vertices_.resize(vertex_count);
      std::iota(vertices_.begin(), vertices_.end(), 0);
      outgoing_edges_.resize(vertex_count);
    }

    void AddEdge(const Edge& edge);

    using VertexIterator = typename std::vector<Vertex>::const_iterator;
    IteratorRange<VertexIterator> GetVertices() const override;

    using EdgeIterator = typename std::vector<Edge>::const_iterator;
    IteratorRange<EdgeIterator> GetOutgoingEdges(Vertex vertex) const override;

  private:
    std::vector<Vertex> vertices_;
    std::vector<std::vector<Edge>> outgoing_edges_;
};

class Colormap : IColormap<Vertex> {
  public:
    explicit Colormap(int vertex_count) {
      colormap_.resize(vertex_count, Color::kWhite);
    }

    Color GetColor(Vertex vertex) const override;
    void SetColor(Vertex vertex, Color color) override;

  private:
    std::vector<Color> colormap_;
};

struct CutpointDFSVisitor : IDFSVisitor<Vertex, Edge> {
  explicit CutpointDFSVisitor(int vertex_count) {
    parent.resize(vertex_count, -2);
    time_in.resize(vertex_count);
    children.resize(vertex_count);
    min_back_time_in.resize(vertex_count);
  }

  void StartVertex(Vertex vertec) override;
  void DiscoverVertex(Vertex vertex) override;
  void ExamineEdge(const Edge& edge) override;
  void TreeEdge(const Edge& edge) override;
  void BackEdge(const Edge& edge) override;
  void ForwardOrCrossEdge(const Edge& edge) override;
  void FinishVertex(Vertex vertex) override;

  int timer = 0;
  std::set<Vertex> cutpoints;
  std::vector<Vertex> parent;
  std::vector<int> time_in, children, min_back_time_in;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("points.in", "r", stdin);
  std::freopen("points.out", "w", stdout);

  int vertex_count, edge_count;
  std::cin >> vertex_count >> edge_count;
  Graph graph(vertex_count);
  while (edge_count --> 0) {
    Vertex first, second;
    std::cin >> first >> second;
    --first, --second;
    graph.AddEdge({first, second});
    graph.AddEdge({second, first});
  }

  CutpointDFSVisitor cutpoint_dfs_visitor(vertex_count);
  DepthFirstSearch<Vertex, Graph, Colormap, CutpointDFSVisitor>(graph, cutpoint_dfs_visitor);

  std::cout << cutpoint_dfs_visitor.cutpoints.size() << "\n";
  for (const auto& cutpoint : cutpoint_dfs_visitor.cutpoints) {
    std::cout << cutpoint + 1 << " ";
  }
  std::cout << "\n";

  return 0;
}

template <class Vertex, class Graph, class Colormap, class DFSVisitor>
void DepthFirstSearch(const Graph& graph, DFSVisitor& visitor, Vertex start) {
  Colormap colormap(graph.GetVertices().size());
  for (const auto& vertex : graph.GetVertices()) {
    colormap.SetColor(vertex, Color::kWhite);
    visitor.InitializeVertex(vertex);
  }
  if (start != -1) {
    visitor.StartVertex(start);
    DepthFirstSearchVisit(graph, colormap, visitor, start);
  }
  for (const auto& vertex : graph.GetVertices()) {
    if (colormap.GetColor(vertex) == Color::kWhite) {
      visitor.StartVertex(vertex);
      DepthFirstSearchVisit(graph, colormap, visitor, vertex);
    }
  }
}

template <class Vertex, class Graph, class Colormap, class DFSVisitor>
void DepthFirstSearchVisit(const Graph& graph, Colormap& colormap, DFSVisitor& visitor, Vertex vertex) {
  colormap.SetColor(vertex, Color::kGray);
  visitor.DiscoverVertex(vertex);
  for (const auto& outgoing_edge : graph.GetOutgoingEdges(vertex)) {
    visitor.ExamineEdge(outgoing_edge);
    const auto destination = outgoing_edge.destination;
    if (colormap.GetColor(destination) == Color::kWhite) {
      DepthFirstSearchVisit(graph, colormap, visitor, destination);
      visitor.TreeEdge(outgoing_edge);
    } else if (colormap.GetColor(destination) == Color::kGray) {
      visitor.BackEdge(outgoing_edge);
    } else {
      visitor.ForwardOrCrossEdge(outgoing_edge);
    }
    visitor.FinishEdge(outgoing_edge);
  }
  colormap.SetColor(vertex, Color::kBlack);
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
IteratorRange<EdgeIterator> Graph::GetOutgoingEdges(Vertex vertex) const {
  return {outgoing_edges_[vertex].begin(), outgoing_edges_[vertex].end()};
}

Color Colormap::GetColor(Vertex vertex) const {
  return colormap_[vertex];
}

void Colormap::SetColor(Vertex vertex, Color color) {
  colormap_[vertex] = color;
}

void CutpointDFSVisitor::StartVertex(Vertex vertex) {
  parent[vertex] = -1;
}

void CutpointDFSVisitor::DiscoverVertex(Vertex vertex) {
  time_in[vertex] = timer++;
  min_back_time_in[vertex] = time_in[vertex];
}

void CutpointDFSVisitor::ExamineEdge(const Edge& edge) {
  if (parent[edge.destination] == -2) {
    parent[edge.destination] = edge.source;
  }
} 

void CutpointDFSVisitor::TreeEdge(const Edge& edge) {
  min_back_time_in[edge.source] \
    = std::min(min_back_time_in[edge.source], min_back_time_in[edge.destination]);
  if (min_back_time_in[edge.destination] >= time_in[edge.source] && parent[edge.source] != -1) {
    cutpoints.insert(edge.source);
  }
  ++children[edge.source];
}

void CutpointDFSVisitor::BackEdge(const Edge& edge) {
  if (parent[edge.source] != edge.destination) {
    min_back_time_in[edge.source] \
      = std::min(min_back_time_in[edge.source], time_in[edge.destination]);
  }
}

void CutpointDFSVisitor::ForwardOrCrossEdge(const Edge& edge) {
  min_back_time_in[edge.source] \
    = std::min(min_back_time_in[edge.source], time_in[edge.destination]);
}

void CutpointDFSVisitor::FinishVertex(Vertex vertex) {
  if (parent[vertex] == -1 && children[vertex] > 1) {
    cutpoints.insert(vertex);
  }
}
