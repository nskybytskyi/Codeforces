#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int64_t> x(n), y(n);
    for (int i = 0; i < n; ++i) {
      cin >> x[i] >> y[i];
    }
    if (n & 1) {
      cout << "1\n";
    } else {
      sort(x.begin(), x.end());
      sort(y.begin(), y.end());
      int k = n >> 1;
      cout << (x[k] - x[k - 1] + 1) * (y[k] - y[k - 1] + 1) << "\n";
    }
  }
  return 0;
}
