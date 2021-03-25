#include <iostream>
#include <string>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int testcase_count;
  std::cin >> testcase_count;
  while (testcase_count --> 0) {
    int city_count;
    std::string initial_roads;
    std::cin >> city_count >> initial_roads;
    ++city_count;

    std::vector<std::vector<int>> prev(2, std::vector<int>(city_count));
    for (int index = 1; index < city_count; ++index) {
      if (initial_roads[index - 1] == 'L') {
        if (index > 1 && initial_roads[index - 2] == 'R') {
          prev[0][index] = prev[1][index - 1];
        } else {
          prev[0][index] = index - 1;
        }
      } else {
        prev[0][index] = index;
      }
      if (initial_roads[index - 1] == 'R') {
        if (index > 1 && initial_roads[index - 2] == 'L') {
          prev[1][index] = prev[0][index - 1];
        } else {
          prev[1][index] = index - 1;
        }
      } else {
        prev[1][index] = index;
      }
    }

    std::vector<std::vector<int>> next(2, std::vector<int>(city_count));
    next[0][city_count - 1] = next[1][city_count - 1] = city_count - 1;
    for (int index = city_count - 2; index >= 0; --index) {
      if (initial_roads[index] == 'R') {
        if (index + 2 < city_count && initial_roads[index + 1] == 'L') {
          next[0][index] = next[1][index + 1];
        } else {
          next[0][index] = index + 1;
        }
      } else {
        next[0][index] = index;
      }
      if (initial_roads[index] == 'L') {
        if (index + 2 < city_count && initial_roads[index + 1] == 'R') {
          next[1][index] = next[0][index + 1];
        } else {
          next[1][index] = index + 1;
        }
      } else {
        next[1][index] = index;
      }
    }

    for (int index = 0; index < city_count; ++index) {
      std::cout << next[0][index] + 1 - prev[0][index] << " ";
    }
    std::cout << "\n";
  }

  return 0;
}
