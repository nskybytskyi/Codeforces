#include <bitset>
#include <iostream>
#include <vector>

template <typename T = int>
std::vector<T> ReadArray(int size = 0, std::istream& in_stream = std::cin);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  // std::freopen("knapsack.in", "r", stdin);
  // std::freopen("knapsack.out", "w", stdout);

  const int max_knapsack_capacity = 10'000;

  int knapsack_capacity;
  std::cin >> knapsack_capacity;

  const auto ingots_weights = ReadArray();

  std::bitset<max_knapsack_capacity + 1> possible_subset_total_weight;
  possible_subset_total_weight[0] = 1;

  for (const auto ingot_weight : ingots_weights) {
    possible_subset_total_weight |= possible_subset_total_weight << ingot_weight;
  }

  bool found_max = false;
  for (int weight = knapsack_capacity; weight >= 0 && !found_max; --weight) {
    if (possible_subset_total_weight[weight]) {
      std::cout << weight << "\n";
      found_max = true;
    }
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
