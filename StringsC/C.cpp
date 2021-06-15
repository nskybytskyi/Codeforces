#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  freopen("unequal.in", "r", stdin);
  freopen("unequal.out", "w", stdout);

  string text;
  cin >> text;

  const int length = text.length();
  unordered_set<string> substrings;
  for (int first = 0; first < length; ++first) {
    for (int last = first; last < length; ++last) {
      substrings.insert(text.substr(first, last - first + 1));
    }
  }
  cout << substrings.size() << "\n";

  return 0;
}
