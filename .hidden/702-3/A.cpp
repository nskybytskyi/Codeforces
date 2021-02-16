#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t;
  cin >> t;
  auto dist = [&] (int x, int y) -> int {
    if (x > y) {
      swap(x, y);
    }
    int d = 0;
    while ((x << 1) < y) {
      x <<= 1;
      ++d;
    }
    return d;
  };
  while (t--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& ai : a)
      cin >> ai;
    int answer = 0;
    for (int i = 1; i < n; ++i) {
      answer += dist(a[i - 1], a[i]);
    }
    cout << answer << "\n";
  }
  return 0;
}
