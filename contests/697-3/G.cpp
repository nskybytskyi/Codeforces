#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <numeric>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

template <typename T = int64_t>
std::vector<T> ReadArray(int64_t size = 0, std::istream& in_stream = std::cin);

const int64_t kMax = 200'200;

vector<int64_t> prime_divisor(kMax);

void init(int64_t n = kMax) {
  iota(prime_divisor.begin(), prime_divisor.end(), 0);
  for (int64_t d = 2; d * d < n; ++d) {
    if (prime_divisor[d] == d) {
      for (int64_t m = d * d; m < n; m += d) {
        prime_divisor[m] = d;
      }
    }
  }
}

vector<int64_t> divisors(int64_t n) {
  vector<int64_t> divs;
  while (n > 1) {
    divs.push_back(prime_divisor[n]);
    n /= prime_divisor[n];
  }
  return divs;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  init();

  int64_t t;
  cin >> t;
  while (t--) {
    int64_t n;
    cin >> n;
    auto a = ReadArray(n);
    vector<int64_t> f(kMax);
    for (auto ai : a)
      ++f[ai];
    vector<int64_t> dp(kMax);
    for (int64_t i = 0; i < kMax; ++i) {
      for (auto d : divisors(i)) {
        dp[i] = max(dp[i], dp[i / d]);
      }
      dp[i] += f[i];
    }
    cout << n - *max_element(dp.begin(), dp.end()) << "\n";
  }

  return 0;
}

template <typename T>
std::vector<T> ReadArray(int64_t size, std::istream& in_stream) {
  if (!size) {
    in_stream >> size;
  }
  std::vector<T> array(size);
  for (auto& element : array) {
    in_stream >> element;
  }
  return array;
}
