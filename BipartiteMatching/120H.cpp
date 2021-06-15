#include <bits/stdc++.h>
using namespace std;
// library code goes here

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

  freopen("input.txt", "r", stdin);
  int n;
  cin >> n;
  vector<string> s(n);
  for (auto& si : s)
    cin >> si;

  const int kMaxHash = 27 * 27 * 27 * 27;

  auto string_to_hash = [&] (const string& string) -> int {
    int hash = 0;
    for (auto letter : string)
      hash = 27 * hash + (letter - 'a' + 1); 
    return hash;
  };

  auto get_short_subsequences = [&] (const string& s) -> unordered_set<string> {
    unordered_set<string> short_subsequences = {""};
    for (auto letter : s) {
      unordered_set<string> new_short_subsequences(short_subsequences.begin(), short_subsequences.end());
      for (auto short_subsequence : short_subsequences)
        if (short_subsequence.length() < 4)
          new_short_subsequences.insert(short_subsequence + letter);
      short_subsequences = new_short_subsequences;
    }
    short_subsequences.erase("");
    return short_subsequences;
  };

  BipartiteGraph bipartite_graph({n, kMaxHash});
  for (int i = 0; i < n; ++i)
    for (auto short_subsequence : get_short_subsequences(s[i]))
      bipartite_graph.AddEdge({i, string_to_hash(short_subsequence)});

  auto matching = Kuhn(bipartite_graph);

  auto hash_to_string = [&] (int hash) -> string {
    string s;
    while (hash) {
      s += char(((hash % 27) - 1) + 'a');
      hash /= 27;
    }
    return string(s.rbegin(), s.rend());
  };

  vector<string> a(n);
  for (auto hash = 0; hash < kMaxHash; ++hash)
    if (matching.Get(hash, true) != BipartiteMatching::kNoMatch)
      a[matching.Get(hash, true)] = hash_to_string(hash);

  freopen("output.txt", "w", stdout);
  if (matching.Size() != n)
    cout << -1 << "\n";
  else
    for (auto ai : a)
      cout << ai << "\n";

  return 0;
}
