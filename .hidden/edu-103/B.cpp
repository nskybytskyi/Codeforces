#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int testcase_count;
  std::cin >> testcase_count;
  while (testcase_count --> 0) {
    int64_t months_count, max_inflation_percent;
    std::cin >> months_count >> max_inflation_percent;
    std::vector<int64_t> price_changes(months_count);
    for (auto& price_change : price_changes) {
      std::cin >> price_change;
    }

    std::vector<int64_t> prices(months_count);
    std::partial_sum(price_changes.begin(), price_changes.end(), prices.begin());

    int64_t answer = 0;
    for (int index = 1; index < months_count; ++index) {
      answer = std::max(answer, 
        (100 * price_changes[index]
          - max_inflation_percent * prices[index - 1]
            + max_inflation_percent - 1)
              / max_inflation_percent);
    }
    std::cout << answer << "\n";
  }

  return 0;
}
