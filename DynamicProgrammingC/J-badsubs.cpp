#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  // std::freopen("badsubs.in", "r", stdin);
  // std::freopen("badsubs.out", "w", stdout);

  int length;
  std::cin >> length;

  if (!length) {
    std::cout << 1 << "\n";
  } else {
    std::unordered_map<char, std::vector<int>> count_strings_with_last_letter_length;
    for (char letter = 'a'; letter <= 'c'; ++letter) {
      count_strings_with_last_letter_length[letter].resize(length);
      count_strings_with_last_letter_length[letter][0] = 1;
    }

    for (int prefix_length = 1; prefix_length < length; ++prefix_length) {
      count_strings_with_last_letter_length['a'][prefix_length] \
        = count_strings_with_last_letter_length['a'][prefix_length - 1] \
        + count_strings_with_last_letter_length['b'][prefix_length - 1] \
        + count_strings_with_last_letter_length['c'][prefix_length - 1];
      count_strings_with_last_letter_length['b'][prefix_length] \
        = count_strings_with_last_letter_length['b'][prefix_length - 1] \
        + count_strings_with_last_letter_length['c'][prefix_length - 1];
      count_strings_with_last_letter_length['c'][prefix_length] \
        = count_strings_with_last_letter_length['a'][prefix_length - 1] \
        + count_strings_with_last_letter_length['b'][prefix_length - 1] \
        + count_strings_with_last_letter_length['c'][prefix_length - 1];
    }

    std::cout << count_strings_with_last_letter_length['a'][length - 1] \
      + count_strings_with_last_letter_length['b'][length - 1] \
      + count_strings_with_last_letter_length['c'][length - 1] << "\n";
  }

  return 0;
}
