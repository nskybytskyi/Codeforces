#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int64_t> h(n);
    for (auto& hi : h) {
      cin >> hi;
    }
    bool possible = true;
    int64_t buffer = 0;
    for (int i = 0; i < n; ++i) {
      if (h[i] > i) {
        buffer += h[i] - i;
      } else if (h[i] + buffer < i) {
        possible = false;
        break;
      } else {
        int64_t diff = i - h[i];
        buffer -= diff;
        h[i] += diff;
      }
    }
    cout << (possible ? "YES" : "NO") << "\n";
  }
  return 0;
}
