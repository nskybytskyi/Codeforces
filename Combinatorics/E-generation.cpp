#include <algorithm>
#include <iostream>
#include <string>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("generation.in", "r", stdin);
  std::freopen("generation.out", "w", stdout);

  int length, choose;
  std::cin >> length >> choose;

  std::string bitmask(choose, 1);
  bitmask.resize(length, 0);

  do {
    for (int index = 0; index < length; ++index) {
      if (bitmask[index]) {
        std::cout << length - index << " ";
      }
    }
    std::cout << "\n";
  } while (std::prev_permutation(bitmask.begin(), bitmask.end()));

  return 0;
}
