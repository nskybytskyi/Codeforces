#include <iostream>
#include <numeric>
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
    const auto candies = ReadArray();

    if (accumulate(candies.begin(), candies.end(), 0) & 1) {
      cout << "NO\n";
      continue;
    }

    int one = 0, two = 0;
    for (auto candy : candies) {
      if (candy == 1) {
        ++one;
      } else {
        ++two;
      }
    }

    if (!one && accumulate(candies.begin(), candies.end(), 0) & 2) {
      cout << "NO\n";
    } else {
      cout << "YES\n";
    }
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
