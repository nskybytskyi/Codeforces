#include <bits/stdc++.h>

using namespace std;

const int mod = 1'000'000'007;

vector<int> prefix_function(string s) {
  int n = s.length();
  vector<int> pi(n);
  for (int i = 1; i < n; ++i) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) {
      j = pi[j - 1];
    }
    if (s[i] == s[j]) {
      ++j;
    }
    pi[i] = j;
  }
  return pi;
}

using Aut = vector<vector<int>>;

const int alphabet = 27;

const char sep = 'z' + 1;

Aut BuildAut(string s) {
  s += sep;
  int n = s.length();
  vector<int> pi = prefix_function(s);
  Aut aut(n, vector<int>(alphabet));
  for (int i = 0; i < n; ++i) {
    for (char c = 'a'; c <= sep; ++c) {
      if (i > 0 && c != s[i]) {
        aut[i][c - 'a'] = aut[pi[i - 1]][c - 'a'];
      } else {
        aut[i][c - 'a'] = i + (c == s[i]);
      }
    }
  }
  return aut;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, q;
  string s0, t;
  cin >> n >> q >> s0 >> t;

  while (q--) {
    int k;
    string w;
    cin >> k >> w;

    const auto aut = BuildAut(w);

    vector<vector<int>> G(k + 1, vector<int>(aut.size())), K(k + 1, vector<int>(aut.size()));
    for (int j = 0; j < (int)aut.size(); ++j) {
      int state = j;
      for (auto ch : s0) {
        state = aut[state][ch - 'a'];
      }
      G[0][j] = state;
    }

    for (int i = 1; i <= k; ++i) {
      for (int j = 0; j < (int)aut.size(); ++j) {
        int mid = aut[G[i - 1][j]][t[i - 1] - 'a'];
        G[i][j] = G[i - 1][mid];
        K[i][j] = K[i - 1][j] + (mid == (int)w.length()) + K[i - 1][mid];
        K[i][j] %= mod;
      }
    }

    cout << K[k][0] << "\n";
  }

  return 0;
}
