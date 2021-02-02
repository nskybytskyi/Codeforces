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
    vector<int> x(n);
    for (auto& xi : x)
      cin >> xi;
    set<int> s;
    for (auto xi : x)
      for (auto xj : x)
        s.insert(abs(xj - xi));
    s.erase(0);
    cout << s.size() << "\n";
  }

  return 0;
}
