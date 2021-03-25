#include <iostream>
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
    int w, h, n, k = 1;
    cin >> w >> h >> n;
    while (!(w & 1)) {
      w >>= 1;
      k <<= 1;
    }
    while (!(h & 1)) {
      h >>= 1;
      k <<= 1;
    }
    if (k >= n) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
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
