#include <cmath>
#include <cstdio>
#include <functional>
#include <iostream>
#include <iomanip>
#include <utility>

template <typename T>
struct Point {
  T x, y;
  Point(T x_, T y_) : x(x_), y(y_) {}
};

template <typename T>
inline T Distance(const Point<T>& first, const Point<T>& second);

template <typename T = int>
T TernarySearch(T lower_bound, T upper_bound, std::function<T(T)> unary_function, T precision = 3);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("forest.in", "r", stdin);
  std::freopen("forest.out", "w", stdout);

  int velocity_field, velocity_forest;
  long double field_forest_border;
  std::cin >> velocity_field >> velocity_forest >> field_forest_border;

  long double lower_bound = 0, upper_bound = 1, precision = 1e-10;
  auto unary_function = [&] (long double field_forest_change) -> long double {
    Point<long double> village(0, 1), change(field_forest_change, field_forest_border), meadow(1, 0);
    return -Distance(village, change) / velocity_field - Distance(change, meadow) / velocity_forest;
  };

  std::cout << std::fixed << std::setprecision(10) \
    << TernarySearch<long double>(lower_bound, upper_bound, unary_function, precision) << "\n";

  return 0;
}

template <typename T>
inline T Distance(const Point<T>& first, const Point<T>& second) {
  return sqrtl((first.x - second.x) * (first.x - second.x) + (first.y - second.y) * (first.y - second.y));
}

template <typename T>
T TernarySearch(T lower_bound, T upper_bound, std::function<T(T)> unary_function, T precision) {
  while (lower_bound + precision < upper_bound) {
    T left_middle = lower_bound + (upper_bound - lower_bound) / 3;
    T right_middle = upper_bound - (upper_bound - lower_bound) / 3;
    if (unary_function(left_middle) < unary_function(right_middle)) {
      lower_bound = left_middle;
    } else {
      upper_bound = right_middle;
    }
  }
  return lower_bound;
}
