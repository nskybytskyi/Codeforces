#include <bits/stdc++.h>
using namespace std;

template <typename T = int>
T BinarySearch(T lower_bound, T upper_bound, std::function<bool(T)> unary_predicate, T precision = 1);

class SparseTable {
  public:
    explicit SparseTable(int rows, int cols)
        : rows_(rows), cols_(cols), max_power_(10) {
      sparse_table_.resize(max_power_,
        std::vector<std::vector<std::vector<int>>>(max_power_,
          std::vector<std::vector<int>>(cols_,
            std::vector<int>(rows_, 0))));
    }

    void Initialize(const std::vector<std::vector<int>>& array);
    int Maximum(int top, int left, int right, int bottom) const;

  private:
    int rows_, cols_, max_power_;
    // horizontal power, vertical power, left, top
    std::vector<std::vector<std::vector<std::vector<int>>>> sparse_table_;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int rows, cols, q;
  cin >> rows >> cols >> q;
  vector<string> board(rows);
  for (auto& row : board)
    cin >> row;

  vector<vector<int>> center(rows, vector<int>(cols));

  auto expand = [&] (int row, int col) -> int {
    int size = 0;
    bool good = true;

    while (0 <= row - size && row + 1 + size < rows &&
           0 <= col - size && col + 1 + size < cols &&
           good) {
      for (int j = 0; j <= size; ++j)
        good &= board[row - size][col - j] == 'R';
      for (int j = 0; j <= size; ++j)
        good &= board[row - j][col - size] == 'R';

      for (int j = 0; j <= size; ++j)
        good &= board[row + 1 + size][col - j] == 'Y';
      for (int j = 0; j <= size; ++j)
        good &= board[row + 1 + j][col - size] == 'Y';

      for (int j = 0; j <= size; ++j)
        good &= board[row - size][col + 1 + j] == 'G';
      for (int j = 0; j <= size; ++j)
        good &= board[row - j][col + 1 + size] == 'G';

      for (int j = 0; j <= size; ++j)
        good &= board[row + 1 + size][col + 1 + j] == 'B';
      for (int j = 0; j <= size; ++j)
        good &= board[row + 1 + j][col + 1 + size] == 'B';

      ++size;
    }

    return max(0, good ? (4 * size * size) : (4 * (size - 1) * (size - 1)));
  };

  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      center[row][col] = expand(row, col);
    }
  }

  SparseTable sparse_table(rows, cols);
  sparse_table.Initialize(center);

  while (q--) {
    int top, left, right, bottom;
    cin >> top >> left >> bottom >> right;
    --top, --left, --right, --bottom;

    int lower_bound = 0, upper_bound = (min(rows, cols) >> 1) + 10;
    auto possible = [&] (int middle) -> bool {
      return sparse_table.Maximum(top - 1 + middle,
                                  left - 1 + middle,
                                  right - middle,
                                  bottom - middle) >= 4 * middle * middle;
    };
    int best_side = BinarySearch<int>(lower_bound, upper_bound, possible);

    cout << 4 * best_side * best_side << "\n";
  }

  return 0;
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

void SparseTable::Initialize(const std::vector<std::vector<int>>& array) {
  for (int row = 0; row < rows_; ++row) {
    for (int col = 0; col < cols_; ++col) {
      sparse_table_[0][0][col][row] = array[row][col];
    }
  }

  for (int row = 0; row < rows_; ++row) {
    for (int horizontal = 1; horizontal < max_power_; ++horizontal) {
      for (int left = 0, right = 1 << (horizontal - 1); right < cols_; ++left, ++right) {
        sparse_table_[horizontal][0][left][row] \
          = std::max(sparse_table_[horizontal - 1][0][left][row],
                     sparse_table_[horizontal - 1][0][right][row]);
      }
    }
  }

  for (int col = 0; col < cols_; ++col) {
    for (int vertical = 1; vertical < max_power_; ++vertical) {
      for (int top = 0, bottom = 1 << (vertical - 1); bottom < rows_; ++top, ++bottom) {
        sparse_table_[0][vertical][col][top] \
          = std::max(sparse_table_[0][vertical - 1][col][top],
                     sparse_table_[0][vertical - 1][col][bottom]);
      }
    }
  }

  for (int horizontal = 1; horizontal < max_power_; ++horizontal) {
    for (int vertical = 1; vertical < max_power_; ++vertical) {
      for (int top = 0, bottom = 1 << (vertical - 1); bottom < rows_; ++top, ++bottom) {
        for (int left = 0, right = 1 << (horizontal - 1); right < cols_; ++left, ++right) {
          sparse_table_[horizontal][vertical][left][top] \
            = std::max({sparse_table_[horizontal - 1][vertical - 1][left][top],
                        sparse_table_[horizontal - 1][vertical - 1][right][top],
                        sparse_table_[horizontal - 1][vertical - 1][left][bottom],
                        sparse_table_[horizontal - 1][vertical - 1][right][bottom]});
        }
      }
    }
  }
}

int SparseTable::Maximum(int top, int left, int right, int bottom) const {
  if (left > right || top > bottom) return 0;
  const int horizontal = std::log2(right + 1 - left);
  const int vertical = std::log2(bottom + 1 - top);
  return std::max({sparse_table_[horizontal][vertical][left][top],
                   sparse_table_[horizontal][vertical][left][bottom + 1 - (1 << vertical)],
                   sparse_table_[horizontal][vertical][right + 1 - (1 << horizontal)][top],
                   sparse_table_[horizontal][vertical][right + 1 - (1 << horizontal)][bottom + 1 - (1 << vertical)]});
}
