#include <cstdio>
#include <functional>
#include <iostream>
#include <iomanip>
#include <utility>

inline long double Cubic(int a, int b, int c, int d, long double x);

template <typename T = int>
T BinarySearch(T lower_bound, T upper_bound, std::function<bool(T)> unary_predicate, T precision = 1);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("cubroot.in", "r", stdin);
  std::freopen("cubroot.out", "w", stdout);

  int a, b, c, d;
  std::cin >> a >> b >> c >> d;

  long double lower_bound = -10'000, upper_bound = 10'000, precision = 1e-10;
  auto unary_predicate = [&] (long double x) -> bool {
    // if (a > 0) {
    //   return Cubic(x) < 0;
    // } else {
    //   return Cubic(x) > 0;
    // }
    return (a > 0) ^ (Cubic(a, b, c, d, x) > 0);
  };

  std::cout << std::fixed << std::setprecision(10) \
    << BinarySearch<long double>(lower_bound, upper_bound, unary_predicate, precision) << "\n";

  return 0;
}

template <typename T>
T BinarySearch(T lower_bound, T upper_bound, std::function<bool(T)> unary_predicate, T precision) {
  while (lower_bound + precision < upper_bound) {
    T middle = lower_bound + (upper_bound - lower_bound) / 2;
    if (unary_predicate(middle)) {
      lower_bound = middle;
    } else {
      upper_bound = middle;
    }
  }
  return lower_bound;
}

inline long double Cubic(int a, int b, int c, int d, long double x) {
  return a * x * x * x + b * x * x + c * x + d;
}
