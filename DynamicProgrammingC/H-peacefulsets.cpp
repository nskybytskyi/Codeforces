#include <iostream>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("peacefulsets.in", "r", stdin);
  std::freopen("peacefulsets.out", "w", stdout);
 
  int strength;
  std::cin >> strength;

  std::vector<std::vector<int>> dp(12, std::vector<int>(strength + 1));
  dp[0][0] = 1;

  for (int subset_strength = 1; subset_strength <= strength; ++subset_strength) {
    for (int i = 0, power = 1;
         i < 12 && power <= subset_strength;
         ++i, power = (power << 1) | 1) {
      for (int j = 0; j <= i; ++j) {
        dp[i][subset_strength] += dp[j][subset_strength - power];
      }
    }
  }

  int64_t answer = 0;
  for (int i = 0; i < 12; ++i) {
    answer += dp[i][strength];
  }
  std::cout << answer << "\n";

  return 0;
}
