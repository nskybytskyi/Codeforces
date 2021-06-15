#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int p = 1, e = 0;
    while (p <= n) {
      ++e;
      p <<= 1;
    }
    cout << (p >> 1) - 1 << "\n";
  }
  return 0;
}
