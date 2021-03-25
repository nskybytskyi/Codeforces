#include <algorithm>
#include <iostream>
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
    auto array = ReadArray();
    sort(array.begin(), array.end(), greater<>());

    int64_t score_difference = 0;

    bool alice_turn = true;
    for (auto element : array) {
      if (alice_turn) {
        if (!(element & 1)) {
          score_difference += element;
        }
      } else {
        if (element & 1) {
          score_difference -= element;
        }
      } 
      alice_turn = !alice_turn;
    }

    if (score_difference < 0) {
      cout << "Bob\n";
    } else if (score_difference == 0) {
      cout << "Tie\n";
    } else {  // score_difference > 0
      cout << "Alice\n";
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
