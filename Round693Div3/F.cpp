#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

using Cell = pair<int, int>;  // {col, row}

std::vector<Cell> ReadArray(int size = 0, std::istream& in_stream = std::cin) {
  if (!size) {
    in_stream >> size;
  }
  std::vector<Cell> array(size);
  for (auto& element : array) {
    in_stream >> element.second >> element.first;
    --element.second;
  }
  return array;
}

bool solve() {
  int strip_length;
  cin >> strip_length;
  auto cells = ReadArray();

  sort(cells.begin(), cells.end());

  cells.emplace_back(strip_length + 1, 0);
  cells.emplace_back(strip_length + 1, 1);

  bool top_free = true, bot_free = true;
  int col = 0;

  for (const auto& cell : cells) {
    // cout << "prev col = " << col << " " \
    //   << "cell col = " << cell.first << " " \
    //   << "cell row = " << cell.second << " " \
    //   << "top free = " << top_free << " " \
    //   << "bot free = " << bot_free << "\n";
    if (top_free == bot_free) {
      if (col == cell.first) {
        return false;
      }
      if (cell.second == 1) {
        col = cell.first;
        bot_free = false;
        top_free = true;
      } else {
        col = cell.first;
        top_free = false;
        bot_free = true;
      }
    } else {
      if ((cell.first - col) & 1) {  // distance is odd
        if (cell.second == 1) {
          if (!top_free) {
            return false;
          }
        } else {
          if (!bot_free) {
            return false;
          }
        }
      } else {  // distance is even
        if (cell.second == 1) {
          if (!bot_free) {
            return false;
          }
        } else {
          if (!top_free) {
            return false;
          }
        }
      }
      col = cell.first;
      top_free = false;
      bot_free = false;
    }
  }
  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    if (solve()) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }

  return 0;
}
