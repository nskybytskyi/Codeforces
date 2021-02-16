#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& ai : a)
      cin >> ai;
    unordered_map<int, int> f;
    for (auto ai : a)
      ++f[ai];
    vector<int> v;
    for (auto [_, vi] : f)
      v.push_back(vi);
    sort(v.begin(), v.end());
    int ans = n;
    vector<int> ps = {0};
    partial_sum(v.begin(), v.end(), back_inserter(ps));
    vector<int> ss = {0};
    partial_sum(v.rbegin(), v.rend(), back_inserter(ss));
    reverse(ss.begin(), ss.end());
    // for (auto psi : ps) {
    //   cout << psi << " ";
    // }
    // cout << "\n";
    // for (auto ssi : ss) {
    //   cout << ssi << " ";
    // }
    // cout << "\n";
    const int k = v.size();
    for (int i = 0; i < k; ++i) {
      int c = v[i];
      ans = min(ans, ps[i] + (ss[i] - c * (k - i)));
    }
    cout << ans << "\n";
  }
  return 0;
}
