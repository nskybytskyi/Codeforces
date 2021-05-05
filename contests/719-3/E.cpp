#include <bits/stdc++.h>
using namespace std;

int64_t min_moves(string& s, int64_t k) {
  vector<int64_t> sheep_positions;
  const int length = s.length();
  for (int i = 0; i < length; ++i) {
    if (s[i] == '*') {
      sheep_positions.push_back(i);
    }
  }

  vector<int64_t> b = {0};
  partial_sum(sheep_positions.begin(), sheep_positions.end(), back_inserter(b));

  const int n = sheep_positions.size();
  int64_t res = numeric_limits<int64_t>::max();
  for (int i = 0; i < n - k + 1; ++i) {
    res = min(res, b[i + k] - b[k / 2 + i] - b[(k + 1) / 2 + i] + b[i]);
  }
  res -= (k / 2) * ((k + 1) / 2);
  return res;
}

int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t, n;
  string s;
  cin >> t;
  while (t--) {
    cin >> n >> s;
    cout << min_moves(s, count(s.begin(), s.end(), '*')) << "\n";
  }
  return 0;
}