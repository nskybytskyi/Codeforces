#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  freopen("nenokku_easy.in", "r", stdin);
  freopen("nenokku_easy.out", "w", stdout);

  string text;

  char query_type;
  string query;

  while (cin >> query_type >> query) {
    transform(query.begin(), query.end(), query.begin(), ::tolower);
    if (query_type == 'A') {
      text += query;
    } else { // '?'
      if (text.find(query) != string::npos) {
        cout << "YES\n";
      } else {
        cout << "NO\n";
      }
    }
  }

  return 0;
}
