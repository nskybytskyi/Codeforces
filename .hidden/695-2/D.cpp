#include <iostream>
#include <vector>

using namespace std;

const int mod = 1'000'000'007;

template <typename T = int>
std::vector<T> ReadArray(int size = 0, std::istream& in_stream = std::cin);

std::vector<pair<int, int>> ReadPairsArray(int size = 0, std::istream& in_stream = std::cin);

void iadd(int& a, int b) {
  a += b;
  if (a >= mod)
    a -= mod;
}

int mul(int a, int b) {
  int c = (a * 1ll * b) % mod;
  c += mod;
  if (c >= mod)
    c -= mod;
  return c;
}

using Query = pair<int, int>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n, k, q;
  cin >> n >> k >> q;
  auto a = ReadArray(n);

  // dp[i][j] = number of paths of length i ending at position j
  vector<vector<int>> dp(k + 1, vector<int>(n));
  dp[0].assign(n, 1);
  for (int i = 0; i < k; ++i) {
    for (int j = 0; j < n; ++j) {
      if (j) {
        iadd(dp[i + 1][j], dp[i][j - 1]);
      }
      if (j + 1 < n) {
        iadd(dp[i + 1][j], dp[i][j + 1]);
      }
    }
  }

  // coef[j] = sum(dp[i][j] * dp[k - i][j] for i in range(k + 1))
  vector<int> coef(n);
  for (int i = 0; i <= k; ++i) {
    for (int j = 0; j < n; ++j) {
      iadd(coef[j], mul(dp[i][j], dp[k - i][j]));
    }
  }

  // s = sum(coef[j] * a[j] for j in range(n))
  int s = 0;
  for (int j = 0; j < n; ++j) {
    iadd(s, mul(coef[j], a[j]));
  }

  auto queries = ReadPairsArray(q);
  for (auto query : queries) {
    --query.first;
    iadd(s, mul(coef[query.first], -a[query.first]));
    a[query.first] = query.second;
    iadd(s, mul(coef[query.first], a[query.first]));
    cout << s << "\n";
  }

  return 0;
}

std::vector<pair<int, int>> ReadPairsArray(int size, std::istream& in_stream) {
  if (!size) {
    in_stream >> size;
  }
  std::vector<pair<int, int>> array(size);
  for (auto& element : array) {
    in_stream >> element.first >> element.second;
  }
  return array;
}

template <typename T>
std::vector<T> ReadArray(int size, std::istream& in_stream) {
  if (!size) {
    in_stream >> size;
  }
  std::vector<T> array(size);
  for (auto& element : array) {
    in_stream >> element;
  }
  return array;
}
