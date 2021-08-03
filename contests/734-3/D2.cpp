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
        vector<string> a(n, string(m, '$'));
        for (int j = 0; j < m; j += 2) {
          if ((j / 2) & 1) {
            a[0][j] = 'e';
            a[0][j + 1] = 'e';
            --h;
          } else {
            a[0][j] = 'f';
            a[0][j + 1] = 'f';
            --h;
          }
        }
        for (int i = 1; i < n; i += 2) {
          for (int j = 0; j < m; j += 2) {
            if (h) {
              if ((i / 2 + j / 2) & 1) {
                a[i][j] = 'a';
                a[i][j + 1] = 'a';
                --h;
                a[i + 1][j] = 'b';
                a[i + 1][j + 1] = 'b';
                --h;
              } else {
                a[i][j] = 'g';
                a[i][j + 1] = 'g';
                --h;
                a[i + 1][j] = 'h';
                a[i + 1][j + 1] = 'h';
                --h;
              }
            } else {
              if ((i / 2 + j / 2) & 1) {
                a[i][j] = 'c';
                a[i + 1][j] = 'c';
                a[i][j + 1] = 'd';
                a[i + 1][j + 1] = 'd';
              } else {
                a[i][j] = 'i';
                a[i + 1][j] = 'i';
                a[i][j + 1] = 'j';
                a[i + 1][j + 1] = 'j';
              }
            }
          }
        }
        for (auto ai : a) {
          cout << ai << "\n";
        }
      }
    } else if (m & 1) {
      if ((h & 1) || (v < n / 2)) {
        cout << "NO" << "\n";
      } else {
        cout << "YES" << "\n";
        vector<string> a(n, string(m, '$'));
        for (int i = 0; i < n; i += 2) {
          if ((i / 2) & 1) {
            a[i][0] = 'e';
            a[i + 1][0] = 'e';
          } else {
            a[i][0] = 'f';
            a[i + 1][0] = 'f';
          }
        }
        for (int i = 0; i < n; i += 2) {
          for (int j = 1; j < m; j += 2) {
            if (h) {
              if ((i / 2 + j / 2) & 1) {
                a[i][j] = 'a';
                a[i][j + 1] = 'a';
                --h;
                a[i + 1][j] = 'b';
                a[i + 1][j + 1] = 'b';
                --h;
              } else {
                a[i][j] = 'g';
                a[i][j + 1] = 'g';
                --h;
                a[i + 1][j] = 'h';
                a[i + 1][j + 1] = 'h';
                --h;
              }
            } else {
              if ((i / 2 + j / 2) & 1) {
                a[i][j] = 'c';
                a[i + 1][j] = 'c';
                a[i][j + 1] = 'd';
                a[i + 1][j + 1] = 'd';
              } else {
                a[i][j] = 'i';
                a[i + 1][j] = 'i';
                a[i][j + 1] = 'j';
                a[i + 1][j + 1] = 'j';
              }
            }
          }
        }
        for (auto ai : a) {
          cout << ai << "\n";
        }
      }
    } else {
      assert((h & 1) == (v & 1));
      if (h & 1) {
        cout << "NO" << "\n";
      } else {
        cout << "YES" << "\n";
        vector<string> a(n, string(m, '$'));
        for (int i = 0; i < n; i += 2) {
          for (int j = 0; j < m; j += 2) {
            if (h) {
              if ((i / 2 + j / 2) & 1) {
                a[i][j] = 'a';
                a[i][j + 1] = 'a';
                --h;
                a[i + 1][j] = 'b';
                a[i + 1][j + 1] = 'b';
                --h;
              } else {
                a[i][j] = 'g';
                a[i][j + 1] = 'g';
                --h;
                a[i + 1][j] = 'h';
                a[i + 1][j + 1] = 'h';
                --h;
              }
            } else {
              if ((i / 2 + j / 2) & 1) {
                a[i][j] = 'c';
                a[i + 1][j] = 'c';
                a[i][j + 1] = 'd';
                a[i + 1][j + 1] = 'd';
              } else {
                a[i][j] = 'i';
                a[i + 1][j] = 'i';
                a[i][j + 1] = 'j';
                a[i + 1][j + 1] = 'j';
              }
            }
          }
        }
        for (auto ai : a) {
          cout << ai << "\n";
        }
      }
    }
  }
  return 0;
}