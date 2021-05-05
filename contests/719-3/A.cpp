#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t, n;
  string s;
  cin >> t;
  auto compress = [&] (const string& s) -> string {
    string t;
    for (char c : s) {
      if (t.empty() || c != t.back()) {
        t += c;
      }
    }
    return t;
  };
  while (t--) {
    cin >> n >> s;
    s = compress(s);
    if (s.length() == set<char>(s.begin(), s.end()).size()) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
  return 0;
}