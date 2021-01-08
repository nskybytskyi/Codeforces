#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <typename T = int>
std::vector<T> ReadArray(int size = 0, std::istream& in_stream = std::cin);

inline bool HillValley(int a, int b, int c);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    const auto a = ReadArray(n);

    int initial_intimidation = 0;
    for (int i = 1; i + 1 < n; ++i) {
      if (HillValley(a[i - 1], a[i], a[i + 1])) {
        ++initial_intimidation;
      }
    }

    int best_new_intimidation = initial_intimidation;
    for (int i = 0; i < n; ++i) {
      int current_local_intimidation = 0;
      vector<int> possible;
      if (i >= 2) {
        if (HillValley(a[i - 2], a[i - 1], a[i])) {
          ++current_local_intimidation;
        }
        possible.push_back(a[i - 2]);
      }
      if (i >= 1 && i + 1 < n) {
        if (HillValley(a[i - 1], a[i], a[i + 1])) {
          ++current_local_intimidation;
        }
        possible.push_back(a[i - 1]);
        possible.push_back(a[i + 1]);
      }
      if (i + 2 < n) {
        if (HillValley(a[i], a[i + 1], a[i + 2])) {
          ++current_local_intimidation;
        }
        possible.push_back(a[i + 2]);
      }

      int best_new_local_intimidation = current_local_intimidation;
      for (auto ai : possible) {
        int new_local_intimidation = 0;
        if (i >= 2) {
          if (HillValley(a[i - 2], a[i - 1], ai)) {
            ++new_local_intimidation;
          }
        }
        if (i >= 1 && i + 1 < n) {
          if (HillValley(a[i - 1], ai, a[i + 1])) {
            ++new_local_intimidation;
          }
        }
        if (i + 2 < n) {
          if (HillValley(ai, a[i + 1], a[i + 2])) {
            ++new_local_intimidation;
          }
        }

        best_new_local_intimidation = min(best_new_local_intimidation, new_local_intimidation);
      }

      best_new_intimidation = min(best_new_intimidation,
        initial_intimidation - current_local_intimidation + best_new_local_intimidation);
    }

    cout << best_new_intimidation << "\n";
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

bool HillValley(int a, int b, int c) {
  return (a < b && b > c) || (a > b && b < c);
}
