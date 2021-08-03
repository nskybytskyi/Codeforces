#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0);
  int t; cin >> t; while (t--) {
    int n;
    cin >> n;
    vector<string> s(n);
    for (auto& si : s) {
      cin >> si;
    }
    int mx = 0;
    string kAlphabet = "abcde"; 
    for (auto c : kAlphabet) {
      vector<int> d(n);
      for (int i = 0; i < n; ++i) {
        for (auto l : s[i]) {
          if (l == c) {
            ++d[i];
          } else {
            --d[i];
          }  
        }
      }
      sort(d.rbegin(), d.rend());
      int ps = 0, i = 0;
      while (i < n && ps + d[i] > 0) {
        ps += d[i];
        ++i;
      }
      mx = max(mx, i);
    }
    cout << mx << "\n";
  }
  return 0;
}