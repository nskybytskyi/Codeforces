#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <set>
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
    auto a = ReadArray<int64_t>(n);

    vector<int64_t> x(n);
    x[0] = a[0];
    for (int64_t i = 1; i < n; ++i) {
      x[i] = a[i] - x[i - 1];
    }

    // PrintArray(x);

    const auto right_it = find_if(x.begin(), x.end(), 
      [] (int64_t v) -> bool { return v < 0; });

    if (right_it == x.end() && !x[n - 1]) {
      cout << "YES\n";
    } else {

      int64_t even_suffix_min = numeric_limits<int64_t>::max();
      int64_t odd_suffix_min = numeric_limits<int64_t>::max();

      int64_t right = distance(x.begin(), right_it);
      right = min(right, n - 2);
      for (int64_t left = n - 1; left > right; --left) {
        if (left & 1) {
          odd_suffix_min = min(odd_suffix_min, x[left]);
        } else {
          even_suffix_min = min(even_suffix_min, x[left]);
        }
      }

      // cout << "right = " << right << ", " \
      //      << "odd_suffix_min = " << odd_suffix_min << ", " \
      //      << "even_suffix_min = " << even_suffix_min << "\n";

      bool success = false;
      for (int64_t left = right; left >= 0 && !success; --left) {
        const int64_t delta = 2 * (a[left] - a[left + 1]);

        // cout << "left = " << left << ", " \
        //      << "delta = " << delta << ", " \
        //      << "odd_suffix_min = " << odd_suffix_min << ", " \
        //      << "even_suffix_min = " << even_suffix_min << "\n";

        if (left & 1) {
          if (odd_suffix_min >= delta &&
              even_suffix_min >= -delta &&
              x[left] >= (delta / 2) &&
              x[n - 1] == ((n & 1) ? -delta : delta)) {
            success = true;
          }
        } else {
          if (odd_suffix_min >= -delta &&
              even_suffix_min >= delta &&
              x[left] >= (delta / 2) &&
              x[n - 1] == ((n & 1) ? delta : -delta)) {
            success = true;
          }
        }

        if (left & 1) {
          odd_suffix_min = min(odd_suffix_min, x[left]);
        } else {
          even_suffix_min = min(even_suffix_min, x[left]);
        }
      }

      if (success) {
        cout << "YES\n";
      } else {
        cout << "NO\n";
      }
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
