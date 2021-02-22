#include <iostream>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int testcase_count;
  std::cin >> testcase_count;
  while (testcase_count --> 0) {
    int mountains_count, boulders_count;
    std::cin >> mountains_count >> boulders_count;
    std::vector<int> mountain_heights(mountains_count);
    for (auto& mountain_height : mountain_heights) {
      std::cin >> mountain_height;
    }
    int last_position = 0;
    while (boulders_count --> 0 &&
           last_position != mountains_count - 1) {
      int position = 0;
      while (position + 1 < mountains_count &&
             mountain_heights[position] >= mountain_heights[position + 1]) {
        ++position;
      }
      if (position + 1 < mountains_count) {
        ++mountain_heights[position];
      }
      last_position = position;
    }
    if (last_position == mountains_count - 1) {
      std::cout << -1 << "\n";
    } else {
      std::cout << last_position + 1 << "\n";
    }
  }

  return 0;
}
