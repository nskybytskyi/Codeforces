#include <algorithm>
#include <iostream>
#include <string>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int testcase_count;
  std::cin >> testcase_count;
  while (testcase_count --> 0) {
    int planet_x, planet_y;
    std::string orders;
    std::cin >> planet_x >> planet_y >> orders;
    if (-std::count(orders.begin(), orders.end(), 'L') <= planet_x &&
        planet_x <= std::count(orders.begin(), orders.end(), 'R') &&
        -std::count(orders.begin(), orders.end(), 'D') <= planet_y &&
        planet_y <= std::count(orders.begin(), orders.end(), 'U')) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
    }
  }

  return 0;
}
