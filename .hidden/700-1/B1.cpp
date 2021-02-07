#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

  int n;
  cin >> n;

  if (n <= 2) {
    cout << n << "\n";
    return 0;
  }

  vector<int> a(n);
  for (auto& ai : a)
    cin >> ai;

  // len, val
  vector<pair<int, int>> b;
  for (auto ai : a) {
    if (!b.empty() && ai == b.back().second) {
      b.back().first = 2;
    } else {
      b.emplace_back(1, ai);
    }
  }

  bool good_between = false;
  int count = 0;
  int last_double_val = -1;
  int last_single_val = -1;
  for (const auto len_val : b) {
    const auto len = len_val.first;
    const auto val = len_val.second;
    if (len == 1) {
      if (last_single_val != last_double_val &&
          last_single_val != -1 &&
          last_double_val != val) {
        good_between = true;
      }
      last_single_val = val;
      ++count;
    } else {  // len == 2
      if (last_double_val == val) {
        if (good_between) {
          count += 2;
        } else {
          ++count;
        }
      } else {
        count += 2;
      }
      last_single_val = -1;
      last_double_val = val;
      good_between = false;
    }
  }

  cout << count << "\n";

  return 0;
}
