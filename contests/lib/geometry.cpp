#include <iostream>
#include <iomanip>
#include <vector>

template <typename T>
void Read(std::vector<T>& vector) {
  for (auto& element : vector) {
    Read(element);
  }
}

#include "geometry.h"

template <typename First, typename... Rest>
void Read(First& first, Rest&... rest) {
  Read(first);
  Read(rest...);
}

void problem_a() {
  std::freopen("angle1.in", "r", stdin);
  std::freopen("angle1.out", "w", stdout);
  Point point;
  Read(point);
  std::cout << std::fixed << std::setprecision(6)
    << Angle(point) << "\n";
}

void problem_b() {
  std::freopen("angle2.in", "r", stdin);
  std::freopen("angle2.out", "w", stdout);
  Point first, second;
  Read(first, second);
  std::cout << std::fixed << std::setprecision(6)
    << Angle(first, second) << "\n";
}

void problem_c() {
  std::freopen("area.in", "r", stdin);
  std::freopen("area.out", "w", stdout);
  int vertex_count;
  std::cin >> vertex_count;
  std::vector<Point> points(vertex_count);
  Read(points);
  std::cout << std::fixed << std::setprecision(6)
    << Area(points) << "\n";
}

void problem_d() {
  std::freopen("area1.in", "r", stdin);
  std::freopen("area1.out", "w", stdout);
  Point first, second, third;
  Read(first, second, third);
  std::cout << std::fixed << std::setprecision(6)
    << Area(first, second, third) << "\n";
}

void problem_e() {
  std::freopen("bisector.in", "r", stdin);
  std::freopen("bisector.out", "w", stdout);
  Point first, second, third;
  Read(first, second, third);
  std::cout << std::fixed << std::setprecision(6)
    << Area(first, second, third) << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  // problem_a();
  // problem_b();
  // problem_c();
  // problem_d();

  return 0;
}
