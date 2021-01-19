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

    vector<pair<int,int>>ops;
    vector<int> p(n);
    int64_t t = 0;
    int l = 0, r = n - 1;
    for (; l + 1 < r - 1; l += 2, r -= 2) {
      p[l + 1] = r + 1;
      p[r - 1] = l + 2;
      p[r] = l + 1;
      p[l] = r;
      ops.emplace_back(l + 2, r + 1);
      t += (r - l - 1) * (r - l - 1);
      ops.emplace_back(l + 1, r);
      t += (r - l - 1) * (r - l - 1);
      ops.emplace_back(l + 1, r + 1);
      t += (r - l) * (r - l);
    }

    if (l + 2 == r) {
      p[l] = l + 3;
      p[l + 1] = l + 1;
      p[l + 2] = l + 2;
      ops.emplace_back(l + 3, l + 1);
      ops.emplace_back(l + 2, l + 1);
      t += 5;
    } else if (l + 1 == r) {
      p[l] = l + 2;
      p[l + 1] = l + 1;
      ops.emplace_back(l + 1, l + 2);
      t += 1;
    } else if (l == r) {
      p[l] = l + 1;
    }

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
