#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int64_t> a(n);
    for (auto& ai : a)
      cin >> ai;
    vector<pair<int64_t, int>> ai(n);
    for (int i = 0; i < n; ++i) {
      ai[i] = {a[i], i};
    }
    sort(ai.begin(), ai.end());
    auto good = [&] (int mi) -> bool {
      int64_t sum = ai[mi].first;
      for (int i = 0; i < n; ++i) {
        if (i != mi) {
          if (sum >= ai[i].first) {
            sum += ai[i].first;
          } else {
            return false;
          }
        }
      }
      return true;
    };
    int lo = -1, hi = n;
    while (lo + 1 < hi) {
      int mi = (lo + hi) >> 1;
      if (good(mi)) {
        hi = mi;
      } else {
        lo = mi;
      }
    }
    vector<int> possible_winners;
    for (int i = 0; i < n; ++i) {
      if (i >= hi) {
        possible_winners.push_back(ai[i].second);
      }
    }
    sort(possible_winners.begin(), possible_winners.end());
    cout << possible_winners.size() << "\n";
    for (auto possible_winner : possible_winners) {
      cout << possible_winner + 1 << " ";
    }
    cout << "\n";
  }
  return 0;
}
