#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& ai : a)
      cin >> ai;

    int max_ = numeric_limits<int>::min();
    int min_ = numeric_limits<int>::max();

    for (int i = 0; i + 1 < n; ++i) {
      if ((a[i] == -1) ^ (a[i + 1] == -1)) {
        max_ = max(max_, -a[i] * a[i + 1]);
        min_ = min(min_, -a[i] * a[i + 1]);
      }
    }

    int k = (max_ + min_) / 2;

    for (auto& ai : a)
      if (ai == -1)
        ai = k;

    int m = 0;

    for (int i = 0; i + 1 < n; ++i)
      m = max(m, std::abs(a[i] - a[i + 1]));

    cout << m << " " << k << "\n";
  }

  return 0;
}
