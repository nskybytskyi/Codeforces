#include <iostream>
#include <deque>
#include <utility>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int testcase_count;
  std::cin >> testcase_count;
  while (testcase_count --> 0) {
    int array_length, divisor;
    std::cin >> array_length >> divisor;
    std::deque<std::pair<int, int>> array(array_length);
    for (auto& [element, count] : array) {
      std::cin >> element;
      count = 1;
    }

    int64_t elements_sum = 0;
    while (!array.empty()) {
      auto [element, count] = array.front();
      array.pop_front();
      elements_sum += element * count;
      if (element % divisor == 0) {
        array.emplace_back(element / divisor, count * divisor);
      } else {
        break;
      }
    }
    for (auto [element, count] : array) {
      elements_sum += element * count;
    }
    std::cout << elements_sum << "\n";
  }

  return 0;
}
