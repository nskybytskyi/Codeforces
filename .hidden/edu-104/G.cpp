#include <bits/stdc++.h>
using namespace std;

const int mod = 998'244'353;

struct mint {
  int val = 0;
  mint(int val_ = 0) : val(val_) { }
  mint& operator+=(mint other) {
    val += other.val;
    if (val >= mod) {
      val -= mod;
    }
    return *this;
  }
  mint operator+(mint other) {
    return mint(*this) += other;
  }
  mint& operator-=(mint other) {
    val -= other.val;
    if (val < 0) {
      val += mod;
    }
    return *this;
  }
  mint operator-(mint other) {
    return mint(*this) -= other;
  }
  mint& operator*=(mint other) {
    val = (val * 1ll * other.val) % mod;
    return *this;
  }
  mint operator*(mint other) {
    return mint(*this) *= other;
  }
};

mint dp0(int n) {
  vector<mint> dp(n + 1);
  dp[2] = 26 * 26;

  for (int i = 3; i <= n; ++i) {
    dp[i] += dp[i - 1] * 25;
  }

  return dp[n];
}

auto dp1(int n) {
  // [last = c|!c, prev = c|!c, used c] 
  vector<vector<vector<mint>>> dp(2,
    vector<vector<mint>>(2,
      vector<mint>(n + 1)));

  dp[0][0][0] = 25 * 25;
  dp[1][0][1] = dp[0][1][1] = 25;
  dp[1][1][2] = 1;

  for (int i = 3; i <= n; ++i) {
    vector<vector<vector<mint>>> new_dp(2,
      vector<vector<mint>>(2,
        vector<mint>(n + 1)));

    for (int r = 0; r <= n; ++r) {
      if (r + 1 <= n) {
        new_dp[1][0][r + 1] = dp[0][0][r];
        new_dp[1][1][r + 1] = dp[1][0][r];
      }
      new_dp[0][0][r] = dp[0][0][r] * 24 + dp[0][1][r] * 25;
      new_dp[0][1][r] = dp[1][0][r] * 24 + dp[1][1][r] * 25;
    }

    dp = new_dp;
  }

  return dp;
}

auto dp2(int n) {
  // [last = c1|c2|!c, prev = c1|c2|!c, used c1, used c2] 
  vector<vector<vector<vector<mint>>>> dp(3,
    vector<vector<vector<mint>>>(3,
      vector<vector<mint>>(n + 1,
        vector<mint>(n + 1))));

  dp[0][0][0][0] = 24 * 24;
  dp[1][0][1][0] = dp[0][1][1][0] = dp[2][0][0][1] = dp[0][2][0][1] = 24;
  dp[1][2][1][1] = dp[2][1][1][1] = dp[1][1][2][0] = dp[2][2][0][2] = 1;

  for (int i = 3; i <= n; ++i) {
    vector<vector<vector<vector<mint>>>> new_dp(3,
      vector<vector<vector<mint>>>(3,
        vector<vector<mint>>(n + 1,
          vector<mint>(n + 1))));

    for (int r1 = 0; r1 <= n; ++r1) {
      for (int r2 = 0; r2 <= n; ++r2) {
        if (r1 + 1 <= n) {
          new_dp[1][0][r1 + 1][r2] = dp[0][0][r1][r2] + dp[0][2][r1][r2];
          new_dp[1][1][r1 + 1][r2] = dp[1][0][r1][r2] + dp[1][2][r1][r2];
          new_dp[1][2][r1 + 1][r2] = dp[2][0][r1][r2] + dp[2][2][r1][r2];
        }

        if (r2 + 1 <= n) {
          new_dp[2][0][r1][r2 + 1] = dp[0][0][r1][r2] + dp[0][1][r1][r2];
          new_dp[2][1][r1][r2 + 1] = dp[1][0][r1][r2] + dp[1][1][r1][r2];
          new_dp[2][2][r1][r2 + 1] = dp[2][0][r1][r2] + dp[2][1][r1][r2];
        }

        new_dp[0][0][r1][r2] = dp[0][0][r1][r2] * 23 + dp[0][1][r1][r2] * 24 + dp[0][2][r1][r2] * 24;
        new_dp[0][1][r1][r2] = dp[1][0][r1][r2] * 23 + dp[1][1][r1][r2] * 24 + dp[1][2][r1][r2] * 24;
        new_dp[0][2][r1][r2] = dp[2][0][r1][r2] * 23 + dp[2][1][r1][r2] * 24 + dp[2][2][r1][r2] * 24;
      }
    }

    dp = new_dp;
  }

  return dp;
}

int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

  int n;
  cin >> n;

  vector<int> c(26);
  for (auto& ci : c) {
    cin >> ci;
  }

  auto dp1_ans = dp1(n);
  auto get_dp1 = [&] (int c) -> mint {
    mint ans = 0;
    for (int last : {0, 1}) {
      for (int prev : {0, 1}) {
        for (int r = c + 1; r <= n; ++r) {
          ans += dp1_ans[last][prev][r];
        }
      }
    }
    return ans;
  };

  auto dp2_ans = dp2(n);
  auto get_dp2 = [&] (int c1, int c2) -> mint {
    mint ans = 0;
    for (int last : {0, 1, 2}) {
      for (int prev : {0, 1, 2}) {
        for (int r1 = c1 + 1; r1 <= n; ++r1) {
          for (int r2 = c2 + 1; r2 <= n; ++r2) {
            ans += dp2_ans[last][prev][r1][r2];
          }
        }
      }
    }
    return ans;
  };

  // inclusion-exclusion
  mint a = dp0(n);
  for (int i = 0; i < 26; ++i) {
    a -= get_dp1(c[i]);
  }
  for (int i = 0; i < 26; ++i) {
    for (int j = 0; j < i; ++j) {
      a += get_dp2(c[i], c[j]);
    }
  }
  cout << a.val << "\n";

  return 0;
}
