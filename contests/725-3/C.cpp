#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t; cin >> t; while (t--) {
    int n, l, r; cin >> n >> l >> r;
    vector<int> a(n);
    for (auto& ai : a) cin >> ai;
    sort(a.begin(), a.end());
    auto count_pair_sums_upto = [&] (int max_pair_sum) -> int64_t {
      int64_t pairs_count = 0;
      int left = 0, right = n - 1;
      while (left < right) {
        if (a[left] + a[right] > max_pair_sum) {
          --right;
        } else {
          pairs_count += right - left;
          ++left;
        }
      }
      return pairs_count;
    };
    cout << count_pair_sums_upto(r) - count_pair_sums_upto(l - 1) << "\n";
  }
  return 0;
}