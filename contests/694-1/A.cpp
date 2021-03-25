#include <algorithm>
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
    int n, m;
    cin >> n >> m;
    auto friends = ReadArray(n);
    for (auto& frend : friends)
      --frend;
    auto presents = ReadArray(m);

    sort(friends.begin(), friends.end(), greater<>());

    int present_id = 0;
    int64_t cost = 0;
    for (auto frend : friends) {
      if (present_id <= frend) {
        cost += presents[present_id];
        ++present_id;
      } else {
        cost += presents[frend];
      }
    }

    cout << cost << "\n";
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
