#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

template <typename T = int>
std::vector<T> ReadArray(int size = 0, std::istream& in_stream = std::cin);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("ladder.in", "r", stdin);
  std::freopen("ladder.out", "w", stdout);

  const int stairs_count;
  std::cin >> stairs_count;
  const auto stairs_scores = ReadArray(stairs_count);

  std::vector<int> best_score_on_prefix(stairs_count + 1, std::numeric_limits<int>::min());
  best_score_on_prefix[0] = 0;
  for (int stair = 1; stair <= stairs_count; ++stair) {
    best_score_on_prefix[stair] = std::max(best_score_on_prefix[stair],
      best_score_on_prefix[stair - 1] + stairs_scores[stair - 1]);
    if (2 <= stair) {
      best_score_on_prefix[stair] = std::max(best_score_on_prefix[stair],
        best_score_on_prefix[stair - 2] + stairs_scores[stair - 1]);
    }
  }

  std::cout << best_score_on_prefix[stairs_count];

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
