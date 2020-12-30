#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <utility>
#include <vector>

const long double kInfinity = std::numeric_limits<long double>::max();

struct Point {
  int x, y;
};

using Edge = std::pair<int, int>;

inline long double Distance(const Point& first, const Point& second);

std::vector<Point> ReadPoints(int point_count, std::istream& in_stream = std::cin);

std::vector<Edge> PrimEMST(const std::vector<Point>& points);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("unionday.in", "r", stdin);
  std::freopen("unionday.out", "w", stdout);

  int point_count;
  std::cin >> point_count;

  const auto points = ReadPoints(point_count);
  const auto mst = PrimEMST(points);

  std::cout << std::fixed << std::setprecision(10) << \
    std::accumulate(mst.begin(), mst.end(), 0.,
      [&points] (long double accumulator, const Edge& edge) -> long double {
        return accumulator + Distance(points[edge.first], points[edge.second]);
      }) << "\n";

  return 0;
}

inline long double Distance(const Point& first, const Point& second) {
  return sqrtl((first.x - second.x) * 1. * (first.x - second.x) +
               (first.y - second.y) * 1. * (first.y - second.y));
}

std::vector<Point> ReadPoints(int point_count, std::istream& in_stream) {
  std::vector<Point> points(point_count);
  for (auto& point : points) {
    in_stream >> point.x >> point.y;
  }
  return points;
}

std::vector<Edge> PrimEMST(const std::vector<Point>& points) {
  const int point_count = points.size();
  std::vector<bool> used(point_count);
  std::vector<long double> min_edge(point_count, kInfinity);
  std::vector<int> selected_edge(point_count, -1);
  min_edge[0] = 0;  // start at first vertex 
  // can start anywhere, random is better on average
  std::vector<Edge> mst;

  const int iteration_count = point_count;
  for (int iteration = 0; iteration < iteration_count; ++iteration) {
    // select min edge vertex in O(n)
    int min_edge_vertex = -1;
    for (int vertex = 0; vertex < point_count; ++vertex) {
      if (!used[vertex]) {
        if (min_edge_vertex == -1 || min_edge[vertex] < min_edge[min_edge_vertex]) {
          min_edge_vertex = vertex;
        }
      }
    }

    // process the min edge vertex itself
    used[min_edge_vertex] = true;
    if (selected_edge[min_edge_vertex] != -1) {
      mst.emplace_back(min_edge_vertex, selected_edge[min_edge_vertex]);
    }

    // loop over all other vertices and update min and seleced edges
    for (int adjacent = 0; adjacent < point_count; ++adjacent) {
      const auto edge_length = Distance(points[min_edge_vertex], points[adjacent]);
      if (edge_length < min_edge[adjacent]) {
        min_edge[adjacent] = edge_length;
        selected_edge[adjacent] = min_edge_vertex;
      }
    }
  }

  return mst;
}
