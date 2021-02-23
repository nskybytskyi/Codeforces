#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> p(n);
    for (auto& pi : p) {
      cin >> pi;
    }
    vector<int> a;
    set<int> s(p.begin(), p.end());
    for (int l = n - 1, r = n; l >= 0; --l) {
      if (p[l] == *s.rbegin()) {
        copy(next(p.begin(), l),
             next(p.begin(), r),
          back_inserter(a));
        r = l;
      }
      s.erase(p[l]);
    }
    for (auto ai : a) {
      cout << ai << " ";
    }
    cout << "\n";
  }
  return 0;
}
