#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t; cin >> t; while (t--) {
    int l, r; cin >> l >> r;
    auto count_digit_changes_upto = [&] (int max_number) -> int {
      int digit_changes_count = 0;
      while (max_number) {
        digit_changes_count += max_number;
        max_number /= 10;
      }
      return digit_changes_count;
    };
    cout << count_digit_changes_upto(r) - count_digit_changes_upto(l) << "\n";
  }
  return 0;
}