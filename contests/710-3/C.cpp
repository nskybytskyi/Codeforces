#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

  int t;
  cin >> t;
  while (t--) {
    string a, b;
    cin >> a >> b;

    unordered_set<string> a_substrings;
    const int a_length = a.length();
    for (int left = 0; left < a_length; ++left) {
      for (int right = left + 1; right <= a_length; ++right) {  // [left, right)
        a_substrings.insert(a.substr(left, right - left));
      }
    }

    const int b_length = b.length();
    int max_common = 0;
    for (int left = 0; left < b_length; ++left) {
      for (int right = left + 1; right <= b_length; ++right) {  // [left, right)
        if (a_substrings.count(b.substr(left, right - left))) {
          max_common = max(max_common, right - left);
        }
      }
    }
    int min_operations = (a_length - max_common) + (b_length - max_common);
    cout << min_operations << "\n";
  }

  return 0;
}
