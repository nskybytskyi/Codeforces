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
    for (auto& ai : a)
      cin >> ai;
    vector<int> d(n);
    function<void(int,int,int)>
    build = [&] (int begin, int end, int cd = 0) -> void {
      if (begin != end) {
        auto max_it = max_element(next(a.begin(), begin),
                                  next(a.begin(), end));
        auto max_ind = distance(a.begin(), max_it);
        d[max_ind] = cd;
        build(begin, max_ind, cd + 1);
        build(max_ind + 1, end, cd + 1);
      }
    };
    build(0, n, 0);
    for (auto di : d) {
      cout << di << " ";
    }
    cout << "\n";
  }
  return 0;
}
