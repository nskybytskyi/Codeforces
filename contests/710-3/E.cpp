#include <bits/stdc++.h>
using namespace std;

vector<int> find_smallest(vector<int> p, set<int> unused) {
  const int n = p.size();
  for (int i = 0; i < n; ++i) {
    if (!p[i]) {
      auto it = unused.begin();
      p[i] = *it;
      unused.erase(it);
    }
  }
  return p;
}

vector<int> find_largest(vector<int> p, set<int> unused) {
  const int n = p.size();
  int prefix_max = 0;
  for (int i = 0; i < n; ++i) {
    if (!p[i]) {
      auto it = prev(unused.lower_bound(prefix_max));
      p[i] = *it;
      unused.erase(it);
    } else {
      prefix_max = p[i];
    }
  }
  return p;
}

int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> q(n);
    for (auto& qi : q) {
      cin >> qi;
    }

    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
      if (!i || q[i] != q[i - 1]) {
        p[i] = q[i];
      }
    }

    set<int> unused;
    for (int i = 0; i < n; ++i) {
      unused.insert(i + 1);
    }
    for (auto used : q) {
      auto it = unused.find(used);
      if (it != unused.end()) {
        unused.erase(it);
      }
    }

    for (auto element : find_smallest(p, unused)) {
      cout << element << " ";
    }
    cout << "\n";
    for (auto element : find_largest(p, unused)) {
      cout << element << " ";
    }
    cout << "\n";
  }

  return 0;
}
