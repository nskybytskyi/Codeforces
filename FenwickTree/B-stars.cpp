#include <cstdio>
#include <iostream>
#include <vector>

template <typename T>
class FenwickTree3D {
  public:
    explicit FenwickTree3D(int length, int width, int height);
    T Sum(int x_left, int x_right, int y_left, int y_right, int z_left, int z_right) const;
    void Increment(int x, int y, int z, T delta);

  private:
    int length_, width_, height_;
    std::vector<std::vector<std::vector<T>>> tree_;

    T Sum(int x_right, int y_right, int z_right) const;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("stars.in", "r", stdin);
  std::freopen("stars.out", "w", stdout);

  int cube_side;
  std::cin >> cube_side;
  FenwickTree3D<int64_t> fenwick_tree_3d(cube_side, cube_side, cube_side);

  int query_type;
  while (std::cin >> query_type) {
    if (query_type == 1) {
      int x, y, z; int64_t delta;
      std::cin >> x >> y >> z >> delta;
      fenwick_tree_3d.Increment(x, y, z, delta);
    } else if (query_type == 2) {
      int x_left, y_left, z_left, x_right, y_right, z_right;
      std::cin >> x_left >> y_left >> z_left >> x_right >> y_right >> z_right;
      std::cout << fenwick_tree_3d \
        .Sum(x_left, x_right, y_left, y_right, z_left, z_right) << "\n";
    } else {  // if (query_type == 3)
      break;
    }
  }

  return 0;
}

template <typename T>
FenwickTree3D<T>::FenwickTree3D(int length, int width, int height)
  : length_(length), width_(width), height_(height) {
    tree_.resize(length);
    for (auto& slice : tree_) {
      slice.resize(width);
      for (auto& line : slice) {
        line.resize(height, 0);
      }
    }
}

template <typename T>
T FenwickTree3D<T>::Sum(int x_left, int x_right, int y_left, int y_right, int z_left, int z_right) const {
  return Sum(x_right, y_right, z_right) - Sum(x_left - 1, y_right, z_right)
    - Sum(x_right, y_left - 1, z_right) - Sum(x_right, y_right, z_left - 1)
    + Sum(x_left - 1, y_left - 1, z_right) + Sum(x_left - 1, y_right, z_left - 1)
    + Sum(x_right, y_left - 1, z_left - 1) - Sum(x_left - 1, y_left - 1, z_left - 1);
}

template <typename T>
void FenwickTree3D<T>::Increment(int x, int y, int z, T delta) {
  for (int i = x; i < length_; i = (i | (i + 1))) {
    for (int j = y; j < width_; j = (j | (j + 1))) {
      for (int k = z; k < height_; k = (k | (k + 1))) {
        tree_[i][j][k] += delta;
      }
    }
  }
}

template <typename T>
T FenwickTree3D<T>::Sum(int x_right, int y_right, int z_right) const {
  T sum = 0;
  for (int x = x_right; x >= 0; x = (x & (x + 1)) - 1) {
    for (int y = y_right; y >= 0; y = (y & (y + 1)) - 1) {
      for (int z = z_right; z >= 0; z = (z & (z + 1)) - 1) {
        sum += tree_[x][y][z];
      }
    }
  }
  return sum;
}
