#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int testcase_count;
  std::cin >> testcase_count;
  while (testcase_count --> 0) {
    int planks_counts, painters_count;
    std::cin >> planks_counts >> painters_count;

    std::vector<int> initial_colors(planks_counts);
    for (auto& initial_color : initial_colors) {
      std::cin >> initial_color;
    }

    std::vector<int> desired_colors(planks_counts);
    for (auto& desired_color : desired_colors) {
      std::cin >> desired_color;
    }

    std::vector<int> painters_colors(painters_count);
    for (auto& painter_color : painters_colors) {
      std::cin >> painter_color;
    }

    std::map<int, std::vector<int>> mismatch_positions;
    for (int plank = 0; plank < planks_counts; ++plank) {
      if (desired_colors[plank] != initial_colors[plank]) {
        mismatch_positions[desired_colors[plank]].push_back(plank);
      }
    }

    int last = -1, last_color = painters_colors.back();
    if (!mismatch_positions[last_color].empty()) {
      last = mismatch_positions[last_color].back();
      mismatch_positions[last_color].pop_back();
      painters_colors.pop_back();
    } else {
      for (int plank = 0; plank < planks_counts && last == -1; ++plank) {
        if (last_color == desired_colors[plank]) {
          last = plank;
          painters_colors.pop_back();
        }
      }
    }

    if (last == -1) {
      std::cout << "NO\n";
    } else {
      std::vector<int> orders = {last};
      std::reverse(painters_colors.begin(), painters_colors.end());
      for (auto painter_color : painters_colors) {
        if (!mismatch_positions[painter_color].empty()) {
          orders.push_back(mismatch_positions[painter_color].back());
          mismatch_positions[painter_color].pop_back();
        } else {
          orders.push_back(last);
        }
      }

      bool possible = true;
      for (const auto& [color, positions] : mismatch_positions) {
        if (!positions.empty()) {
          possible = false;
        }
      }

      if (!possible) {
        std::cout << "NO\n";
      } else {
        std::reverse(orders.begin(), orders.end());
        std::cout << "YES\n";
        for (auto order : orders) {
          std::cout << order + 1 << " ";
        }
        std::cout << "\n";
      }
    }
  }

  return 0;
}
