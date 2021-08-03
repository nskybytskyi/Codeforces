#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0);
  int t; cin >> t; while (t--) {
    int n, m, h;
    cin >> n >> m >> h;
    int v = (n * m) / 2 - h;
    if (n & 1) {
      if ((v & 1) || (h < m / 2)) {
        cout << "NO" << "\n";
      } else {
        cout << "YES" << "\n";
      }
    } else if (m & 1) {
      if ((h & 1) || (v < n / 2)) {
        cout << "NO" << "\n";
      } else {
        cout << "YES" << "\n";
      }
    } else {
      assert((h & 1) == (v & 1));
      if (h & 1) {
        cout << "NO" << "\n";
      } else {
        cout << "YES" << "\n";
      }
    }
  }
  return 0;
}