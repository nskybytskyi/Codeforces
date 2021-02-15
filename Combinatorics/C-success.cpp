#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("success.in", "r", stdin);
  std::freopen("success.out", "w", stdout);

  int length;
  std::cin >> length;

  std::vector<int> permutation(length);
  for (auto& element : permutation) {
    std::cin >> element;
  }

  std::next_permutation(permutation.begin(), permutation.end());

  for (auto& element : permutation) {
    std::cout << element << " ";
  }
  std::cout << "\n";

  return 0;
}
