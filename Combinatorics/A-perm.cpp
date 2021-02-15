#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("perm.in", "r", stdin);
  std::freopen("perm.out", "w", stdout);

  int length;
  std::cin >> length;

  std::vector<int> permutation(length);
  std::iota(permutation.begin(), permutation.end(), 1);

  do {
    for (auto element : permutation) {
      std::cout << element << " ";
    }
    std::cout << "\n";
  } while (std::next_permutation(permutation.begin(), permutation.end()));

  return 0;
}
