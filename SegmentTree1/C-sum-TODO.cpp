#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

class RangeSumAssignSegmentTree {
  public:
    explicit RangeSumAssignSegmentTree(int size) : size_(size) {
      lazy_.resize(size_ << 2, -1);
      sum_.resize(size_ << 2);
    }

    int RangeSum(int left, int right);
    void RangeAssign(int left, int right, int value);

  private:
    const int size_;
    std::vector<int> lazy_;
    std::vector<int64_t> sum_;

    void Push(int vertex);
    int RangeSum(int left, int right,
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
  RangeSumAssignSegmentTree segment_tree(array_size);

  int query_count;
  std::cin >> query_count;
  while (query_count --> 0) {
    char query_type;
    std::cin >> query_type;

    if (query_type == 'A') {
      int left, right, value;
      std::cin >> left >> right, value;
      segment_tree.RangeAssign(left - 1, right - 1, value);
    } else {  // query_type == 'Q'
      int left, right;
      std::cin >> left >> right;
      std::cout << segment_tree.RangeSum(left - 1, right - 1) << "\n";
    }
  }

  return 0;
}

int RangeSumAssignSegmentTree::RangeSum(int left, int right) {
  return RangeSum(left, right, 1, 0, size_ - 1);
}

void RangeSumAssignSegmentTree::RangeAssign(int left, int right, int value) {
  RangeAssign(left, right, 1, 0, size_ - 1);
}

void Push(int vertex) {
  // todo
}

int RangeSum(int left, int right,
  int tree_vertex, int tree_left, int tree_right) {
  // todo
}

void RangeAssign(int left, int right, int value,
  int tree_vertex, int tree_left, int tree_right) {
  // todo
}
