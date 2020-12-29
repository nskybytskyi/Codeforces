#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

template <typename T>
class FenwickTree {
  public:
    explicit FenwickTree(int size);
    T Sum(int left, int right) const;
    void Increment(int index, T delta);

  private:
    int size_;
    std::vector<T> tree_;

    T Sum(int right) const;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("inverse.in", "r", stdin);
  std::freopen("inverse.out", "w", stdout);

  int array_size;
  std::cin >> array_size;
  FenwickTree<int64_t> fenwick_tree(array_size);

  std::vector<int64_t> array(array_size);
  for (auto& element : array) {
    std::cin >> element;
  }

  // convert array to permutation
  std::vector<std::pair<int64_t, int>> value_index(array_size);
  for (int index = 0; index < array_size; ++index) {
    value_index[index] = std::make_pair(array[index], index);
  }
  std::sort(value_index.begin(), value_index.end());
  for (int index = 0; index < array_size; ++index) {
    array[value_index[index].second] = index;
  }

  int64_t inversion_count = 0;
  for (const auto element : array) {
    inversion_count += fenwick_tree.Sum(element, array_size - 1);
    fenwick_tree.Increment(element, 1);
  }
  std::cout << inversion_count;

  return 0;
}

template <typename T>
FenwickTree<T>::FenwickTree(int size) : size_(size) {
  tree_.resize(size);
}

template <typename T>
T FenwickTree<T>::Sum(int left, int right) const {
  return Sum(right) - Sum(left - 1);
}

template <typename T>
void FenwickTree<T>::Increment(int index, T delta) {
  for (; index < size_; index = (index | (index + 1))) {
    tree_[index] += delta;
  }
}

template <typename T>
T FenwickTree<T>::Sum(int right) const {
  T sum = 0;
  for (; right >= 0; right = (right & (right + 1)) - 1) {
    sum += tree_[right];
  }
  return sum;
}
