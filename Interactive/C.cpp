#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int ask(int dividend_index, int divisor_index) {
  std::cout << "?" << " " << dividend_index + 1 << " " << divisor_index + 1 << std::endl << std::flush;
  std::cout.flush();

  int remainder;
  std::cin >> remainder;
  return remainder;
}

void answer(const std::vector<int>& permutation) {
  std::cout << "!";
  for (auto element : permutation) {
    std::cout << " " << element;
  }
  std::cout << std::endl << std::flush;
  std::cout.flush();
  exit(0);
}

int main() {
  int length;
  std::cin >> length;

  std::vector<int> permutation(length);

  auto helper = [&] (int first_index, int second_index) -> std::pair<bool, int> {
    auto first_remainder = ask(first_index, second_index);
    auto second_remainder = ask(second_index, first_index);
    if (first_remainder > second_remainder) {
      return {true, first_remainder};
    } else {
      return {false, second_remainder};
    }
  };

  int first_index = 0, second_index = length - 1;
  while (first_index < second_index) {
    auto [move_first, value] = helper(first_index, second_index);
    if (move_first) {
      permutation[first_index] = value;
      ++first_index;
    } else {
      permutation[second_index] = value;
      --second_index;
    }
  }

  *std::find(permutation.begin(), permutation.end(), 0) = length;
  answer(permutation);

  return 0;
}
