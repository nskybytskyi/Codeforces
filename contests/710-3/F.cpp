#include <bits/stdc++.h>
using namespace std;

using Point = pair<int64_t, int64_t>;

int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

  int64_t t;
  cin >> t;
  while (t--) {
    int64_t n;
    cin >> n;
    vector<Point> rc(n);
    for (auto& [r, c] : rc) {
      cin >> r;
    }
    for (auto& [r, c] : rc) {
      cin >> c;
    }

    rc.emplace_back(1, 1);
    sort(rc.begin(), rc.end());

    auto cost = [&] (const Point& source, const Point& destination) -> int64_t {
      const auto source_diagonal = source.first - source.second;
      const auto destination_diagonal = destination.first - destination.second;
      const auto diagonal_distance = destination_diagonal - source_diagonal;
      if (source_diagonal & 1) {
        return (diagonal_distance + 1) / 2;
      } else {
        if (destination_diagonal == source_diagonal) {
          return destination.first - source.first;
        } else {
          return diagonal_distance / 2;
        }
      }
    };

    int64_t min_cost = 0;
    for (int64_t i = 0; i < n; ++i) {
      min_cost += cost(rc[i], rc[i + 1]);
    }
    cout << min_cost << "\n";
  }

  return 0;
}
