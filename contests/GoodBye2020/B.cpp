#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> x(n);
    for (auto& xi : x) {
      cin >> xi;
      --xi;
    }

    int k = (n << 1) + 2;
    vector<pair<int, int>> a(k, {0, 0});
    for (auto xi : x)
      ++a[xi].first;

    int ans = 0;
    for (int i = 0; i < k; ++i) {
      if (a[i].second > 0) {
        --a[i].second;
        ++ans;
      } else if (a[i].first > 0) {
        --a[i].first;
        ++ans;
      }
      a[i + 1].second += a[i].first;
    }
    cout << ans << "\n";
  }

  return 0;
}
