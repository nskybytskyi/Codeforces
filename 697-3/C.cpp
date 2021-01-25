#include <iostream>
#include <vector>

inline int64_t choose_2(int64_t pairs_count) {
  return (pairs_count * (pairs_count - 1)) >> 1;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int t;
  std::cin >> t;
  while (t --> 0) {
    int64_t boys_count, girls_count, pairs_count;
    std::cin >> boys_count >> girls_count >> pairs_count;

    std::vector<int64_t> boy_degree(boys_count), girl_degree(girls_count);
    for (int i = 0, boy; i < pairs_count; ++i) {
      std::cin >> boy;
      ++boy_degree[boy - 1];
    }
    for (int i = 0, girl; i < pairs_count; ++i) {
      std::cin >> girl;
      ++girl_degree[girl - 1];
    }

    int64_t ways = choose_2(pairs_count);
    for (int i = 0; i < boys_count; ++i) {
      ways -= choose_2(boy_degree[i]);
    }
    for (int i = 0; i < girls_count; ++i) {
      ways -= choose_2(girl_degree[i]);
    }

    std::cout << ways << "\n";
  }

  return 0;
}
