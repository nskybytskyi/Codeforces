#include <iostream>
#include <vector>

int ask(int left, int right) {
  std::cout << "?" << " " << left + 1 << " " << right + 1 << std::endl << std::flush;
  std::cout.flush();

  int answer;
  std::cin >> answer;
  return answer;
}

void answer(const std::vector<int>& array) {
  std::cout << "!";
  for (auto element : array) {
    std::cout << " " << element;
  }
  std::cout << std::endl << std::flush;
  std::cout.flush();
  exit(0);
}

int main() {
  int length;
  std::cin >> length;

  std::vector<int> array(length), prefix_sum(length);
  for (int right = 1; right < length; ++right) {
    prefix_sum[right] = ask(0, right);
    array[right] = prefix_sum[right] - prefix_sum[right - 1];
  }

  int special = ask(1, 2);
  array[0] = prefix_sum[2] - special;
  array[1] = prefix_sum[2] - array[0] - array[2];

  answer(array);

  return 0;
}
