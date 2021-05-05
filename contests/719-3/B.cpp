#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t, n;
  cin >> t;
  vector<int> a;
  for (int l = 1, p = 1; l <= 9; ++l, p = p * 10 + 1) {
    for (int d = 1; d <= 9; ++d) {
      a.push_back(d * p);
    }
  }
  while (t--) {
    cin >> n;
    cout << distance(a.begin(), upper_bound(a.begin(), a.end(), n)) << "\n";
  }
  return 0;
}