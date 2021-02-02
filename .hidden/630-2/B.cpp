#include <algorithm>
#include <iostream>
#include <iterator>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  unordered_map<int, int> colors = {
    {2, 1}, {3, 2}, {5, 3}, {7, 4},
    {11, 5}, {13, 6}, {17, 7}, {19, 8},
    {23, 9}, {29, 10}, {31, 11}
  };

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& ai : a)
      cin >> ai;

    unordered_set<int> used;
    vector<int> c(n);
    for (int i = 0; i < n; ++i)
      for (const auto& [prime, color] : colors)
        if (a[i] % prime == 0) {
          c[i] = color;
          used.insert(color);
          break;
        }

    vector<int> id(used.begin(), used.end());
    for (int i = 0; i < n; ++i) {
      const auto it = find(id.begin(), id.end(), c[i]);
      c[i] = distance(id.begin(), it) + 1;
    }

    cout << used.size() << "\n";
    for (auto ci : c)
      cout << ci << " ";
    cout << "\n";
  }

  return 0;
}
