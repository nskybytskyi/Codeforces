#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int64_t n, k;
    cin >> n >> k;
    vector<int64_t> x(n);
    for (auto& xi : x)
      cin >> xi;

    int64_t g = 0;
    for (int i = 0; i + 1 < n; ++i)
      g = gcd(g, x[i + 1] - x[i]);

    int64_t r1 = x[0] % g;
    if (r1 < 0)
      r1 += g;
    int64_t r2 = k % g;
    if (r2 < 0)
      r2 += g;
    if (r1 != r2) {
      cout << "NO\n";
    } else {
      cout << "YES\n";
    }
  }

  return 0;
}
