#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int n, k;
    string s;
    cin >> n >> k >> s;

    int answer = 0;
    for (int i = 0; i < (k + 1) / 2; ++i) {
      unordered_map<char, int> f;
      for (int p = i; p < n; p += k)
        ++f[s[p]];
      if (2 * i + 1 != k)
        for (int p = n - 1 - i; p >= 0; p -= k)
          ++f[s[p]];
      int fsum = 0, fmax = 0;
      for (auto [_, fi] : f) {
        fsum += fi;
        fmax = max(fmax, fi);
      }
      answer += fsum - fmax;
    }
    cout << answer << "\n";
  }

  return 0;
}
