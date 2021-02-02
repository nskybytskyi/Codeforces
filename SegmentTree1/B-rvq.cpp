#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

class SegmentTree {
  public:
    explicit SegmentTree(int size) : size_(size) {
      min_.resize(size_ << 2);
      max_.resize(size_ << 2);
    }

    void Initialize(const std::vector<int>& array);
    int RangeVariation(int left, int right);
    void PointAssign(int index, int value);

  private:
    const int size_;
    std::vector<int> min_, max_;

    void Initialize(const std::vector<int>& array,
      int tree_vertex, int tree_left, int tree_right);
    std::pair<int, int> RangeVariation(int left, int right,
      int tree_vertex, int tree_left, int tree_right);
    void PointAssign(int index, int value,
      int tree_vertex, int tree_left, int tree_right);
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("rvq.in", "r", stdin);
  std::freopen("rvq.out", "w", stdout);

  const int array_size = 100'000;
  SegmentTree segment_tree(array_size);

  std::vector<int> array(array_size);
  for (int64_t index = 1; index <= array_size; ++index) {
    array[index - 1] = (index * index) % 12'345 \
      + (index * index * index) % 23'456;
  }
  segment_tree.Initialize(array);

  int query_count;
  std::cin >> query_count;
  while (query_count --> 0) {
    int first, second;
    std::cin >> first >> second;

    if (first > 0) {
      std::cout << segment_tree.RangeVariation(first - 1, second - 1) << "\n";
    } else {
      segment_tree.PointAssign(std::abs(first) - 1, second);
    }
  }

  return 0;
}

void SegmentTree::Initialize(const std::vector<int>& array) {
  Initialize(array, 1, 0, size_ - 1);
}

void SegmentTree::Initialize(const std::vector<int>& array,
    int tree_vertex, int tree_left, int tree_right) {
  if (tree_left == tree_right) {
    max_[tree_vertex] = min_[tree_vertex] = array[tree_left];
  } else {
    const int tree_middle = (tree_left + tree_right) >> 1;
    const int left_tree_vertex = tree_vertex << 1;
    const int right_tree_vertex = (tree_vertex << 1) | 1;
    Initialize(array, left_tree_vertex, tree_left, tree_middle);
    Initialize(array, right_tree_vertex, tree_middle + 1, tree_right);
    min_[tree_vertex] = std::min(min_[left_tree_vertex], min_[right_tree_vertex]);
    max_[tree_vertex] = std::max(max_[left_tree_vertex], max_[right_tree_vertex]);
  }
}

int SegmentTree::RangeVariation(int left, int right) {
  const auto [range_min, range_max] = RangeVariation(left, right, 1, 0, size_ - 1);
  return range_max - range_min;
}

std::pair<int, int> SegmentTree::RangeVariation(int left, int right,
    int tree_vertex, int tree_left, int tree_right) {
  if (left > right) {
    return {std::numeric_limits<int>::max(), std::numeric_limits<int>::min()};
  } else if (left == tree_left && right == tree_right) {
    return {min_[tree_vertex], max_[tree_vertex]};
  } else {
    const int tree_middle = (tree_left + tree_right) >> 1;
    const auto [left_min, left_max] = RangeVariation(left, std::min(right, tree_middle),
      tree_vertex << 1, tree_left, tree_middle);
    const auto [right_min, right_max] = RangeVariation(std::max(left, tree_middle + 1), right,
      (tree_vertex << 1) | 1, tree_middle + 1, tree_right);
    return {std::min(left_min, right_min), std::max(left_max, right_max)};
  }
}

void SegmentTree::PointAssign(int index, int value) {
  PointAssign(index, value, 1, 0, size_ - 1);
}

void SegmentTree::PointAssign(int index, int value,
    int tree_vertex, int tree_left, int tree_right) {
  if (tree_left == tree_right) {
    max_[tree_vertex] = min_[tree_vertex] = value;
  } else {
    const int tree_middle = (tree_left + tree_right) >> 1;
    const int left_tree_vertex = tree_vertex << 1;
    const int right_tree_vertex = (tree_vertex << 1) | 1;
    if (index <= tree_middle) {
      PointAssign(index, value, left_tree_vertex, tree_left, tree_middle);
    } else {
      PointAssign(index, value, right_tree_vertex, tree_middle + 1, tree_right);
    }
    min_[tree_vertex] = std::min(min_[left_tree_vertex], min_[right_tree_vertex]);
    max_[tree_vertex] = std::max(max_[left_tree_vertex], max_[right_tree_vertex]);
  }
}
