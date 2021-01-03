#include <algorithm>
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

template <typename T = int>
std::vector<T> ReadArray(int size = 0, std::istream& in_stream = std::cin);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("collect.in", "r", stdin);
  std::freopen("collect.out", "w", stdout);

  const auto present_butterflies = ReadArray();
  const auto query_butterflies = ReadArray();

  for (auto query_butterfly : query_butterflies) {
    auto it = std::lower_bound(present_butterflies.begin(),
                               present_butterflies.end(),
                               query_butterfly);
    if (it == present_butterflies.end() || *it != query_butterfly) {
      std::cout << "NO" << "\n";
    } else {
      std::cout << "YES" << "\n";
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
