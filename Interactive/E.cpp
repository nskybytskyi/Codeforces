#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

int ask(int first_vertex, int second_vertex) {
  std::cout << "?" << " " << first_vertex + 1 << " " << second_vertex + 1 << std::endl << std::flush;
  std::cout.flush();

  int lca;
  std::cin >> lca;
  --lca;
  return lca;
}

void answer(int root) {
  std::cout << "!" << " " << root + 1 << std::endl << std::flush;
  std::cout.flush();
  exit(0);
}

int main() {
  int vertex_count;
  std::cin >> vertex_count;

  std::vector<std::unordered_set<int>> graph(vertex_count);
  for (int edge_id = 0; edge_id < vertex_count - 1; ++edge_id) {
    int first_vertex, second_vertex;
    std::cin >> first_vertex >> second_vertex;
    --first_vertex, --second_vertex;

    graph[first_vertex].insert(second_vertex);
    graph[second_vertex].insert(first_vertex);
  }

  std::set<int> leaves;
  for (int first_leaf = 0; first_leaf < vertex_count; ++first_leaf) {
    if (graph[first_leaf].size() == 1) {
      leaves.insert(first_leaf);
    }
  }

  for (int query = 0; query < vertex_count / 2; ++query) {
    int first_leaf = *leaves.begin();
    leaves.erase(leaves.begin());

    int second_leaf = *leaves.begin();
    leaves.erase(leaves.begin());

    auto lca = ask(first_leaf, second_leaf);

    if (lca == first_leaf) {
      answer(first_leaf);
    } else if (lca == second_leaf) {
      answer(second_leaf);
    } else {
      for (auto neighbour : graph[first_leaf]) {
        graph[neighbour].erase(first_leaf);
        if (graph[neighbour].size() == 1) {
          leaves.insert(neighbour);
        }
      }

      for (auto neighbour : graph[second_leaf]) {
        graph[neighbour].erase(second_leaf);
        if (graph[neighbour].size() == 1) {
          leaves.insert(neighbour);
        }
      }
    }
  }

  auto root = *leaves.begin();
  answer(root);

  return 0;
}
