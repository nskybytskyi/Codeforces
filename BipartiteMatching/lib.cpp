// cl /c /EHsc /Ox /std:c++17 lib.cpp

#include <functional>
#include <limits>
#include <numeric>
#include <queue>
#include <utility>
#include <vector>


class BipartiteGraph {
  public:
    BipartiteGraph(std::pair<int, int> sizes) : sizes_(sizes) {
      edges_.first.resize(sizes_.first);
      nodes_.first.resize(sizes_.first);
      std::iota(nodes_.first.begin(), nodes_.first.end(), 0);

      edges_.second.resize(sizes_.second);
      nodes_.second.resize(sizes_.second);
      std::iota(nodes_.second.begin(), nodes_.second.end(), 0);
    }

    void AddEdge(std::pair<int, int> edge) {
      edges_.first[edge.first].push_back(edge.second);
      edges_.second[edge.second].push_back(edge.first);
    }

    std::pair<int, int> GetSizes() const {
      return sizes_;
    }

    std::pair<std::vector<int>, std::vector<int>> GetNodes() const {
      return nodes_;
    }

    std::vector<int> GetEdges(int node, bool part) const {
      if (part) {
        return edges_.second[node];
      } else {
        return edges_.first[node];
      }
    }

  private:
    std::pair<int, int> sizes_;
    std::pair<std::vector<int>, std::vector<int>> nodes_;
    std::pair<std::vector<std::vector<int>>,
              std::vector<std::vector<int>>> edges_;
};

class BipartiteMatching {
  public:
    static const int kNoMatch;

    BipartiteMatching(std::pair<int, int> capacities) {
      matches_.first.resize(capacities.first, kNoMatch);
      matches_.second.resize(capacities.second, kNoMatch);
    }

    int Get(int node, bool part) const {
      if (part) {
        return matches_.second[node];
      } else {
        return matches_.first[node];
      }
    }

    void Set(std::pair<int, int> edge) {
      if (matches_.first[edge.first] == kNoMatch) {
        ++size_;
      }
      matches_.first[edge.first] = edge.second;
      matches_.second[edge.second] = edge.first;
    }

    int Size() const {
      return size_;
    }

  private:
    int size_ = 0;
    std::pair<std::vector<int>, std::vector<int>> matches_;
};

const int BipartiteMatching::kNoMatch = -1;


BipartiteMatching Kuhn(const BipartiteGraph& bipartite_graph) {
  BipartiteMatching bipartite_matching(bipartite_graph.GetSizes());
  std::vector<bool> used(bipartite_graph.GetSizes().first);

  std::function<bool(int)> try_kuhn = [&] (int node) -> bool {
    if (used[node]) {
      return false;
    } else {
      used[node] = true;
      for (auto adjacent : bipartite_graph.GetEdges(node, false)) {
        auto next_node = bipartite_matching.Get(adjacent, true);
        if (next_node == BipartiteMatching::kNoMatch || try_kuhn(next_node)) {
          bipartite_matching.Set({node, adjacent});
          return true;
        }
      }
      return false;
    }
  };

  for (auto node : bipartite_graph.GetNodes().first) {
    if (try_kuhn(node)) {
      used.assign(used.size(), false);
    }
  }

  return bipartite_matching;
}


BipartiteMatching HopcroftKarp(const BipartiteGraph& bipartite_graph) {
  BipartiteMatching bipartite_matching(bipartite_graph.GetSizes());
  const int kNoMatchNode = bipartite_graph.GetSizes().first;
  const int64_t kUnreachable = std::numeric_limits<int64_t>::max();
  std::vector<int64_t> distance(bipartite_graph.GetSizes().first + 1);

  auto try_bfs = [&] () -> bool {
    distance.assign(distance.size(), kUnreachable);
    std::deque<int> bfs;
    for (auto node : bipartite_graph.GetNodes().first) {
      if (bipartite_matching.Get(node, false) == BipartiteMatching::kNoMatch) {
        distance[node] = 0;
        bfs.push_back(node);
      }
    }

    while (!bfs.empty()) {
      auto node = bfs.front();
      bfs.pop_front();
      if (distance[node] < distance[kNoMatchNode]) {
        for (auto adjacent : bipartite_graph.GetEdges(node, false)) {
          auto next_node = bipartite_matching.Get(adjacent, true);
          if (next_node == BipartiteMatching::kNoMatch) {
            next_node = kNoMatchNode;
          } 
          if (distance[next_node] == kUnreachable) {
            distance[next_node] = distance[node] + 1;
            bfs.push_back(next_node);
          }
        }
      }
    }

    return distance[kNoMatchNode] < kUnreachable;
  };

  std::function<bool(int)> dfs = [&] (int node) -> bool {
    if (node != kNoMatchNode) {
      for (auto adjacent : bipartite_graph.GetEdges(node, false)) {
        auto next_node = bipartite_matching.Get(adjacent, true);
        if (next_node == BipartiteMatching::kNoMatch) {
          next_node = kNoMatchNode;
        }
        if (distance[next_node] == distance[node] + 1 && dfs(next_node)) {
          bipartite_matching.Set({node, adjacent});
          return true;
        }
      }
      distance[node] = kUnreachable;
      return false;
    }
    return true;
  };

  while (try_bfs()) {
    for (auto node : bipartite_graph.GetNodes().first) {
      if (bipartite_matching.Get(node, false) == BipartiteMatching::kNoMatch) {
        dfs(node);
      }
    }
  }
  return bipartite_matching;
}
