#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

  int t;
  cin >> t;
  while (t--) {
    int64_t n;
    cin >> n;

    // a^2 + b^2 = c^2 (1)
    // c = a^2 - b     (2)

    // plug (1) into (2)
    // c = c^2 - b^2 - b
    // b^2 + b = c^2 - c
    // b (b + 1) = c (c - 1)

    // x maps to x (x + 1)
    // at b and c - 1
    // b == c - 1
    // a > 1
    // a^2 == b + c = 2c - 1
    // a is odd
    // c is (a^2 + 1) / 2 <= n 
    // a <= sqrt(2n - 1)

    // count odds in 2..sqrt(2n + 1)
    // (sqrt(2n + 1) - 2) >> 1

    cout << (int(sqrt(2 * n - 1) - 1) >> 1) << "\n";
  }

  return 0;
}
