#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("inverse.in", "r", stdin);
  std::freopen("inverse.out", "w", stdout);

  int length;
  std::cin >> length;

  std::vector<int> permutation(length);
  for (auto& element : permutation) {
    std::cin >> element;
  }

  std::vector<int> inverse(length);
  for (int index = 0; index < length; ++index) {
    inverse[permutation[index] - 1] = index + 1;
  }

  for (auto& element : inverse) {
    std::cout << element << " ";
  }
  std::cout << "\n";

  return 0;
}
