#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    string a, b, c;
    cin >> a >> b >> c;
    const int n = a.length();
    bool possible = true;
    for (int i = 0; i < n; ++i) {
      possible &= b[i] == c[i] || a[i] == c[i];
    }
    cout << (possible ? "YES" : "NO") << "\n";
  }

  return 0;
}
