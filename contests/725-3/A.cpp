#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t; cin >> t; while (t--) {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& ai : a) cin >> ai;
    int index_of_min = distance(a.begin(), min_element(a.begin(), a.end()));
    int index_of_max = distance(a.begin(), max_element(a.begin(), a.end()));
    int min_index = min(index_of_min, index_of_max);
    int max_index = max(index_of_min, index_of_max);
    cout << min({max_index + 1, n - min_index, (min_index + 1) + (n - max_index)}) << "\n";
  }
  return 0;
}