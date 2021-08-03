#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0);
  int t; cin >> t; while (t--) {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& ai : a) {
      cin >> ai;
    }
    unordered_map<int, vector<int>> p;
    for (int i = 0; i < n; ++i) {
      if (p[a[i]].size() < k) {
        p[a[i]].push_back(i);
      }
    }
    vector<int> pv;
    for (auto& [_, v] : p) {
      copy(v.begin(), v.end(), back_inserter(pv));
    }
    const int l = (pv.size() / k) * k;
    pv.resize(l);
    vector<int> c(n, -1);
    for (int j = 0; j < l; ++j) {
      c[pv[j]] = j % k;
    }
    for (auto ci : c) {
      cout << ci + 1 << " ";
    }
    cout << "\n";
  }
  return 0;
}