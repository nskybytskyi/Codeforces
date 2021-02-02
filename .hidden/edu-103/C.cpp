#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int testcase_count;
  std::cin >> testcase_count;
  while (testcase_count --> 0) {
    int64_t chains_count;
    std::cin >> chains_count;

    std::vector<int64_t> chain_lengths(chains_count);
    for (auto& chain_length : chain_lengths) {
      std::cin >> chain_length;
    }
    std::vector<int64_t> first_parents(chains_count);
    for (auto& first_parent : first_parents) {
      std::cin >> first_parent;
    }
    std::vector<int64_t> last_parents(chains_count);
    for (auto& last_parent : last_parents) {
      std::cin >> last_parent;
    }

    std::vector<int64_t> dp(chains_count);
    for (int index = 1; index < chains_count; ++index) {
      const int64_t first_parent = first_parents[index];
      const int64_t last_parent = last_parents[index];
      const int64_t delta = std::abs(last_parent - first_parent);
      dp[index] = chain_lengths[index] + 1 + delta;
      if (first_parent != last_parent) {
        dp[index] = std::max(dp[index],
          dp[index - 1] + chain_lengths[index] + 1 - delta);
      }
    }

    // // debug
    // for (auto element : dp) {
    //   std::cout << element << " ";
    // }
    // std::cout << "\n";

    std::cout << *std::max_element(dp.begin(), dp.end()) << "\n";
  }

  return 0;
}
