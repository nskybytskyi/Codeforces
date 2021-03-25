#include <algorithm>
#include <iostream>
#include <functional>
#include <vector>

template <typename T = int>
std::vector<T> ReadArray(int size = 0, std::istream& in_stream = std::cin);

const int kMod = 1'000'000'007;

int modmul(int64_t first, int64_t second, int mod = kMod) {
  return (first * second) % mod;
}

int binmodpow(int64_t base, int64_t power, int mod = kMod) {
  int64_t result = 1;
  while (power) {
    if (power & 1)
      result = modmul(result, base, mod);
    base = modmul(base, base, mod);
    power >>= 1;
  }
  return result;
}

inline int modinv(int base, int mod = kMod) {
  return binmodpow(base, mod - 2, mod);
}

int moddiv(int numerator, int denominator, int mod = kMod) {
  return modmul(numerator, modinv(denominator, mod), mod);
}

std::vector<int> modular_factorial = {1};

void init(int bloggers_count = 10000) {
  for (int i = 1; i <= bloggers_count; ++i)
    modular_factorial.push_back(modmul(modular_factorial.back(), i));
}

int Binom(int bloggers_count, int k) {
  return moddiv(modular_factorial[bloggers_count],
    modmul(modular_factorial[k], modular_factorial[bloggers_count - k]));
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  init();

  int t;
  std::cin >> t;
  while (t --> 0) {
    int bloggers_count, places;
    std::cin >> bloggers_count >> places;

    auto follower_counts = ReadArray(bloggers_count);
    std::sort(follower_counts.begin(), follower_counts.end(), std::greater<>());

    const int marginal = std::count(follower_counts.begin(), follower_counts.end(), follower_counts[places - 1]);
    places -= std::count_if(follower_counts.begin(), follower_counts.end(),
      [&] (int follower_count) { return follower_count > follower_counts[places - 1]; });

    std::cout << Binom(marginal, places) << "\n";
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
