#include <bits/stdc++.h>

using namespace std;

const int mod = 1'000'000'007;

const int len = 60;

vector<int> pow2 = {1};
void init() {
  for (int i = 0; i < 128; ++i)
    pow2.push_back((pow2.back() << 1) % mod);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  init();

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int64_t> x(n);
    for (auto& xi : x)
      cin >> xi;
 
    vector<int> bitf(len);
    for (auto xi : x)
      for (int i = 0; i < len; ++i)
        if (xi & (1ll << i))
          ++bitf[i];

    int64_t ans = 0;
    // join on j?
    for (auto xj : x) {
      // number of i having k-th bit set in (x_i & x_j)
      int64_t b = 0;
      for (int k = 0; k < len; ++k) {
        int64_t bk;
        if (xj & (1ll << k))
          bk = bitf[k];
        else
          bk = 0;
        bk *= pow2[k];
        bk %= mod;
        b += bk;
        b %= mod;
      }

      // number of k having l-th bit set in (x_j | x_k)
      int64_t c = 0;
      for (int l = 0; l < len; ++l) {
        int64_t cl;
        if (xj & (1ll << l))
          cl = n;
        else
          cl= bitf[l];
        cl *= pow2[l];
        cl %= mod;
        c += cl;
        c %= mod;
      }

      int64_t d = (b * c) % mod;
      ans += d;
      ans %= mod;
    }

    cout << ans << "\n";
  }

  return 0;
}
