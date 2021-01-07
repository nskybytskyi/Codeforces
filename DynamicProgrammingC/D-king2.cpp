#include <algorithm>
#include <iostream>
#include <vector>

template <typename T = int>
std::vector<std::vector<T>> ReadMatrix(int row_count = 0, int column_count = 0,
                                       std::istream& in_stream = std::cin);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("king2.in", "r", stdin);
  std::freopen("king2.out", "w", stdout);

  const auto matrix = ReadMatrix(8);

  std::vector<std::vector<int>> best_score_to_cell(8, std::vector<int>(8,
    std::numeric_limits<int>::max()));
  best_score_to_cell[7][0] = 0;

  for (int row = 7; row >= 0; --row) {
    for (int column = 0; column < 8; ++column) {
      if (row < 7) {
        best_score_to_cell[row][column] = std::min(best_score_to_cell[row][column],
          best_score_to_cell[row + 1][column] + matrix[row][column]);
        if (column) {
          best_score_to_cell[row][column] = std::min(best_score_to_cell[row][column],
            best_score_to_cell[row + 1][column - 1] + matrix[row][column]);
        }
      }
      if (column) {
        best_score_to_cell[row][column] = std::min(best_score_to_cell[row][column],
          best_score_to_cell[row][column - 1] + matrix[row][column]);
      }
    }
  }

  std::cout << best_score_to_cell[0][7] << "\n";

  return 0;
}

template <typename T>
std::vector<std::vector<T>> ReadMatrix(int row_count, int column_count, std::istream& in_stream) {
  if (!row_count) {
    in_stream >> row_count >> column_count;
  } else if (!column_count) {
    column_count = row_count;
  }

  std::vector<std::vector<T>> matrix(row_count, std::vector<int>(column_count));
  for (auto& row : matrix) {
    for (auto& entry : row) {
      in_stream >> entry;
    }
  }

  return matrix;
}
