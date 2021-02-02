#include <algorithm>
#include <iostream>
#include <vector>

class MinimumSparseTable {
  public:
    explicit MinimumSparseTable(int size) : size_(size), max_power_(32 - __builtin_clz(size)) {
      sparse_table_.resize(max_power_);
      for (auto& sparse_layer : sparse_table_) {
        sparse_layer.resize(size_);
      }
    }

    void Initialize(const std::vector<int>& array);
    int Minimum(int left, int right) const;

  private:
    int size_, max_power_;
    std::vector<std::vector<int>> sparse_table_;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("sparse.in", "r", stdin);
  std::freopen("sparse.out", "w", stdout);

  int array_size, query_count;
  std::cin >> array_size >> query_count;
  MinimumSparseTable sparse_table(array_size);

  std::vector<int> array(array_size);
  std::cin >> array[0];
  for (int index = 0; index + 1 < array_size; ++index) {
    array[index + 1] = (23 * array[index] + 21'563) % 16'714'589;
  }
  sparse_table.Initialize(array);

  int first, second, answer = 0;
  std::cin >> first >> second;
  for (int index = 1; index <= query_count; ++index) {
    const auto [left, right] = std::minmax(first, second);
    answer = sparse_table.Minimum(left - 1, right - 1);
    if (index < query_count) {
      first = ((17 * first + 751 + answer + 2 * index) % array_size) + 1;
      second = ((13 * second + 593 + answer + 5 * index) % array_size) + 1;
    }
  }

  std::cout << first << " " << second << " " << answer << "\n";

  return 0;
}

void MinimumSparseTable::Initialize(const std::vector<int>& array) {
  std::copy(array.begin(), array.end(), sparse_table_[0].begin());
  for (int power = 1; power < max_power_; ++power) {
    for (int first = 0, second = 1 << (power - 1); second < size_; ++first, ++second) {
      sparse_table_[power][first] \
        = std::min(sparse_table_[power - 1][first], sparse_table_[power - 1][second]);
    }
  }
}

int MinimumSparseTable::Minimum(int left, int right) const {
  const int power = 31 - __builtin_clz(right + 1 - left);
  return std::min(sparse_table_[power][left], sparse_table_[power][right + 1 - (1 << power)]);
}
