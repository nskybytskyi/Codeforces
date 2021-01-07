#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("lepus.in", "r", stdin);
  std::freopen("lepus.out", "w", stdout);

  int cells_count;
  std::string cells_description;
  std::cin >> cells_count >> cells_description;

  const char kSwamp = 'w';
  const char kEmpty = '.';
  const char kGrass = '"';

  std::vector<int> best_score_on_prefix(cells_count, -1);
  best_score_on_prefix[0] = 0;
  for (int cell = 1; cell < cells_count; ++cell) {
    if (cells_description[cell] != kSwamp) {
      const int cell_score = cells_description[cell] == kGrass;
      if (best_score_on_prefix[cell - 1] != -1) {
        best_score_on_prefix[cell] = std::max(best_score_on_prefix[cell],
          best_score_on_prefix[cell - 1] + cell_score);
      }
      if (3 <= cell && best_score_on_prefix[cell - 3] != -1) {
        best_score_on_prefix[cell] = std::max(best_score_on_prefix[cell],
          best_score_on_prefix[cell - 3] + cell_score);
      }
      if (5 <= cell && best_score_on_prefix[cell - 5] != -1) {
        best_score_on_prefix[cell] = std::max(best_score_on_prefix[cell],
          best_score_on_prefix[cell - 5] + cell_score);
      }
    }
  }

  std::cout << best_score_on_prefix[cells_count - 1];

  return 0;
}
