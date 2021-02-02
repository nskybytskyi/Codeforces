#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

template <typename T = int>
std::vector<T> ReadArray(int size = 0, std::istream& in_stream = std::cin);

const int max_a = 1'001'000;

vector<int> sieve(max_a, 1);

// smallest prime divisor
void init_sieve() {
  iota(sieve.begin(), sieve.end(), 0);
  for (int d = 2; d * d < max_a; ++d) {
    if (sieve[d] == d) {  // prime
      for (int r = d * d; r < max_a; r += d) {
        sieve[r] = d;
      }
    }
  }
}

// n = p_1^a_1 * ... p_k^a_k -> p_1^(a_1 % 2) * ... * p_k^(a_k % 2)
int key(int n) {
  int smol = 1;
  while (n > 1) {
    int d = sieve[n];
    bool odd = false;
    while (n % d == 0) {
      odd = !odd;
      n /= d;
    }
    if (odd)
      smol *= d;
  }
  return smol;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  init_sieve();

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    auto a = ReadArray(n);

    // find all adjacent numbers after 0 moves
    unordered_map<int, int> f0;
    for (int ai : a) {
      ++f0[key(ai)];
    }

    int a0 = 0;
    for (auto [k, v] : f0) {
      a0 = max(a0, v);
    }

    // find all adjacent numbers after 1 move
    unordered_map<int, int> f1;
    for (auto [k, v] : f0) {
      if (v & 1) {
        f1[k] += v;
      } else {
        f1[1] += v;
      }
    }

    int a1 = 0;
    for (auto [k, v] : f1) {
      a1 = max(a1, v);
    }

    int q;
    cin >> q;
    while (q--) {
      int64_t w;
      cin >> w;
      if (!w) {
        cout << a0 << "\n";
      } else {
        cout << a1 << "\n";
      }
    }
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
