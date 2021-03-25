#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& ai : a) {
      cin >> ai;
    }

    map<int, int> m;
    for (auto ai : a) {
      ++m[ai];
    }

    int max_frequency = 0;
    for (auto [k, v] : m) {
      max_frequency = max(max_frequency, v);
    }

    const int majority_lower_bound = 2 * max_frequency - n;
    const int parity_lower_bound = n & 1;  // 1 if n is odd else 0
    cout << max(majority_lower_bound, parity_lower_bound) << "\n";
  }

  return 0;
}
