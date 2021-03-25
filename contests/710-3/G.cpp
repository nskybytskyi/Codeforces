#include <bits/stdc++.h>
using namespace std;

string solve(string s) {
  if (s.empty()) return "";
  unordered_map<char, int> first, last;
  const int n = s.length();
  for (int i = 0; i < n; ++i) {
    if (!first.count(s[i])) {
      first[s[i]] = i;
    }
    last[s[i]] = i;
  }
  char max_possible = 'a';
  for (auto [k1, v1] : first) {
    bool possible = true;
    for (auto [k2, v2] : last) {
      if (v2 < v1) {
        possible = false;
      }
    }
    if (possible) {
      max_possible = max(max_possible, k1);
    }
  }
  string rest;
  for (int i = first[max_possible]; i < n; ++i) {
    if (s[i] != max_possible) {
      rest += s[i];
    }
  }
  return max_possible + solve(rest);
}

int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

  int t;
  cin >> t;
  while (t--) {
    string s;
    cin >> s;
    cout << solve(s) << "\n";
  }

  return 0;
}
