#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);    
  int n, m;
  cin >> n >> m;
  vector<map<int, int>> g(n);
  set<pair<int, int>> s, ss;
  while (m--) {
    char cmd;
    cin >> cmd;
    if (cmd == '+') {
      int u, v, c; char _;
      cin >> u >> v >> _;
      c = _ - 'a';
      --u, --v;
      g[u][v] = c;
      if (g[v].count(u)) {
        auto cc = g[v][u];
        if (cc == c) {
          s.emplace(u, v);
          s.emplace(v, u);
        }
        ss.emplace(u, v);
        ss.emplace(v, u);
      }
    } else if (cmd == '-') {
      int u, v;
      cin >> u >> v;
      --u, --v;
      auto c = g[u][v];
      g[u].erase(v);
      if (g[v].count(u)) {
        auto cc = g[v][u];
        if (cc == c) {
          s.erase(make_pair(u, v));
          s.erase(make_pair(v, u));
        }
        ss.erase(make_pair(u, v));
        ss.erase(make_pair(v, u));
      }
    } else {  // '?'
      int k;
      cin >> k;
      if (k & 1) {  // even edge length
        if (s.empty() && ss.empty()) {
          cout << "NO\n";
        } else {
          cout << "YES\n";
        }
      } else {  // odd edge length
        if (s.empty()) {
          cout << "NO\n";
        } else {
          cout << "YES\n";
        }
      }
    }
  } 
  return 0;
}
