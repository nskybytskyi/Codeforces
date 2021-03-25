#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n);
  while (m--) {
    int xi, yi;
    cin >> xi >> yi;
    --xi, --yi;
    g[xi].push_back(yi);
    g[yi].push_back(xi);
  }
  // todo
  return 0;
}
