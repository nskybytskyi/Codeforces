#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, t, k;
  cin >> n >> t >> k;
  auto ask = [&] (int l, int r) -> int {
    cout << "? " << l + 1 << " " << r + 1 << endl << flush;
    cout.flush();
    int a;
    cin >> a;
    return (r - l + 1) - a;
  };
  auto say = [&] (int x) -> void {
    cout << "! " << x + 1 << endl << flush;
    cout.flush();
  };
  int lo = -1, hi = n - 1;
  while (lo + 1 < hi) {
    int mi = lo + (hi - lo) / 2;
    if (ask(0, mi) < k) {
      lo = mi;
    } else {
      hi = mi;
    }
  }
  say(hi);
  return 0;
}