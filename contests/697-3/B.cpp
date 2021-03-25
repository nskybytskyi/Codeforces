#include <iostream>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int t;
  std::cin >> t;
  while (t --> 0) {
    int n;
    std::cin >> n;

    std::cout << ((n % 2020) * 2021 <= n ? "YES" : "NO") << "\n";
  }

  return 0;
}
