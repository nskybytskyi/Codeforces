/* INPUT
6 6
1
1 2
2 3
3 4
4 2
4 5
3 6
2
5 6
6 6
->
1
2
*/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <set>

typedef std::pair<int, int> Edge;

typedef std::vector<std::vector<int>> Graph;

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
        depth.resize(graph.size());  // problem-specific
        time_in.resize(graph.size());
        time_out.resize(graph.size());
    }

    void Initialize(int root);
    int Lca(int first, int second) const;
    int LcaDepth(int first, int second) const;  // problem-specific

private:
    void Dfs(int from, int parent);
    bool Upper(int first, int second) const;

    Graph graph;

    int n_levels = 1;
    std::vector<int> depth;  // problem-specific

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
        --first;
        --second;
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
        // vertex to component
        int first = components[bridge.first], second = components[bridge.second];
        tree[first].push_back(second);
        tree[second].push_back(first);
    }

    // // Debug
    // for (int vertex = 0; vertex < n_vertices; ++vertex) {
    //     std::cout << vertex << ": ";
    //     for (int to: tree[vertex]) {
    //         std::cout << to << ", ";
    //     }
    //     std::cout << "\n";
    // }

    // vertex to component
    capital = components[capital];

    LcaComputer lca_computer(tree);
    lca_computer.Initialize(capital);

    int n_queries;
    std::cin >> n_queries;

    for (int query = 0; query < n_queries; ++query) {
        int first, second;
        std::cin >> first >> second;
        --first;
        --second;

        // vertex to component
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

    time_in[from] = timer;
    fup[from] = timer;
    ++timer;

    for (int to: graph[from]) {
        if (to != parent) {
            if (used[to]) {
                fup[from] = std::min(fup[from], time_in[to]);
            } else {
                Dfs(to, from);
                fup[from] = std::min(fup[from], fup[to]);
                if (fup[to] > time_in[from]) {
                    bridges.insert(std::make_pair(from, to));
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
    for (int from = 0; from < static_cast<int>(graph.size()); ++from) {
        for (int to: graph[from]) {
            if (bridges.find(std::make_pair(from, to)) == bridges.end() &&
                bridges.find(std::make_pair(to, from)) == bridges.end()) {
                disjoint_set_union.UnionSets(from, to);
            }
        }
    }
    for (int from = 0; from < static_cast<int>(graph.size()); ++from) {
        components[from] = disjoint_set_union.FindSet(from);
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
    depth[root] = -1;  // problem-specific
    Dfs(root, root);
}

int LcaComputer::Lca(int first, int second) const {
    if (Upper(first, second)) {
        return first;
    } else if (Upper(second, first)) {
        return second;
    } else {
        for (int level = n_levels; level >= 0; --level) {
            if (!Upper(up[first][level], second)) {
                first = up[first][level];
            }
        }
        return up[first][0];
    }
}

// problem-specific
int LcaComputer::LcaDepth(int first, int second) const {
    return depth[Lca(first, second)];
}

void LcaComputer::Dfs(int from, int parent) {
    depth[from] = depth[parent] + 1;  // problem-specific
    ++timer;
    time_in[from] = timer;
    up[from][0] = parent;
    for (int level = 1; level <= n_levels; ++level) {
        up[from][level] = up[up[from][level - 1]][level - 1];
    }
    for (int to: graph[from]) {
        if (to != parent) {
            Dfs(to, from);
        }
    }
    ++timer;
    time_out[from] = timer;
}

bool LcaComputer::Upper(int first, int second) const {
    return time_in[first] <= time_in[second] && time_out[first] >= time_out[second];
}
