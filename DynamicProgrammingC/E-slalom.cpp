#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

template <typename T = int>
std::vector<T> ReadArray(int size = 0, std::istream& in_stream = std::cin);

template <typename T = int>
std::vector<std::vector<T>> ReadSlalom(int size = 0, std::istream& in_stream = std::cin);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  // std::freopen("slalom.in", "r", stdin);
  // std::freopen("slalom.out", "w", stdout);

  int slalom_size;
  std::cin >> slalom_size;
  const auto slalom = ReadSlalom(slalom_size);

  std::vector<std::vector<int>> best_score_to_entry(slalom_size);
  for (int row = 0; row < slalom_size; ++row) {
    best_score_to_entry[row].resize(row + 1, std::numeric_limits<int>::min());
  }
  best_score_to_entry[0][0] = slalom[0][0];

  for (int row = 1; row < slalom_size; ++row) {
    for (int column = 0; column <= row; ++column) {
      if (column < row) {
        best_score_to_entry[row][column] = std::max(best_score_to_entry[row][column],
          best_score_to_entry[row - 1][column] + slalom[row][column]);
      }
      if (column) {
        best_score_to_entry[row][column] = std::max(best_score_to_entry[row][column],
          best_score_to_entry[row - 1][column - 1] + slalom[row][column]);
      }
    }
  }

  std::cout << *std::max_element(best_score_to_entry[slalom_size - 1].begin(),
    best_score_to_entry[slalom_size - 1].end()) << "\n";

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

template <typename T>
std::vector<std::vector<T>> ReadSlalom(int size, std::istream& in_stream) {
  if (!size) {
    in_stream >> size;
  }
  std::vector<std::vector<T>> slalom(size);
  for (int row = 0; row < size; ++row) {
    slalom[row] = ReadArray(row + 1);
  }
  return slalom;
}
