#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for (auto& ai : a) {
    cin >> ai;
  }
  auto possible = [&] (int mi) -> bool {
    int ps = 0;
    map<int, int> left = {{0, -1}};
    for (int r = 0; r < n; ++r) {
      if (a[r] >= mi) {
        ++ps;
      } else {
        --ps;
      }
      if (!left.count(ps)) {
        left[ps] = r;
      }
      if (left.count(ps - 1) && r - left[min(0, ps - 1)] >= k) {
        return true;
      }
    }
    return false;
  };
  int lo = 0, hi = n + 1;
  while (lo + 1 < hi) {
    int mi = (lo + hi) >> 1;
    if (possible(mi)) {
      lo = mi;
    } else {
      hi = mi;
    }
  }
  cout << lo << "\n";
  return 0;
}
