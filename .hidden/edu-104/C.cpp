#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    if (n & 1) {  // odd
      int half = n >> 1;
      for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        for (int k = 0; k < half; ++k, j = (j + 1) % n) {
          a[i][j] = 1;
        }
        for (int k = 0; k < half; ++k, j = (j + 1) % n) {
          a[i][j] = -1;
        }
      }
    } else {  // even
      int half = (n >> 1) - 1;
      for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        for (int k = 0; k < half; ++k, j = (j + 1) % n) {
          a[i][j] = 1;
        }
        a[i][j] = 0;
        j = (j + 1) % n;
        for (int k = 0; k < half; ++k, j = (j + 1) % n) {
          a[i][j] = -1;
        }
      }
    }

    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        cout << a[i][j] << " ";
      }
    }
    cout << "\n";
  }

  return 0;
}
