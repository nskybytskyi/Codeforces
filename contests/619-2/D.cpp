#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int64_t rows, cols, steps;
  cin >> rows >> cols >> steps;

  if (steps > 4 * rows * cols - 2 * rows - 2 * cols) {
    cout << "NO\n";
  } else {
    vector<pair<int64_t, char>> moves;

    auto mv = [&] (int64_t repeat, char move) -> void {
      int64_t f = min(steps, repeat);
      if (f) moves.emplace_back(f, move);
      steps -= f;
    };

    for (int step = 0; (step < rows - 1) && steps; ++step) {
      mv(cols - 1, 'R');
      mv(cols - 1, 'L');
      mv(1, 'D');
    }
    mv(cols - 1, 'R');
    for (int step = 0; (step < cols - 1) && steps; ++step) {
      mv(rows - 1, 'U');
      mv(rows - 1, 'D');
      mv(1, 'L');
    }
    mv(rows - 1, 'U');

    cout << "YES" << "\n";
    cout << moves.size() << "\n";
    for (const auto& [repeat, move] : moves) {
      cout << repeat << " " << move << "\n";
    }
  }

  return 0;
}
