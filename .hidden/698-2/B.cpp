#include <iostream>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int testcase_count;
  std::cin >> testcase_count;
  while (testcase_count --> 0) {
    int queries_count, lucky_digit;
    std::cin >> queries_count >> lucky_digit;
    const int bound = 10 * lucky_digit;
    std::vector<int> lucky_sum(bound);
    lucky_sum[0] = true;
    for (int i = 1; i < bound; ++i) {
      for (int j = lucky_digit; j <= i; j += 10) {
        if (lucky_sum[i - j]) {
          lucky_sum[i] = true;
        }
      }
    }
    while (queries_count --> 0) {
      int query;
      std::cin >> query;
      if (query >= bound) {
        std::cout << "YES\n";
      } else if (lucky_sum[query]) {
        std::cout << "YES\n";
      } else {
        std::cout << "NO\n"; 
      }
    }
  }

  return 0;
}
