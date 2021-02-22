#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

struct Point {
  int64_t id, x, y;
  Point(int64_t id_, int64_t x_ = 0, int64_t y_ = 0) 
    : id(id_), x(x_), y(y_) { }
  bool operator==(const Point& other) const {
    return id == other.id;
  }
  bool operator<(const Point& other) const {
    return id < other.id;
  }
};

inline int64_t Distance(const Point& p, const Point& q) {
  return (p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int point_count;
  std::cin >> point_count;
  std::set<Point> points;
  for (int id = 0; id < point_count; ++id) {
    Point point(id);
    std::cin >> point.x >> point.y;
    points.insert(point);
  }
  std::vector<int> permutation = {0};
  permutation.reserve(point_count);
  Point previous_point = *points.find(Point(0));
  points.erase(previous_point);
  for (int iteration = 1; iteration < point_count; ++iteration) {
    previous_point = *std::max_element(points.begin(), points.end(),
      [&] (const Point& p, const Point& q) -> int64_t {
        return Distance(previous_point, p) < Distance(previous_point, q);
      });
    permutation.push_back(previous_point.id);
    points.erase(previous_point);
  }
  for (auto& index : permutation) {
    std::cout << index + 1 << " ";
  }
  std::cout << "\n";

  return 0;
}
