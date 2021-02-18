#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int64_t n, q, k;
  cin >> n >> q >> k;
  vector<int64_t> a(n);
  for (auto& ai : a) {
    cin >> ai;
  }
  while (q--) {
    int li, ri;
    cin >> li >> ri;
    --li, --ri;
    int64_t m = a[li], M = a[ri], len = ri - li;
    cout << (k - M) + 2 * (M - m - len) + (m - 1) << "\n"; 
  }
  return 0;
}
