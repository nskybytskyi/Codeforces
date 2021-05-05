#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t, n;
  cin >> t;
  while (t--) {
    cin >> n;
    if (n == 1) {
      cout << 1 << "\n";
    } else if (n == 2) {
      cout << -1 << "\n";
    } else if (n == 3) {
      cout << "2 9 7\n4 6 3\n1 8 5\n";
    } else if (n == 4) {
      cout << "1 9 2 10\n11 3 12 4\n5 13 6 14\n15 7 16 8\n";
    } else {
      vector<vector<int>> a(n, vector<int>(n));
      int val = 1;
      for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; col += 2) {
          a[row][col] = val++;
        }
        for (int col = 1; col < n; col += 2) {
          a[row][col] = val++;
        }
      }
      for (const auto& row : a) {
        for (auto val : row) {
          cout << val << " ";
        }
        cout << "\n";
      }
    }
  }
  return 0;
}