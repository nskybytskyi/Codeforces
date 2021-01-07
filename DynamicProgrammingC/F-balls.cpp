#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

template <typename T = int>
std::vector<T> ReadArray(int size = 0, std::istream& in_stream = std::cin);

std::vector<int> GetPyramidSizes(int max_testcase);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  // std::freopen("balls.in", "r", stdin);
  // std::freopen("balls.out", "w", stdout);

  const auto testcases = ReadArray();

  const int max_testcase = *std::max_element(testcases.begin(), testcases.end());
  std::vector<int> min_piramids(max_testcase + 1, std::numeric_limits<int>::max());
  min_piramids[0] = 0;

  const auto pyramid_sizes = GetPyramidSizes(max_testcase);

  for (int balls = 1; balls <= max_testcase; ++balls) {
    for (const auto pyramid_size : pyramid_sizes) {
      if (pyramid_size <= balls) {
        min_piramids[balls] = std::min(min_piramids[balls],
          min_piramids[balls - pyramid_size] + 1);
      }
    }
  }

  for (const auto testcase : testcases) {
    std::cout << min_piramids[testcase] << "\n";
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

std::vector<int> GetPyramidSizes(int max_testcase) {
  std::vector<int> pyramid_sizes;
  int row = 1, slice = 1, pyramid = 1;
  while (pyramid <= max_testcase) {
    pyramid_sizes.push_back(pyramid);
    ++row;
    slice += row;
    pyramid += slice;
  }
  return pyramid_sizes;
}
