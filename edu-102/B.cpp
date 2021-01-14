#include <iostream>
#include <string>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int query_count;
  std::cin >> query_count;
  while (query_count --> 0) {
    bool lca_exists = true;
    std::string first, second, lca;
    std::cin >> first >> second;

    const int first_length = first.length(), second_length = second.length();
    int first_index = 0, second_index = 0;

    do {
      lca_exists &= first[first_index] == second[second_index];
      lca += first[first_index];
      first_index = (first_index + 1) % first_length;
      second_index = (second_index + 1) % second_length;
    } while (lca_exists && (first_index || second_index));

    if (lca_exists) {
      std::cout << lca << "\n";
    } else {
      std::cout << -1 << "\n";
    }
  }

  return 0;
}
