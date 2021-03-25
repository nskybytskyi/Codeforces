#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);    
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (auto& ai : a) {
      cin >> ai;
    }
    for (auto& bj : b) {
      cin >> bj;
    }
    vector<int> ap, an, bp, bn;
    for (auto ai : a) {
      if (ai < 0) {
        an.push_back(-ai);
      } else {
        ap.push_back(ai);
      }
    }
    reverse(an.begin(), an.end());
    for (auto bj : b) {
      if (bj < 0) {
        bn.push_back(-bj);
      } else {
        bp.push_back(bj);
      }
    }
    reverse(bn.begin(), bn.end());
    auto solve = [] (vector<int>& aa, vector<int>& bb) -> int {
      vector<int> suffix_count = {0};
      for (auto it = bb.rbegin(); it != bb.rend(); ++it) {
        auto it2 = lower_bound(aa.begin(), aa.end(), *it);
        if (it2 != aa.end() && *it2 == *it) {
          suffix_count.push_back(suffix_count.back() + 1);
        } else {
          suffix_count.push_back(suffix_count.back());
        }
      }
      reverse(suffix_count.begin(), suffix_count.end());
      int n = aa.size(), m = bb.size(), i = 0, j = 0, r = 0;
      while (j < m) {
        if (i == n || aa[i] > bb[j] + i) {
          auto it = upper_bound(bb.begin(), bb.end(), bb[j] + i - 1);
          int k = distance(bb.begin(), it);
          r = max(r, k - j + suffix_count[k]);
          ++j;
        } else {
          ++i;
        }
      }
      return r;
    };
    auto pos = solve(ap, bp);
    auto neg = solve(an, bn);
    // cout << pos << " " << neg << "\n";  // debug
    cout << pos + neg << "\n";
  }
  return 0;
}
