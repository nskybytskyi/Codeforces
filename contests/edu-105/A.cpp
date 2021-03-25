#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);    
  int t;
  cin >> t;
  auto g = [&] (string s, char a, char b, char c) -> bool {
    for (auto& l : s) {
      if (l == 'A') {
        l = a;
      } else if (l == 'B') {
        l = b;
      } else {
        l = c;
      }
    }
    int balance = 0;
    for (auto l : s) {
      if (l == '(') {
        ++balance;
      } else {
        --balance;
      }
      if (balance < 0) {
        return false;
      }
    }
    return !balance;
  };
  while (t--) {
    string s;
    cin >> s;
    bool p = false;
    for (char a : "()") {
      for (char b : "()") {
        for (char c : "()") {
          if (g(s, a, b, c)) {
            p = true;
          }
        }
      }
    }
    if (p) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
  return 0;
}
