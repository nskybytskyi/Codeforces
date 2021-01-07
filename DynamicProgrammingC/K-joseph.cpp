#include <iostream>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("joseph.in", "r", stdin);
  std::freopen("joseph.out", "w", stdout);

  int children_count, step;
  std::cin >> children_count >> step;

  int last_child_standing = 0;
  for (int iteration = 1; iteration <= children_count; ++iteration) {
    last_child_standing = (last_child_standing + step) % iteration;
  }

  std::cout << last_child_standing + 1;

  return 0;
}
