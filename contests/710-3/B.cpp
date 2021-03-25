#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

  int t;
  cin >> t;
  while (t--) {
    string s;
    int n, k;
    cin >> n >> k >> s;

    vector<int> star_positions;
    for (int i = 0; i < n; ++i) {
      if (s[i] == '*') {
        star_positions.push_back(i);
      }
    }
    const int star_count = star_positions.size();

    vector<int> dp(star_count, star_count);
    dp[0] = 1;
    for (int i = 1; i < star_count; ++i) {
      for (int j = i - 1; j >= 0 && star_positions[i] - star_positions[j] <= k; --j) {
        dp[i] = min(dp[i], dp[j] + 1);
      }
    }
    cout << dp.back() << "\n";
  }

  return 0;
}
