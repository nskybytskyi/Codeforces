#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int testcase_count;
  std::cin >> testcase_count;
  while (testcase_count --> 0) {
    int program_length, query_count;
    std::string program;
    std::cin >> program_length >> query_count >> program;

    std::vector<int> prefix_minimum = {0}, prefix_maximum = {0}, prefix_current = {0},
      suffix_minimum = {0}, suffix_maximum = {0}, suffix_current = {0};

    for (auto command : program) {
      if (command == '+') {
        prefix_current.push_back(prefix_current.back() + 1);
      } else{
        prefix_current.push_back(prefix_current.back() - 1);
      }
      prefix_minimum.push_back(std::min(prefix_minimum.back(), prefix_current.back()));
      prefix_maximum.push_back(std::max(prefix_maximum.back(), prefix_current.back()));
    }

    std::reverse(program.begin(), program.end());
    for (auto command : program) {
      if (command == '+') {
        suffix_current.push_back(suffix_current.back() + 1);
      } else {
        suffix_current.push_back(suffix_current.back() - 1);
      }
      suffix_minimum.push_back(std::min(suffix_minimum.back(), suffix_current.back()));
      suffix_maximum.push_back(std::max(suffix_maximum.back(), suffix_current.back()));
    }

    std::reverse(program.begin(), program.end());
    std::reverse(suffix_current.begin(), suffix_current.end());
    std::reverse(suffix_minimum.begin(), suffix_minimum.end());
    std::reverse(suffix_maximum.begin(), suffix_maximum.end());;

    while (query_count--) {
      int left, right;
      std::cin >> left >> right;
      --left;

      const int minimum = std::min(prefix_minimum[left],
        prefix_current[left] + suffix_current[right] - suffix_maximum[right]);
      const int maximum = std::max(prefix_maximum[left],
        prefix_current[left] + suffix_current[right] - suffix_minimum[right]);

      std::cout << maximum + 1 - minimum << "\n";
    }
  }

  return 0;
}
