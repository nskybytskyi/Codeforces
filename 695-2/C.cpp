#include <algorithm>
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

  int n1, n2, n3;
  cin >> n1 >> n2 >> n3;
  const auto a1 = ReadArray(n1), a2 = ReadArray(n2), a3 = ReadArray(n3);

  const int64_t s1 = accumulate(a1.begin(), a1.end(), 0ll);
  const int64_t s2 = accumulate(a2.begin(), a2.end(), 0ll);
  const int64_t s3 = accumulate(a3.begin(), a3.end(), 0ll);

  const int64_t m1 = *min_element(a1.begin(), a1.end());
  const int64_t m2 = *min_element(a2.begin(), a2.end());
  const int64_t m3 = *min_element(a3.begin(), a3.end());

  cout << max(s1 + s2 + s3 - 2 * min(min(s1, s2), s3),
      s1 + s2 + s3 - 2 * (m1 + m2 + m3 - max(max(m1, m2), m3))) << "\n";

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
