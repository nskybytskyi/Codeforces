#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

std::pair<int, int> ask(const std::vector<int>& indices) {
  std::cout << "?";
  for (auto index : indices) {
    std::cout << " " << index + 1;
  }
  std::cout << std::endl << std::flush;
  std::cout.flush();

  int position, value;
  std::cin >> position >> value;
  if (position == -1) {
    exit(1);
  } else {
    return {position, value};
  }
}

void answer(int order) {
  std::cout << "!" << " " << order << std::endl << std::flush;
  std::cout.flush();
  exit(0);
}

int main() {
  int array_length, query_length;
  std::cin >> array_length >> query_length;
  int max = 0, count = 0;
  for (int leave_out = 0; leave_out <= query_length; ++leave_out) {
    std::vector<int> query(query_length);
    auto middle = std::next(query.begin(), leave_out);
    std::iota(query.begin(), middle, 0);
    std::iota(middle, query.end(), leave_out + 1);
    auto [position, value] = ask(query);
    if (value > max) {
      max = value;
      count = 1;
    } else if (value == max) {
      ++count;
    }
  }
  answer(count);
  return 0;
}
