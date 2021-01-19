#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <numeric>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

template <typename T = int>
std::vector<T> ReadArray(int size = 0, std::istream& in_stream = std::cin);

template <typename T>
void PrintArray(const std::vector<T>& array, std::ostream& out_stream = std::cout,
                bool size = false, char element_separator = ' ', char end = '\n');

template <typename T> 
using Counter = std::unordered_map<T, int>;

template <typename Iterator>
using ValueType = typename std::iterator_traits<Iterator>::value_type;

template <class InputIt>
Counter<ValueType<InputIt>> BuildCounter(InputIt first, InputIt last);

template <typename T>
using IndexedValue = std::pair<int, T>;

template <class InputIt>
std::vector<IndexedValue<ValueType<InputIt>>> Enumerate(InputIt first, InputIt last);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int64_t t;
  cin >> t;
  while (t--) {
    int64_t n;
    cin >> n;

    vector<pair<int, int>> ops;
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    int64_t t = 0;

    t += (n - 1) * (n - 1);
    swap(p[0], p[n - 1]);
    ops.emplace_back(1, n);

    int l = 1, r = n - 2;
    bool turn = true;
    while (l <= r) {
      if (turn) {
        t += (n - l - 1) * 1ll * (n - l - 1);
        swap(p[l], p[n - 1]);
        ops.emplace_back(l + 1, n);
        ++l;
      } else {
        t += r * 1ll * r;
        swap(p[r], p[0]);
        ops.emplace_back(r + 1, 1);
        --r;
      }
      turn = !turn;
    }
    reverse(ops.begin(), ops.end());

    cout << t << "\n";
    PrintArray(p);
    cout << ops.size() << "\n";
    for (auto [first, second] : ops) {
      cout << first << " " << second << "\n";
    }
  }

  return 0;
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

template <typename T>
void PrintArray(const std::vector<T>& array, std::ostream& out_stream,
                bool size, char element_separator, char end) {
  if (size) {
    out_stream << array.size() << end;
  }
  for (const auto& element : array) {
    out_stream << element << element_separator;
  }
  out_stream << end;
}

template <class InputIt>
Counter<ValueType<InputIt>> BuildCounter(InputIt first, InputIt last) {
  Counter<ValueType<InputIt>> counter;
  for (auto it = first; it != last; ++it) {
    ++counter[*it];
  }
  return counter;
}

template <class InputIt>
std::vector<IndexedValue<ValueType<InputIt>>> Enumerate(InputIt first, InputIt last) {
  std::vector<IndexedValue<ValueType<InputIt>>> pairs;
  for (auto it = first; it != last; ++it) {
    pairs.emplace_back(pairs.size(), *it);
  }
  return pairs;
}
