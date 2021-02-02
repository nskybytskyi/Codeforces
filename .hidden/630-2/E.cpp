#include <iostream>

using namespace std;

const int kMod = 998'244'353;

inline int modmul(int first, int second, int mod = kMod) {
  return (first * 1ll * second) % mod;
}

inline void imodmul(int& first, int second, int mod = kMod) {
  first = modmul(first, second, mod);
}

int modpow(int base, int64_t power, int mod = kMod) {
  int result = 1;
  while (power) {
    if (power & 1)
      imodmul(result, base, mod);
    imodmul(base, base, mod);
    power >>= 1;
  }
  return result;
}

inline int modinv(int number, int mod = kMod) {
  return modpow(number, mod - 2, mod);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m, l, r;
  cin >> n >> m >> l >> r;

  int k = r + 1 - l;

  if ((n * m) & 1) {
    cout << modpow(k, n * 1ll * m) << "\n";
  } else if (k & 1) {
    int r = modpow(k, n * 1ll * m) + 1;
    if (r == kMod) r = 0;
    cout << modmul(r, modinv(2)) << "\n";
  } else {
    const int r = modpow(k, n * 1ll * m - 1);
    cout << modmul(k >> 1, r) << "\n";
  }

  return 0;
}
