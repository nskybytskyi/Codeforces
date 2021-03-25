#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int n, m;
  string s, t;
  cin >> n >> m >> s >> t;
  vector<int> l(m), r(m);
  for (int i = 0, j = 0; i < m; ++i, ++j) {
    while (t[i] != s[j]) {
      ++j;
    }
    l[i] = j;
  }
  for (int i = m - 1, j = n - 1; i >= 0; --i, --j) {
    while (t[i] != s[j]) {
      --j;
    }
    r[i] = j;
  }
  int a = 1;
  for (int i = 1; i < m; ++i) {
    a = max(a, r[i] - l[i - 1]);
  }
  cout << a << "\n";
  return 0;
}
