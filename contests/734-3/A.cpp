#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0);
  int t; cin >> t; while (t--) {
    int n;
    cin >> n;
    auto [q, r] = div(n, 3);
    if (r == 0) {
      cout << q << " " << q << "\n";
    } else if (r == 1) {
      cout << q + 1 << " " << q << "\n";
    } else {  // r == 2
      cout << q << " " << q + 1 << "\n";
    }
  }
  return 0;
}