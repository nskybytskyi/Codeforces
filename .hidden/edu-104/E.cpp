#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

  int n1, n2, n3, n4;
  cin >> n1 >> n2 >> n3 >> n4;
  vector<int> a(n1), b(n2), c(n3), d(n4);
  for (auto& ai : a)
    cin >> ai;
  for (auto& bi : b)
    cin >> bi;
  for (auto& ci : c)
    cin >> ci;
  for (auto& di : d)
    cin >> di;

  int m1, m2, m3;

  cin >> m1;
  vector<vector<int>> g1(n2);
  while (m1--) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    g1[y].push_back(x);
  }

  cin >> m2;
  vector<vector<int>> g2(n3);
  while (m2--) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    g2[y].push_back(x);
  }

  cin >> m3;
  vector<vector<int>> g3(n4);
  while (m3--) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    g3[y].push_back(x);
  }

  vector<int> dp1(n1, 1e9), dp2(n2, 1e9), dp3(n3, 1e9), dp4(n4, 1e9);
  for (int i1 = 0; i1 < n1; ++i1) {
    dp1[i1] = a[i1];
  }

  multiset<int> p1(dp1.begin(), dp1.end());
  for (int i2 = 0; i2 < n2; ++i2) {
    for (auto i1 : g1[i2]) {
      p1.erase(p1.find(dp1[i1]));
    }
    if (!p1.empty()) {
      dp2[i2] = *p1.begin() + b[i2];
    }
    for (auto i1 : g1[i2]) {
      p1.insert(dp1[i1]);
    }
  }

  multiset<int> p2(dp2.begin(), dp2.end());
  for (int i3 = 0; i3 < n3; ++i3) {
    for (auto i2 : g2[i3]) {
      p2.erase(p2.find(dp2[i2]));
    }
    if (!p2.empty()) {
      dp3[i3] = *p2.begin() + c[i3];
    }
    for (auto i2 : g2[i3]) {
      p2.insert(dp2[i2]);
    }
  }

  multiset<int> p3(dp3.begin(), dp3.end());
  for (int i4 = 0; i4 < n4; ++i4) {
    for (auto i3 : g3[i4]) {
      p3.erase(p3.find(dp3[i3]));
    }
    if (!p3.empty()) {
      dp4[i4] = *p3.begin() + d[i4];
    }
    for (auto i3 : g3[i4]) {
      p3.insert(dp3[i3]);
    }
  }

  int ans = *min_element(dp4.begin(), dp4.end());
  cout << ((ans >= 1e9) ? -1 : ans) << "\n";

  return 0;
}
