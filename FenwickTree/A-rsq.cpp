#include <cstdio>
#include <iostream>
#include <vector>

template <typename T>
class FenwickTree {
  public:
    explicit FenwickTree(int size);
    void Initialize(const std::vector<T>& array);
    T Sum(int left, int right) const;
    void Assign(int index, T value);

  private:
    int size_;
    std::vector<T> array_, tree_;

    T Sum(int right) const;
    void Increment(int index, T delta);
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("rsq.in", "r", stdin);
  std::freopen("rsq.out", "w", stdout);

  int array_size, query_count;
  std::cin >> array_size >> query_count;
  FenwickTree<int64_t> fenwick_tree(array_size);

  std::vector<int64_t> array(array_size);
  for (auto& element : array) {
    std::cin >> element;
  }
  fenwick_tree.Initialize(array);

  while (query_count --> 0) {
    int query_type;
    std::cin >> query_type;

    if (query_type == 0) {
      int left, right;
      std::cin >> left >> right;
      --left, --right;
      std::cout << fenwick_tree.Sum(left, right) << "\n";
    } else {  // if (query_type == 1)
      int index; int64_t value;
      std::cin >> index >> value;
      --index;
      fenwick_tree.Assign(index, value);
    }
  }

  return 0;
}

template <typename T>
FenwickTree<T>::FenwickTree(int size) : size_(size) {
  array_.resize(size);
  tree_.resize(size);
}

template <typename T>
void FenwickTree<T>::Initialize(const std::vector<T>& array) {
  for (int index = 0; index < size_; ++index) {
    array_[index] = array[index];
    Increment(index, array[index]);
  }
}

template <typename T>
T FenwickTree<T>::Sum(int left, int right) const {
  return Sum(right) - Sum(left - 1);
}

template <typename T>
void FenwickTree<T>::Assign(int index, T value) {
  Increment(index, value - array_[index]);
  array_[index] = value;
}

template <typename T>
T FenwickTree<T>::Sum(int right) const {
  T sum = 0;
  for (; right >= 0; right = (right & (right + 1)) - 1) {
    sum += tree_[right];
  }
  return sum;
}

template <typename T>
void FenwickTree<T>::Increment(int index, T delta) {
  for (; index < size_; index = (index | (index + 1))) {
    tree_[index] += delta;
  }
}
