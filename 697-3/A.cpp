#include <iostream>

bool is_power_of_two(int64_t n) {
  while (n % 2 == 0) {
    n >>= 1;
  }
  return n == 1;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int t;
  std::cin >> t;
  while (t --> 0) {
    int64_t n;
    std::cin >> n;

    // n has odd divisior iff it is not a power of 2
    std::cout << (is_power_of_two(n) ? "NO" : "YES") << "\n";
  }

  return 0;
}
