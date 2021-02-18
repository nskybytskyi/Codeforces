#include <bits/stdc++.h>
using namespace std;
int64_t power(int64_t x) {
  return x * x * x * x;
}
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int n, m;
  cin >> n >> m;
  vector<vector<int64_t>> a(n, vector<int64_t>(m));
  for (auto& ai : a) {
    for (auto& aij : ai) {
      cin >> aij;
    }
  }
  vector<vector<int64_t>> b(n, vector<int64_t>(m, 720'720));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if ((i + j) & 1) {
        b[i][j] += power(a[i][j]);
      }
    }
  }
  for (auto bi : b) {
    for (auto bij : bi) {
      cout << bij << " ";
    }
    cout << "\n";
  }
  return 0;
}
