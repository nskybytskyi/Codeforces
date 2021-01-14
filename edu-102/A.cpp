#include <algorithm>
#include <iostream>
#include <vector>

template <typename T = int>
std::vector<T> ReadArray(int size = 0, std::istream& in_stream = std::cin);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int testcase_count;
  std::cin >> testcase_count;
  while (testcase_count --> 0) {
    int length, limit;
    std::cin >> length >> limit;
    auto array = ReadArray(length);

    std::sort(array.begin(), array.end());
    const int mimimum = array[0] + array[1];
    for (auto& element : array) {
      element = std::min(element, mimimum); 
    }

    bool all = true;
    for (auto element : array) {
      all &= element <= limit;
    }

    if (all) {
      std::cout << "YES" << "\n";
    } else {
      std::cout << "NO" << "\n";
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
