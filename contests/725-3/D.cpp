#include <bits/stdc++.h>
using namespace std;
vector<int> sieve(int n) {
  vector<int> is_prime(n, true);
  is_prime[0] = is_prime[1] = false;
  for (int d = 2; d * d < n; ++d) {
    if (is_prime[d]) {
      for (int m = d * d; m < n; m += d) {
        is_prime[m] = false;
      }
    }
  }
  vector<int> primes;
  for (int i = 0; i < n; ++i) {
    if (is_prime[i]) {
      primes.push_back(i);
    }
  }
  return primes;
}
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  auto primes = sieve(31624);
  auto count_prime_divisors = [&] (int n) -> int {
    auto prime_divisors_count = 0;
    for (auto prime : primes) {
      if (n < prime) {
        break;
      }
      while (n % prime == 0) {
        n /= prime;
        ++prime_divisors_count;
      }
    }
    if (n > 1) {
      ++prime_divisors_count;
    }
    return prime_divisors_count;
  };
  // auto count_prime_divisors = [&] (int n) -> int {
  //   auto prime_divisors_count = 0;
  //   for (int d = 2; d * d <= n; ++d) {
  //     while (n % d == 0) {
  //       n /= d;
  //       ++prime_divisors_count;
  //     }
  //   }
  //   if (n > 1) {
  //     ++prime_divisors_count;
  //   }
  //   return prime_divisors_count;
  // };
  int t; cin >> t; while (t--) {
    int a, b, k; cin >> a >> b >> k;
    int max_operations_a = count_prime_divisors(a);
    int max_operations_b = count_prime_divisors(b);
    if (k > max_operations_a + max_operations_b) {
      cout << "No\n";
    } else if (k == 1) {
      if (a == b || ((a % b) && (b % a))) {
        cout << "No\n";
      } else {
        cout << "Yes\n";
      }
    } else {
      cout << "Yes\n";
    }
  }
  return 0;
}