#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("stupid_rmq.in", "r", stdin);
  std::freopen("stupid_rmq.out", "w", stdout);

  int array_size;
  std::cin >> array_size;
  std::vector<int> array(array_size);
  for (auto& element : array) {
    std::cin >> element;
  }

  int query_count;
  std::cin >> query_count;
  while (query_count --> 0) {
    int left, right;
    std::cin >> left >> right;
    const auto left_it = std::next(array.begin(), left - 1);
    const auto right_it = std::next(array.begin(), right);
    std::cout << *std::min_element(left_it, right_it) << "\n";
  }

  return 0;
}
