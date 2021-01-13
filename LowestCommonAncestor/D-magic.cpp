#include <algorithm>
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <set>

using Edge = std::pair<int, int>;

using Graph = std::vector<std::vector<int>>;

class BridgesFinder {
public:
  explicit BridgesFinder(const Graph& graph) : graph(graph) {
    fup.resize(graph.size());
    used.resize(graph.size(), false);
    time_in.resize(graph.size());
    time_out.resize(graph.size());
  }

  void Initialize();
  std::set<Edge> GetBridges() const;

private:
  void Dfs(int from, int parent);

  Graph graph;

  int timer;
  std::vector<int> fup;
  std::vector<bool> used;
  std::vector<int> time_in, time_out;

  std::set<Edge> bridges;
};

class DisjointSetUnion {
public:
  explicit DisjointSetUnion(int n_vertices) : n_vertices(n_vertices) {
    parent.resize(n_vertices);
    rank.resize(n_vertices);
  }

  void Initialize();
  int FindSet(int vertex);
  void UnionSets(int first, int second);

private:
  int n_vertices;
  std::vector<int> parent;
  std::vector<int> rank;
};

class ComponentsBuilder {
public:
  explicit ComponentsBuilder(const Graph& graph) :
    graph(graph), disjoint_set_union(graph.size()) {
    components.resize(graph.size());
  }

  void Initialize(const std::set<Edge>& bridges);
  std::vector<int> GetComponents() const;

private:
  Graph graph;

  std::vector<int> components;

  DisjointSetUnion disjoint_set_union;
};

class LcaComputer {
public:
  explicit LcaComputer(const Graph& graph) : graph(graph) {
    up.resize(graph.size());
    depth.resize(graph.size());
    time_in.resize(graph.size());
    time_out.resize(graph.size());
  }

  void Initialize(int root);
  int Lca(int first, int second) const;
  int LcaDepth(int first, int second) const;

private:
  void Dfs(int from, int parent);
  bool IsAncestor(int first, int second) const;

  Graph graph;

  int n_levels = 1;
  std::vector<int> depth;

  int timer;
  std::vector<int> time_in, time_out;
  std::vector<std::vector<int>> up;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::freopen("magic.in", "r", stdin);
  std::freopen("magic.out", "w", stdout);

  int n_vertices, n_edges, capital;
  std::cin >> n_vertices >> n_edges >> capital;
  --capital;

  Graph graph(n_vertices);
  for (int edge = 0; edge < n_edges; ++edge) {
    int first, second;
    std::cin >> first >> second;
    --first, --second;
    graph[first].push_back(second);
    graph[second].push_back(first);
  }

  BridgesFinder bridges_finder(graph);
  bridges_finder.Initialize();
  auto bridges = bridges_finder.GetBridges();

  ComponentsBuilder components_builder(graph);
  components_builder.Initialize(bridges);
  auto components = components_builder.GetComponents();

  Graph tree(n_vertices);
  for (auto bridge: bridges) {
    // vertex adjacent component
    const int first = components[bridge.first];
    const int second = components[bridge.second];
    tree[first].push_back(second);
    tree[second].push_back(first);
  }

  // vertex adjacent component
  capital = components[capital];

  LcaComputer lca_computer(tree);
  lca_computer.Initialize(capital);

  int n_queries;
  std::cin >> n_queries;

  for (int query = 0; query < n_queries; ++query) {
    int first, second;
    std::cin >> first >> second;
    --first, --second;

    // vertex adjacent component
    first = components[first];
    second = components[second];

    std::cout << lca_computer.LcaDepth(first, second) << "\n";
  }

  return 0;
}

void BridgesFinder::Initialize() {
  timer = 0;
  Dfs(0, -1);
}

std::set<Edge> BridgesFinder::GetBridges() const {
  return bridges;
}

void BridgesFinder::Dfs(int from, int parent) {
  used[from] = true;

  time_in[from] = fup[from] = timer++;

  for (int adjacent: graph[from]) {
    if (adjacent != parent) {
      if (used[adjacent]) {
        fup[from] = std::min(fup[from], time_in[adjacent]);
      } else {
        Dfs(adjacent, from);
        fup[from] = std::min(fup[from], fup[adjacent]);
        if (fup[adjacent] > time_in[from]) {
          bridges.emplace(from, adjacent);
        }
      }
    }
  }
}

void DisjointSetUnion::Initialize() {
  for (int vertex = 0; vertex < n_vertices; ++vertex) {
    parent[vertex] = vertex;
  }
}

int DisjointSetUnion::FindSet(int vertex) {
  if (vertex == parent[vertex]) {
    return vertex;
  } else {
    parent[vertex] = FindSet(parent[vertex]);
    return parent[vertex];
  }
}

void DisjointSetUnion::UnionSets(int first, int second) {
  first = FindSet(first);
  second = FindSet(second);
  if (first != second) {
    if (rank[first] < rank[second]) {
      std::swap(first, second);
    }
    parent[second] = first;
    if (rank[first] == rank[second]) {
      ++rank[first];
    }
  }
}

void ComponentsBuilder::Initialize(const std::set<Edge>& bridges) {
  disjoint_set_union.Initialize();
  const int vertex_count = graph.size();
  for (size_t vertex = 0; vertex < vertex_count; ++vertex) {
    for (int adjacent : graph[vertex]) {
      if (bridges.find(std::make_pair(vertex, adjacent)) == bridges.end() &&
          bridges.find(std::make_pair(adjacent, vertex)) == bridges.end()) {
        disjoint_set_union.UnionSets(vertex, adjacent);
      }
    }
  }
  for (size_t vertex = 0; vertex < vertex_count; ++vertex) {
    components[vertex] = disjoint_set_union.FindSet(vertex);
  }
}

std::vector<int> ComponentsBuilder::GetComponents() const {
  return components;
}

void LcaComputer::Initialize(int root) {
  timer = 0;
  while ((1 << n_levels) <= static_cast<int>(graph.size())) {
    ++n_levels;
  }
  for (size_t vertex = 0; vertex < graph.size(); ++vertex) {
    up[vertex].resize(n_levels + 1);
  }
  depth[root] = -1;
  Dfs(root, root);
}

int LcaComputer::Lca(int first, int second) const {
  if (IsAncestor(first, second)) {
    return first;
  } else if (IsAncestor(second, first)) {
    return second;
  } else {
    for (int level = n_levels; level >= 0; --level) {
      if (!IsAncestor(up[first][level], second)) {
        first = up[first][level];
      }
    }
    return up[first][0];
  }
}


int LcaComputer::LcaDepth(int first, int second) const {
  return depth[Lca(first, second)];
}

void LcaComputer::Dfs(int vertex, int parent) {
  depth[vertex] = depth[parent] + 1;
  ++timer;
  time_in[vertex] = timer;
  up[vertex][0] = parent;
  for (int level = 1; level <= n_levels; ++level) {
    up[vertex][level] = up[up[vertex][level - 1]][level - 1];
  }
  for (int adjacent : graph[vertex]) {
    if (adjacent != parent) {
      Dfs(adjacent, vertex);
    }
  }
  ++timer;
  time_out[vertex] = timer;
}

bool LcaComputer::IsAncestor(int first, int second) const {
  return time_in[first] <= time_in[second] \
    && time_out[first] >= time_out[second];
}
