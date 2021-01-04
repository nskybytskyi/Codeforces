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
    const auto array = ReadArray();
    const int length = array.size();
    vector<int64_t> best_suffix_score(array.size());
    for (int index = length - 1; index >= 0; --index) {
      best_suffix_score[index] = array[index];
      const int next_index = index + array[index];
      if (next_index < length) {
        best_suffix_score[index] += best_suffix_score[next_index];
      } 
    }
    cout << *max_element(best_suffix_score.begin(), best_suffix_score.end()) << "\n";
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
