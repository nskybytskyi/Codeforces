#include <bits/stdc++.h>
using namespace std;
int64_t mod = 1'000'000'007;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int64_t> b(n);
    for (auto& bi : b) {
      cin >> bi;
    }
    // a[i] = b[i] or b[i] - a[i - 1] - ... - a[0]
    // psd[i] =
    //   psb[i] - psa[i] =
    //     psb[i - 1] - psa[i - 1] = psd[i - 1]
    //       or psb[i - 1]
    int64_t psb = 0;
    map<int64_t, int64_t> psd = {{0, 1}};
    int64_t valsum = 1;
    for (auto bi : b) {
      int64_t diff = valsum - psd[psb];
      // cout << "bi = " << bi << ", ";
      // cout << "psb = " << psb << ", ";
      // cout << "diff = " << diff << ", ";
      // cout << "psd[psb] = " << psd[psb] << ", ";
      // cout << "valsum = " << valsum << "\n";
      psd[psb] = valsum;
      valsum += diff;
      if (valsum >= mod) {
        valsum -= mod;
      }
      if (valsum < 0) {
        valsum += mod;
      }
      psb += bi;
    }
    cout << valsum << "\n";
  }
  return 0;
}
