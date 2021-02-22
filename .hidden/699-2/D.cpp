#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int testcase_count;
  std::cin >> testcase_count;
  while (testcase_count --> 0) {
    int vertex_count, path_length;
    std::cin >> vertex_count >> path_length;
    std::vector<std::string> edge_label_matrix(vertex_count);
    for (auto& edge_label_row : edge_label_matrix) {
      std::cin >> edge_label_row;
    }

    auto print_cyclic_path = [&] (const std::vector<int>& cycle) -> void {
      if (cycle.empty()) {
        std::cout << "NO\n";
      } else {
        std::cout << "YES\n";
        const int cycle_length = cycle.size();
        for (int i = 0; i <= path_length; ++i) {
          std::cout << cycle[i % cycle_length] + 1 << " ";
        }
        std::cout << "\n";
      }
    };

    if (path_length & 1) {  // odd
      print_cyclic_path({0, 1});
    } else {  // even
      bool found = false;
      for (int u = 0; u < vertex_count && !found; ++u) {
        for (int v = 0; v < u && !found; ++v) {
          if (edge_label_matrix[u][v] == edge_label_matrix[v][u]) {
            found = true;
            print_cyclic_path({u, v});
          }
        }
      }
      if (!found) {
        if (vertex_count == 2) {
          print_cyclic_path({});
        } else {
          const int half_length = path_length >> 1;
          std::vector<int> permutation({0, 1, 2});
          do {
            if (edge_label_matrix[permutation[0]][permutation[1]] == \
                edge_label_matrix[permutation[1]][permutation[2]]) {
              found = true;
            }
          } while (!found && std::next_permutation(permutation.begin(), permutation.end()));
          if (half_length & 1) {  // odd
            print_cyclic_path({permutation[0], permutation[1], permutation[2], permutation[1]});
          } else {  // even
            print_cyclic_path({permutation[1], permutation[2], permutation[1], permutation[0]});
          }
        }
      }
    }
  }

  return 0;
}
