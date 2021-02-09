#include <iostream>
#include <utility>
#include <vector>

using Grid = std::vector<std::vector<int64_t>>;

using Path = std::vector<std::pair<int, int>>;

void ask(const Grid& grid) {
  for (const auto& row : grid) {
    for (auto cell : row) {
      std::cout << cell << " ";
    }
    std::cout << std::endl << std::flush;
    std::cout.flush();
  }
}

void answer(const Path& path) {
  for (const auto [row, column] : path) {
    std::cout << row + 1 << " " << column + 1 << std::endl << std::flush;
    std::cout.flush();
  }
}

int main() {
  int grid_size;
  std::cin >> grid_size;

  Grid grid(grid_size, std::vector<int64_t>(grid_size));
  for (int column = 1; column < grid_size; ++column) {
    grid[0][column] = 1ll << (column - 1);
  }
  for (int row = 1; row < grid_size; ++row) {
    for (int column = 1; column < grid_size; ++column) {
      grid[row][column] = grid[row - 1][column] + grid[row][column - 1];
    }
  }

  Grid lower(grid_size, std::vector<int64_t>(grid_size));
  for (int row = 1; row < grid_size; ++row) {
    lower[row][0] = lower[row - 1][0] + grid[row][0];
  }
  for (int row = 0; row < grid_size; ++row) {
    for (int column = 1; column < grid_size; ++column) {
      lower[row][column] = lower[row][column - 1] + grid[row][column];
    }
  }

  Grid upper(grid_size, std::vector<int64_t>(grid_size));
  for (int column = 1; column < grid_size; ++column) {
    upper[0][column] = upper[0][column - 1] + grid[0][column];
  }
  for (int row = 1; row < grid_size; ++row) {
    for (int column = 0; column < grid_size; ++column) {
      upper[row][column] = upper[row - 1][column] + grid[row][column];
    }
  }

  auto find_path = [&] (int64_t total_weight) -> Path {
    int row = grid_size - 1, column = grid_size - 1;
    Path path = {{row, column}};
    while (row || column) {
      total_weight -= grid[row][column];
      if (!row) {
        --column;
      } else if (!column) {
        --row;
      } else if (lower[row - 1][column] <= total_weight &&
                 total_weight <= upper[row - 1][column]) {
        --row;
      } else if (lower[row][column - 1] <= total_weight &&
                 total_weight <= upper[row][column - 1]) {
        --column;
      } else {
        exit(1);
      }
      path.emplace_back(row, column);
    }
    return {path.rbegin(), path.rend()};
  };

  ask(grid);

  int query_count;
  std::cin >> query_count;
  while (query_count--) {
    int64_t total_weight;
    std::cin >> total_weight;
    auto path = find_path(total_weight);
    answer(path);
  }

  return 0;
}
