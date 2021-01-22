#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

  int s, l;
  cin >> s >> l;

  vector<int> a;

  for (int k = log2(s); k >= 0 && s; --k) {
    for (int m = 1 << k; m <= l && s >= (1 << k); m += 2 << k) {
      a.push_back(m);
      s -= 1 << k;
    }
  }

  if (s) {
    cout << -1 << "\n";
  } else {
    cout << a.size() << "\n";
    for (auto ai : a) {
      cout << ai << " ";
    }
    cout << "\n";
  }

  return 0;
}
