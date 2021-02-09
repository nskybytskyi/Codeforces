#include <array>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <utility>

int ask(int first, int second) {
  std::cout << "?" << " " << first + 1 << " " << second + 1 << std::endl << std::flush;
  std::cout.flush();

  int answer;
  std::cin >> answer;
  return answer;
}

void answer(const std::array<int, 6>& array) {
  std::cout << "!";
  for (auto element : array) {
    std::cout << " " << element;
  }
  std::cout << std::endl << std::flush;
  std::cout.flush();
  exit(0);
}

int main() {
  std::unordered_map<int, std::pair<int, int>> product_to_pair;
  std::array<int, 6> array = {4, 8, 15, 16, 23, 42};
  for (int first = 0; first < 6; ++first) {
    for (int second = 0; second < first; ++second) {
      product_to_pair[array[first] * array[second]] = {array[first], array[second]};
    }
  }

  auto helper = [&] (int i) -> std::tuple<int, int, int> {
    auto [a, b] = product_to_pair[ask(i, i + 1)];
    auto [c, d] = product_to_pair[ask(i + 1, i + 2)];
    if (b == d) {
      return {a, b, c};
    } else if (b == c) {
      return {a, b, d};
    } else if (a == d) {
      return {b, d, c};
    } else {  // a == c
      return {b, c, d};
    }
  };

  for (auto i : {0, 3}) {
    std::tie(array[i], array[i + 1], array[i + 2]) = helper(i);
  }
  answer(array);

  return 0;
}
