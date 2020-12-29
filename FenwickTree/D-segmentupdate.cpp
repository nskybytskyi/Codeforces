#include <cstdio>
#include <iostream>
#include <vector>

template <typename T>
class FenwickTree {
  public:
    explicit FenwickTree(int size);
    void Initialize(const std::vector<T>& array);
    T Query(int index) const;
    void Increment(int left, int right, T delta);

  private:
    int size_;
    std::vector<T> tree_;

    T Sum(int right) const;
    void Increment(int index, T delta);
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("segmentupdate.in", "r", stdin);
  std::freopen("segmentupdate.out", "w", stdout);

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

    if (query_type == 1) {
      int left, right; int64_t delta;
      std::cin >> left >> right >> delta;
      --left, --right;
      fenwick_tree.Increment(left, right, delta);
    } else {  // if (query_type == 2)
      int index;
      std::cin >> index;
      --index;
      std::cout << fenwick_tree.Query(index) << "\n";
    }
  }

  return 0;
}

template <typename T>
FenwickTree<T>::FenwickTree(int size) : size_(size) {
  tree_.resize(size);
}

template <typename T>
void FenwickTree<T>::Initialize(const std::vector<T>& array) {
  for (int index = 0; index < size_; ++index) {
    Increment(index, index, array[index]);
  }
}

template <typename T>
T FenwickTree<T>::Query(int index) const {
  return Sum(index);
}

template <typename T>
void FenwickTree<T>::Increment(int left, int right, T delta) {
  Increment(left, delta);
  Increment(right + 1, -delta);
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
