#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int a, b, k;
  cin >> a >> b >> k;
  if (b == 1) {
    if (k) {
      cout << "No\n";
    } else {
      cout << "Yes\n";
      cout << "1" + string(a, '0') << "\n";
      cout << "1" + string(a, '0') << "\n";
    }
  } else {
    if (k > a + b - 2) {
      cout << "No\n";
    } else if (k <= a) {
      cout << "Yes\n";
      cout << "11" + string(k, '0') + \
        string(a - k, '0') + string(b - 2, '1') << "\n";
      cout << "1" + string(k, '0') + "1" + \
        string(a - k, '0') + string(b - 2, '1') << "\n";
    } else if (a) {
      int r = k - a;
      cout << "Yes\n";
      cout << "11" + string(r, '1') + string(a, '0') + \
        string(b - 2 - r, '1') << "\n";
      cout << "10" + string(r, '1') + string(a - 1, '0') + "1" + \
        string(b - 2 - r, '1') << "\n";
    } else {
      cout << "No\n";
    }
  }
  return 0;
}
