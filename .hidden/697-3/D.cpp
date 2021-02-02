#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

template <typename T = int>
std::vector<T> ReadArray(int size = 0, std::istream& in_stream = std::cin);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int t;
  std::cin >> t;
  while (t --> 0) {
    int app_count, memory_to_free;
    std::cin >> app_count >> memory_to_free;

    auto app_memory = ReadArray(app_count);

    std::vector<int64_t> regular, important;
    for (int i = 0, importance; i < app_count; ++i) {
      std::cin >> importance;
      if (importance == 1) {
        regular.push_back(app_memory[i]);
      } else {  // importance == 2
        important.push_back(app_memory[i]);
      }
    }

    std::sort(regular.begin(), regular.end(), std::greater<>());
    std::sort(important.begin(), important.end(), std::greater<>());

    std::vector<int64_t> prefix_regular = {0}, prefix_important = {0};
    std::partial_sum(regular.begin(), regular.end(), std::back_inserter(prefix_regular));
    std::partial_sum(important.begin(), important.end(), std::back_inserter(prefix_important));

    int regular_count = regular.size(), important_count = important.size();
    int min_to_remove = 2 * app_count + 1;

    for (int i = 0; i <= important_count; ++i) {
      auto r_it = std::lower_bound(prefix_regular.begin(), prefix_regular.end(),
        memory_to_free - prefix_important[i]);
      int r = std::distance(prefix_regular.begin(), r_it);

      if (r <= regular_count) {
        min_to_remove = std::min(min_to_remove, 2 * i + r);
      }
    }

    std::cout << ((min_to_remove == 2 * app_count + 1) ? -1 : min_to_remove) << "\n";
  }

  return 0;
}

template <typename T>
std::vector<T> ReadArray(int size, std::istream& in_stream) {
  if (!size) {
    in_stream >> size;
  }
  std::vector<T> array(size);
  for (auto& element : array) {
    in_stream >> element;
  }
  return array;
}
