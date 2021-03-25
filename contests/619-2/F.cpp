#include <bits/stdc++.h>
using namespace std;

int rows, cols, colors;

const int kNotVisited = -1;

void BFS(const vector<vector<int>>& grid,
         const vector<vector<pair<int, int>>>& cells,
         vector<vector<int>>& distance,
         int color) {
  deque<pair<int, int>> bfs;
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      if (grid[row][col] == color) {
        bfs.emplace_back(row, col);
        distance[row][col] = 0;
      }
    }
  }

  vector<int> used(colors, false);
  used[color] = true;

  while (!bfs.empty()) {
    const auto [row, col] = bfs.front();
    bfs.pop_front();

    const vector<pair<int, int>> neighbours = {{row - 1, col}, {row + 1, col}, {row, col - 1}, {row, col + 1}};

    for (const auto& [nrow, ncol] : neighbours) {
      if (0 <= nrow && nrow < rows && 0 <= ncol && ncol < cols && distance[nrow][ncol] == kNotVisited) {
        bfs.emplace_back(nrow, ncol);
        distance[nrow][ncol] = distance[row][col] + 1;
      }
    }

    if (!used[grid[row][col]]) {
      used[grid[row][col]] = true;

      for (const auto& [nrow, ncol] : cells[grid[row][col]]) {
        if (distance[nrow][ncol] == kNotVisited) {
          bfs.emplace_back(nrow, ncol);
          distance[nrow][ncol] = distance[row][col] + 1;
        }
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> rows >> cols >> colors;

  vector<vector<int>> grid(rows, vector<int>(cols));
  vector<vector<pair<int, int>>> cells(colors);
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      cin >> grid[row][col];
      --grid[row][col];
      cells[grid[row][col]].emplace_back(row, col);
    }
  }

  vector<vector<vector<int>>> distance(colors, vector<vector<int>>(rows, vector<int>(cols, kNotVisited)));
  for (int color = 0; color < colors; ++color) {
    BFS(grid, cells, distance[color], color);
  }

  int q;
  cin >> q;
  while (q--) {
    int src_row, src_col, dst_row, dst_col;
    cin >> src_row >> src_col >> dst_row >> dst_col;
    --src_row, --src_col, --dst_row, --dst_col;

    int answer = std::abs(src_col - dst_col) + std::abs(src_row - dst_row);
    for (int color = 0; color < colors; ++color) {
      answer = min(answer, distance[color][src_row][src_col] + 1 + distance[color][dst_row][dst_col]);
    }
    cout << answer << "\n";
  }

  return 0;
}
