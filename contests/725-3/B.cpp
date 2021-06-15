#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t; cin >> t; while (t--) {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& ai : a) cin >> ai;
    int sum = accumulate(a.begin(), a.end(), 0);
    if (sum % n) {
      cout << -1 << "\n";
    } else {
      int average = sum / n;
      int k = count_if(a.begin(), a.end(), [&] (int candies) -> bool {
        return candies > average;
      });
      cout << k << "\n";
    }
  }
  return 0;
}