#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t, n, ai;
  cin >> t;
  while (t--) {
    cin >> n;
    map<int, int> m;
    int64_t c = 0;
    for (int i = 0; i < n; ++i) {
      cin >> ai;
      c += m[ai - i];
      ++m[ai - i];
    }
    cout << c << "\n";
  }
  return 0;
}