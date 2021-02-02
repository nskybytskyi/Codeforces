#define M_PI 3.14159265358979323846264338327950288 /* pi */

#include <iostream>
#include <cmath>
#include <vector>

struct Point {
  long double x, y;

  Point() { }

  Point(long double x, long double y) : x(x), y(y) { }

  inline Point& operator+=(const Point& other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  inline Point& operator-=(const Point& other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  inline Point& operator*=(long double t) {
    x *= t;
    y *= t;
    return *this;
  }

  inline Point& operator/=(long double t) {
    x /= t;
    y /= t;
    return *this;
  }

  inline Point operator+(const Point& other) {
    return Point(*this) += other;
  }

  inline Point operator-(const Point& other) {
    return Point(*this) -= other;
  }

  inline Point operator*(long double t) {
    return Point(*this) *= t;
  }

  inline Point operator/(long double t) {
    return Point(*this) /= t;
  }
};

// a x + by = c
struct Line {
  long double a, b, c;

  Line() { }

  Line(long double a, long double b, long double c) : a(a), b(b), c(c) { }
};

void Read(Point& point) {
  std::cin >> point.x >> point.y;
}

// x O point, [0, 2 pi)
inline auto Angle(const Point& point) {
  auto angle = std::atan2l(point.y, point.x);
  if (angle < 0) {
    angle += 2 * M_PI;
  }
  return angle;
}

// first O second, [0, pi]
inline auto Angle(const Point& first, const Point& second) {
  auto angle = std::fabsl(Angle(first) - Angle(second));
  if (angle > M_PI) {
    angle = 2 * M_PI - angle;
  }
  return angle;
}

inline auto SignedArea(const Point& first, const Point& second, const Point& third) {
  return ((second.x - first.x) * (third.y - first.y) 
    - (second.y - first.y) * (third.x - first.x)) / 2.0;
}

// unsigned
inline auto Area(const Point& first, const Point& second, const Point& third) {
  return std::fabsl(SignedArea(first, second, third));
}

// vectices in sorted order
inline auto Area(const std::vector<Point>& polygon) {
  const int vertex_count = polygon.size();
  const Point origin(0.0, 0.0);
  long double area = SignedArea(polygon[vertex_count - 1], origin, polygon[0]);
  for (int i = 0; i + 1 < vertex_count; ++i) {
    area += SignedArea(polygon[i], origin, polygon[i + 1]);
  }
  return area;
}
