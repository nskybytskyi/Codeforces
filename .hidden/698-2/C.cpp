#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int testcase_count;
  std::cin >> testcase_count;
  while (testcase_count --> 0) {
    int half_length;
    std::cin >> half_length;
    int array_length = half_length << 1;
    std::vector<int64_t> differences(array_length), half(half_length), past(half_length);
    for (auto& difference : differences) {
      std::cin >> difference;
    }
    std::sort(differences.begin(), differences.end(), std::greater<>());
    bool possible = true;
    for (int i = 0; i < half_length && possible; ++i) {
      half[i] = differences[i << 1];
      if (differences[i << 1] != differences[(i << 1) | 1]) {
        possible = false;
      }
    }
    for (int i = 1; i < half_length && possible; ++i) {
      if (half[i - 1] == half[i]) {
        possible = false;
      }
      const int mod = array_length - (i << 1);
      if ((half[i - 1] - half[i]) % mod) {
        possible = false;
      } else {
        past[i] = (half[i - 1] - half[i]) / mod;
      }
    }
    for (int i = 1; i < half_length; ++i) {
      half.back() -= (i * past[i]) << 1;
    }
    if (half.back() <= 0 || half.back() % array_length) {
      possible = false;
    }
    if (!possible) {
      std::cout << "NO\n";
    } else {
      std::cout << "YES\n";
    }
  }

  return 0;
}
