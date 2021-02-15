#include <bits/stdc++.h>
using namespace std;

inline int64_t nc2(int64_t n) {
  return (n * (n + 1)) >> 1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int64_t n, m;
    cin >> n >> m;

    int64_t a = nc2(n);
    int64_t group_count = m + 1;
    int64_t smaller_group_size = (n - m) / group_count;
    int64_t remainder = (n - m) % group_count;
    a -= nc2(smaller_group_size) * group_count;
    a -= remainder * (smaller_group_size + 1);

    cout << a << "\n";
  }

  return 0;
}
