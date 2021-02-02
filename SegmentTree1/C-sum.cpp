#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

class SegmentTree {
  public:
    explicit SegmentTree(int size) : size_(size) {
      lazy_.resize(size_ << 2, -1);
      sum_.resize(size_ << 2);
    }

    int64_t RangeSum(int left, int right);
    void RangeAssign(int left, int right, int value);

  private:
    const int size_;
    std::vector<int> lazy_;
    std::vector<int64_t> sum_;

    void Push(int tree_vertex, int tree_left, int tree_right);
    int64_t RangeSum(int left, int right,
      int tree_vertex, int tree_left, int tree_right);
    void RangeAssign(int left, int right, int value,
      int tree_vertex, int tree_left, int tree_right);
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("sum.in", "r", stdin);
  std::freopen("sum.out", "w", stdout);

  int array_size;
  std::cin >> array_size;
  SegmentTree segment_tree(array_size);

  int query_count;
  std::cin >> query_count;
  while (query_count --> 0) {
    char query_type;
    std::cin >> query_type;

    if (query_type == 'A') {
      int left, right, value;
      std::cin >> left >> right >> value;
      segment_tree.RangeAssign(left - 1, right - 1, value);
    } else {  // query_type == 'Q'
      int left, right;
      std::cin >> left >> right;
      std::cout << segment_tree.RangeSum(left - 1, right - 1) << "\n";
    }
  }

  return 0;
}

int64_t SegmentTree::RangeSum(int left, int right) {
  return RangeSum(left, right, 1, 0, size_ - 1);
}

void SegmentTree::RangeAssign(int left, int right, int value) {
  RangeAssign(left, right, value, 1, 0, size_ - 1);
}

void SegmentTree::Push(int tree_vertex, int tree_left, int tree_right) {
  if (lazy_[tree_vertex] != -1) {
    if (tree_left != tree_right) {
      lazy_[tree_vertex << 1] = lazy_[(tree_vertex << 1) | 1] = lazy_[tree_vertex];
    }
    sum_[tree_vertex] = lazy_[tree_vertex] * (tree_right - tree_left + 1ll);
    lazy_[tree_vertex] = -1;
  }
}

int64_t SegmentTree::RangeSum(int left, int right,
    int tree_vertex, int tree_left, int tree_right) {
  Push(tree_vertex, tree_left, tree_right);
  if (left > right) {
    return 0;
  } else if (left == tree_left && right == tree_right) {
    return sum_[tree_vertex];
  } else {
    const int tree_middle = (tree_left + tree_right) >> 1;
    const int64_t left_sum = RangeSum(left, std::min(right, tree_middle),
      tree_vertex << 1, tree_left, tree_middle);
    const int64_t right_sum = RangeSum(std::max(left, tree_middle + 1), right,
      (tree_vertex << 1) | 1, tree_middle + 1, tree_right);
    return left_sum + right_sum;
  }
}

void SegmentTree::RangeAssign(int left, int right, int value,
    int tree_vertex, int tree_left, int tree_right) {
  Push(tree_vertex, tree_left, tree_right);
  if (left <= right) {
    if (left == tree_left && right == tree_right) {
      lazy_[tree_vertex] = value;
      Push(tree_vertex, tree_left, tree_right);
    } else {
      const int tree_middle = (tree_left + tree_right) >> 1;
      const int left_tree_vertex = tree_vertex << 1;
      const int right_tree_vertex = (tree_vertex << 1) | 1;
      RangeAssign(left, std::min(right, tree_middle), value,
        left_tree_vertex, tree_left, tree_middle);
      RangeAssign(std::max(left, tree_middle + 1), right, value,
        right_tree_vertex, tree_middle + 1, tree_right);
      sum_[tree_vertex] = sum_[left_tree_vertex] + sum_[right_tree_vertex];
    }
  }
}
