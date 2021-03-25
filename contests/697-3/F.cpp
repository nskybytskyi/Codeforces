#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <numeric>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

template <typename T = int>
std::vector<T> ReadArray(int size = 0, std::istream& in_stream = std::cin);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;

    auto a = ReadArray<string>(n), b = ReadArray<string>(n);

    for (int row = 0; row < n; ++row) {
      if (a[row][0] != b[row][0]) {
        for (auto& col : a[row]) {
          if (col == '1') {
            col = '0';
          } else {  // col == '0';
            col = '1';
          }
        }
      }
    }

    for (int col = 1; col < n; ++col) {
      if (a[0][col] != b[0][col]) {
        for (int row = 0; row < n; ++row) {
          if (a[row][col] == '1') {
            a[row][col] = '0';
          } else {  // a[row][col] == '0';
            a[row][col] = '1';
          }
        }
      }
    }

    bool mismatch = false;

    for (int row = 0; row < n; ++row) {
      mismatch |= a[row] != b[row];
    }

    if (mismatch) {
      cout << "NO";
    } else {
      cout << "YES";
    }
    cout << "\n";
  }

  return 0;
}

template <typename T>
std::vector<T> ReadArray(int size, std::istream& in_stream) {
  if (!size) {
    in_stream >> size;
  }
  std::vector<T> array(size);
  for (auto& element : array) {
    in_stream >> element;
  }
  return array;
}