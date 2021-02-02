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
    vector<int64_t> w(n);
    for (auto& wi : w)
      cin >> wi;

    vector<pair<int64_t, int>> w_i;
    w_i.reserve(n);
    for (auto wi : w) {
      w_i.emplace_back(wi, w_i.size());
    }
    sort(w_i.begin(), w_i.end(), greater<>());
    // for (auto [wi, i] : w_i) {
    //   cout << "(" << wi << ", " << i << ") ";
    // }
    // cout << "\n";

    vector<int> deg(n);
    for (int i = 0; i < n - 1; ++i) {
      int first, second;
      cin >> first >> second;
      --first, --second;
      ++deg[first], ++deg[second];
    }

    int64_t ans = accumulate(w.begin(), w.end(), 0ll);
    cout << ans;

    int j = 0;
    while (j < n) {
      auto [wi, i] = w_i[j];
      while (deg[i] > 1) {
        ans += wi;
        --deg[i];
        cout << " " << ans;
      }
      ++j;
    }
    cout << "\n";
  }

  return 0;
}
