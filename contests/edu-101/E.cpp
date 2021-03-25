#include <algorithm>
#include <cmath>
#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int testcase_count;
  std::cin >> testcase_count;
  while (testcase_count --> 0) {
    int length, substring_length;
    std::string string;
    std::cin >> length >> substring_length >> string;
    std::vector<int> prefix_ones = {0};
    for (auto bit : string) {
      if (bit == '1') {
        prefix_ones.push_back(prefix_ones.back() + 1);
      } else {
        prefix_ones.push_back(prefix_ones.back());
      }
    }
    const int substring_count = length - substring_length + 1;
    const int suffix_length = std::min(substring_length,
      (int)std::log2(substring_count + 1) + 1);
    std::vector<int> banned_suffixes(1 << suffix_length);
    for (int last = length; last >= substring_length; --last) {
      if (prefix_ones[last - suffix_length] - prefix_ones[last - substring_length] == \
          substring_length - suffix_length) {
        int banned_suffix = 0;
        for (auto& bit : string.substr(last - suffix_length, suffix_length)) {
          banned_suffix <<= 1;
          if (bit == '0') {
            ++banned_suffix; 
          }
        }
        banned_suffixes[banned_suffix] = true;
      }
    }
    std::string answer = std::string(substring_length - suffix_length, '0');
    bool found = false;
    for (int bitmask = 0; (bitmask < (1 << suffix_length)) && !found; ++bitmask) {
      int suffix = 0;
      for (int bit = 0; bit < suffix_length; ++bit) {
        if (bitmask & (1 << bit)) {
          suffix |= 1 << bit;
        }
      }
      if (!banned_suffixes[suffix]) {
        found = true;
        for (int bit = suffix_length - 1; bit >= 0; --bit) {
          if (bitmask & (1 << bit)) {
            answer += '1';
          } else {
            answer += '0';
          }
        }
      }
    }
    if (found) {
      std::cout << "YES\n" << answer << "\n";
    } else {
      std::cout << "NO\n";
    }
  }

  return 0;
}
