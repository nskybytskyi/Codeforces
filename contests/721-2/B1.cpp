#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    string s;
    cin >> n >> s;
    if (s == string(n, '1')) {
      cout << "DRAW\n";
    } else if (n & 1) {
      int k = n >> 1;
      if (s[k] == '0') {
        s[k] = '1';
        if (s == string(n, '1')) {
          cout << "BOB\n";
        } else {
          cout << "ALICE\n";
        }
      } else {
        cout << "BOB\n";
      }
    } else {
      cout << "BOB\n";
    }
  }
  return 0;
}
