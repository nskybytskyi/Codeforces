#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);    
  int t;
  cin >> t;
  while (t--) {
    int n, u, r, d, l;
    cin >> n >> u >> r >> d >> l;
    if ((d == n || u == n) && (!l || !r)) {
      cout << "NO"; 
    } else if ((l == n || r == n) && (!d || !u)) {
      cout << "NO";
    } else if ((d == n - 1 || u == n - 1) && !l && !r) {
      cout << "NO";
    } else if ((l == n - 1 || r == n - 1) && !d && !u) {
      cout << "NO";
    } else {
      vector<int> c = {0, 0, 0, 0, 0, 0};
      if (u == n) {
        --c[1];
        --c[3];
      } else if (u == n - 1) {
        ++c[5];
      }
      if (d == n) {
        --c[1];
        --c[3];
      } else if (d == n - 1) {
        ++c[5];
      }
      if (l == n) {
        --c[0];
        --c[2];
      } else if (l == n - 1) {
        ++c[4];
      }
      if (r == n) {
        --c[0];
        --c[2];
      } else if (r == n - 1) {
        ++c[4];
      }
      u += c[0];
      r += c[1];
      d += c[2];
      l += c[3];
      if (u < 0 || r < 0 || d < 0 || l < 0 ||
          l + r < c[5] || u + d < c[4]) {
        cout << "NO";
      } else {
        cout << "YES";
      }
    }
    cout << "\n";
  }
  return 0;
}
