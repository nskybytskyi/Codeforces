#include <bits/stdc++.h>
using namespace std;
// library code goes here

int main() {
  ios::sync_with_stdio(0),cin.tie(0);

  int d, n;
  cin >> d >> n;
  vector<string> p(n);
  for (auto& pi : p) {
    cin >> pi;
  }

  vector<pair<int, string>> ip;
  for (auto pi : p) {
    ip.emplace_back(count(pi.begin(), pi.end(), '1'), pi);
  }
  sort(ip.rbegin(), ip.rend());

  auto contains = [&] (const auto& first, const auto& second) -> bool {
    for (int i = 0; i < d; ++i) {
      if (first[i] < second[i]) {
        return false;
      }
    }
    return true;
  };

  BipartiteGraph g({n, n});
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i != j && contains(ip[i].second, ip[j].second)) {
        g.AddEdge({j, i});
      }
    }
  }

  const auto m = Kuhn(g);

  vector<vector<string>> cs;
  vector<bool> u(n);
  for (int i = n - 1; i >= 0; --i) {
    if (!u[i]) {
      cs.emplace_back();
      auto j = i;
      do {
        u[j] = true;
        cs.back().push_back(ip[j].second);
        j = m.Get(j, false);
      } while (j != BipartiteMatching::kNoMatch);
    }
  }

  auto transit = [&] (const auto& first, const auto& second) -> string {
    string r;
    for (int i = 0; i < d; ++i) {
      if (first[i] < second[i]) {
        r += '0' + i;
      }
    }
    return r;
  };

  string r;
  for (auto& c : cs) {
    r += transit(string(d, '0'), c[0]);
    const int k = c.size();
    for (int i = 1; i < k; ++i) {
      r += transit(c[i - 1], c[i]);
    }
    r += 'R';
  }
  r.pop_back();

  cout << r.length() << "\n";
  for (auto ri : r) {
    cout << ri << " ";
  }
  cout << "\n";

  return 0;
}
