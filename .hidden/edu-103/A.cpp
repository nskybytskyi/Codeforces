#include <iostream>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int testcase_count;
  std::cin >> testcase_count;
  while (testcase_count --> 0) {
    int64_t array_size, divisor;
    std::cin >> array_size >> divisor;
    int64_t minimum_sum = ((array_size + divisor - 1) / divisor) * divisor;
    std::cout << (minimum_sum + array_size - 1) / array_size << "\n";
  }

  return 0;
}
