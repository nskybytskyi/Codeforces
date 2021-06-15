#include <bits/stdc++.h>
using namespace std;
void B1(int n, string& s) {
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
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    string s;
    cin >> n >> s;
    int k = n >> 1;
    int zz = 0, zo = 0, oo = 0;
    for (int i = 0; i < k; ++i) {
      if (s[i] == '0') {
        if (s[n - 1 - i] == '0') {
          ++zz;
        } else {
          ++zo;
        }
      } else {
        if (s[n - 1 - i] == '0') {
          ++zo;
        } else {
          ++oo;
        }
      }
    }
    if (!zo) {
      B1(n, s);
    } else {
      if ((n & 1) && s[k] == '0') {
        if (zo == 1) {
          if (zz) {
            cout << "ALICE\n";
          } else {
            cout << "DRAW\n";
          }
        } else {
          cout << "ALICE\n";
        }
      } else {
        if (zo == 1) {
          cout << "ALICE\n";
        } else {
          cout << "ALICE\n";
        }
      }
    }
  }
  return 0;
}
