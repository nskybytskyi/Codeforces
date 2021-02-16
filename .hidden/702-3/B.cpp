#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& ai : a)
      cin >> ai;
    vector<int> c(3);
    for (auto ai : a)
      ++c[ai % 3];
    int eq = n / 3;
    int ops = 0;
    for (int i = 0; i < 9; ++i) {
      if (c[i % 3] > eq) {
        int diff = c[i % 3] - eq;
        ops += diff;
        c[i % 3] -= diff;
        c[(i + 1) % 3] += diff;
      }
    }
    cout << ops << "\n";
  }
  return 0;
}
