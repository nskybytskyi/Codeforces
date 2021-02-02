#include <iostream>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int testcase_count;
  std::cin >> testcase_count;
  while (testcase_count --> 0) {
    int length, maximum;
    std::cin >> length >> maximum;

    const int last = 2 * maximum - length;

    for (int index = 1; index < last; ++index) {
      std::cout << index << " ";
    }

    for (int index = maximum; index >= last; --index) {
      std::cout << index << " ";
    }

    std::cout << "\n";
  }

  return 0;
}
