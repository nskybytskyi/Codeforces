#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

  int n;
  cin >> n;

  if (n == 1) {
    cout << 1 << "\n";
    return 0;
  }

  vector<int> a(n);
  for (auto& ai : a)
    cin >> ai;

  vector<int> b;
  for (auto ai : a) {
    if (b.empty() || ai != b.back()) {
      b.push_back(ai);
    }
  }

  int count = 0, last_val = -1;
  unordered_set<int> between;
  for (auto bi : b) {
    if (between.count(bi)) {
      between.clear();
      between.insert(last_val);
    } else {
      ++count;
    }
    last_val = bi;
    between.insert(bi);
  }

  cout << count << "\n";

  return 0;
}
