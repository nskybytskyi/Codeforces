#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0);
  int t; cin >> t; while (t--) {
    string s;
    cin >> s;
    unordered_map<char, int> f;
    for (auto c : s) {
      ++f[c];
    }
    int k = 0;
    for (auto [_, v] : f) {
      k += min(2, v);
    }
    cout << k / 2 << "\n";
  }
  return 0;
}