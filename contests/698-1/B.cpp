#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

struct SD {
  int block_size;
  int size;
  vector<int> block_sum;
  vector<int> values;

  SD(const vector<int>& array) {
    size = array.size();
    block_size = sqrt(size) + 1;
    block_sum.resize(block_size);
    values.resize(block_size * block_size);
    for (int i = 0; i < size; ++i) {
      values[i] = array[i];
      block_sum[block(i)] += values[i];
    }
    size = values.size();
  }

  inline int block(int index) {
    return index / block_size;
  }

  // [left, right)
  int BlockSum(int left, int right) {
    int answer = 0;
    for (int block_id = left; block_id < right; ++block_id) {
      answer += block_sum[block_id];
    }
    return answer;
  }

  void Push(int block_id) {
    if (block_sum[block_id] == block_size ||
        !block_sum[block_id]) {
      int value = block_sum[block_id] / block_size;
      for (int index = block_id * block_size;
           index < (block_id + 1) * block_size; ++index) {
        values[index] = value;
      }
    }
  }

  void Update(int block_id) {
    block_sum[block_id] = 0;
    for (int index = block_id * block_size; 
         index < (block_id + 1) * block_size; ++index) {
      block_sum[block_id] += values[index];
    }
  }

  // [left, right)
  int Sum(int left, int right) {
    int left_block = block(left), right_block = block(right);
    int block_sum = BlockSum(left_block + 1, right_block);

    int answer = 0;
    int index = left;
    Push(left_block);
    while (index < right) {
      answer += values[index];
      ++index;
      if (index % block_size == 0) {
        break;
      }
    }

    right_block = block(right - 1);
    Push(right_block);
    if ((left_block != right_block) && (right % block_size)) {
      index = right - 1;
      while (index >= left) {
        answer += values[index];
        if (index % block_size == 0) {
          break;
        }
        --index;
      }
    }

    return answer + block_sum;
  }

  // [left, right)
  void BlockSet(int left, int right, int value) {
    for (int block_id = left; block_id < right; ++block_id) {
      block_sum[block_id] = value * block_size;
    }
  }

  // [left, right)
  void Set(int left, int right, int value) {
    int left_block = block(left), right_block = block(right);
    BlockSet(left_block + 1, right_block, value);

    int index = left;
    while (index < right) {
      values[index] = value;
      ++index;
      if (index % block_size == 0) {
        break;
      }
    }
    Update(left_block);

    right_block = block(right - 1);
    if (left_block != right_block) {
      index = right - 1;
      while (index >= left) {
        values[index] = value;
        if (index % block_size == 0) {
          break;
        }
        --index;
      }
    }
    Update(right_block);
  }

  vector<int> Get() {
    for (int block_id = 0; block_id < block_size; ++block_id) {
      Push(block_id);
    }
    return values;
  }

  // void Print() {
  //   Get();
  //   for (auto value : values)
  //     cout << value << " ";
  //   cout << "\n";
  //   for (auto block_sum_ : block_sum)
  //     cout << block_sum_ << " ";
  //   cout << "\n";
  // }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int n, q;
    string s, f;
    cin >> n >> q >> s >> f;

    vector<pair<int, int>> queries(q);
    for (auto& query : queries) 
      cin >> query.first >> query.second;
    reverse(queries.begin(), queries.end());

    vector<int> a(n);
    for (int i = 0; i < n; ++i)
      a[i] = f[i] - '0';

    bool possible = true;
    SD sd(a);
    for (auto [left, right] : queries) {
      // sd.Print();
      --left;
      int sum = sd.Sum(left, right);
      int new_value = 2 * sum > right - left;
      // cout << "sum from " << left << " to " << right
      //   << " is " << sum << ", about to set " << new_value << "\n";
      if (2 * sum == right - left) {
        possible = false;
        break;
      }
      sd.Set(left, right, new_value);
    }

    vector<int> b(n);
    for (int i = 0; i < n; ++i)
      b[i] = s[i] - '0';
    auto c = sd.Get();
    // sd.Print();
    for (int i = 0; i < n; ++i)
      if (b[i] != c[i])
        possible = false;

    cout << (possible ? "YES" : "NO") << "\n";
  }

  return 0;
}
