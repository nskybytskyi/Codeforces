#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    string s;
    cin >> s;

    int ans = 0;
    int n = s.length();
    for (int i = 1; i < n; ++i) {
      if (s[i] == s[i - 1]) {  // break palindroms of length 2 (and all even)
        ++ans;
        s[i] = '$';
      } 
      if (i > 1 && s[i] != '$' && s[i] == s[i - 2]) {  // break palindroms of length 3 (and all odd)
        ++ans;
        s[i] = '&';
      }
      // looks like we can create new palindroms
      // now that I think about it looks like we can't crete new
    }
    cout << ans << "\n";
  }

  return 0;
}
