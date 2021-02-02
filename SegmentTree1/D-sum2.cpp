#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("sum2.in", "r", stdin);
  std::freopen("sum2.out", "w", stdout);

  int array_size;
  std::cin >> array_size;
  std::vector<int64_t> array(array_size);
  for (auto& element : array) {
    std::cin >> element;
  }

  std::vector<int64_t> prefix_sums = {0};
  std::partial_sum(array.begin(), array.end(), std::back_inserter(prefix_sums));

  int query_count;
  std::cin >> query_count;
  while (query_count --> 0) {
    int left, right;
    std::cin >> left >> right;
    std::cout << prefix_sums[right] - prefix_sums[left - 1] << "\n";
  }

  return 0;
}
