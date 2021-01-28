#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

  int n;
  cin >> n;
  vector<uint64_t> b(n);
  for (auto& bi : b)
    cin >> bi;

  vector<int> lowbit(63);
  for (auto bi : b)
    ++lowbit[__builtin_ctzll(bi)];

  const auto it = max_element(lowbit.begin(), lowbit.end());
  const int i = distance(lowbit.begin(), it);
  cout << n - *it << "\n";
  
  for (auto bi : b)
    if (__builtin_ctzll(bi) != i)
      cout << bi << " ";

  return 0;
}
