#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
  int64_t max;
  std::cin >> max;

  std::vector<int64_t> is_prime(max + 1, true);
  is_prime[0] = is_prime[1] = false;
  for (int64_t divisor = 2; divisor * divisor <= max; ++divisor) {
    if (is_prime[divisor]) {
      for (int64_t multiplier = divisor * divisor; multiplier <= max; multiplier += divisor) {
        is_prime[multiplier] = false;
      }
    }
  }

  std::vector<int64_t> primes;
  for (int64_t candidate = 0; candidate <= max; ++candidate) {
    if (is_prime[candidate]) {
      primes.push_back(candidate);
    }
  }

  const int64_t prime_count = primes.size();

  auto ask = [&] (int64_t divisor) -> int64_t {
    if (divisor > max) {
      return 0;
    } else {
      if (divisor == 1) {
        std::cout << "A" << " " << 1 << std::endl;
      } else {
        std::cout << "B" << " " << divisor << std::endl;
      }
      int64_t count;
      std::cin >> count;
      return count;
    }
  };

  auto answer = [] (int64_t secret) -> void {
    std::cout << "C" << " " << secret << std::endl;
    exit(0);
  };

  int64_t secret = 1;

  for (auto prime : primes) {  // O (sqrt(max) + log(max))
    if (prime * prime > max) {
      break;
    } else {
      ask(prime);
      int64_t power = prime;
      while (ask(power)) {
        power *= prime;
        secret *= prime;
      }
    }
  }

  if (secret == 1) {
    auto left = std::lower_bound(primes.begin(), primes.end(), max,
      [] (int64_t element, int64_t value) -> bool {
        return element * element <= value; 
      });
    auto right = primes.end();

    while (left != right) {
      auto length = std::distance(left, right);
      auto middle = std::next(left, (length + 1) >> 1);

      for (auto it = left; it != middle; ++it) {
        ask(*it);
      }

      if (ask(1) == std::distance(middle, right) + 1) {
        left = middle;
        continue;
      } else {
        for (auto it = left; it != middle; ++it) {
          if (ask(*it)) {
            secret *= *it;
          }
        }
        break;
      }
    }
  } else {
    for (auto prime : primes) {  // O (max / log(max))
      if (prime * prime > max) {
        if (ask(prime) == 2) {
          secret *= prime;
        }
      }
    }
  }

  answer(secret);

  return 0;
}
