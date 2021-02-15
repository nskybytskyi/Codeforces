#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& ai : a)
      cin >> ai;

    int m = *min_element(a.begin(), a.end());
    cout << n - count(a.begin(), a.end(), m) << "\n";
  }

  return 0;
}
