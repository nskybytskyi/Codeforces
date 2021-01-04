#include <cstdio>
#include <functional>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

template <typename T = int>
std::vector<T> ReadArray(int size = 0, std::istream& in_stream = std::cin);

template <typename T = int>
T BinarySearch(T lower_bound, T upper_bound, std::function<bool(T)> unary_predicate, T precision = 1);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("cows.in", "r", stdin);
  std::freopen("cows.out", "w", stdout);

  int stall_count, cow_count;
  std::cin >> stall_count >> cow_count;
  const auto stalls_coordinates = ReadArray(stall_count);

  int lower_bound = 0, upper_bound = std::numeric_limits<int>::max();
  auto unary_predicate = [&] (int distance_between_cows) -> bool {
    int previous_stall_coordinate = std::numeric_limits<int>::min();
    int current_cow_count = 0;
    for (auto stall_coordinate : stalls_coordinates) {
      if (stall_coordinate >= previous_stall_coordinate + distance_between_cows) {
        previous_stall_coordinate = stall_coordinate;
        ++current_cow_count;
      }
    }
    return current_cow_count >= cow_count;
  };

  std::cout << BinarySearch<int>(lower_bound, upper_bound, unary_predicate) << "\n";

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
T BinarySearch(T lower_bound, T upper_bound, std::function<bool(T)> unary_predicate, T precision) {
  while (lower_bound + precision < upper_bound) {
    T middle = lower_bound + (upper_bound - lower_bound) / 2;
    if (unary_predicate(middle)) {
      lower_bound = middle;
    } else {
      upper_bound = middle;
    }
  }
  return lower_bound;
}
