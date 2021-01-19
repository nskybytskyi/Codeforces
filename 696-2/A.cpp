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

  int t;
  cin >> t;
  while (t--) {
    int n;
    string b;
    cin >> n >> b;

    string a = "1";
    for (int i = 1; i < n; ++i) {
      if (b[i] == '0') {
        if (a[i - 1] == '0') {
          if (b[i - 1] == '0') {
            a += "1";
          } else {  // b[i - 1] == '1'
            a += "0";
          }
        } else {  // a[i - 1] == '1'
          if (b[i - 1] == '0') {
            a += "0";
          } else {  // b[i - 1] == '1'
            a += "1";
          }
        }
      } else {  // b[i] == '1'
        if (a[i - 1] == '0') {
          if (b[i - 1] == '0') {
            a += "1";
          } else {  // b[i - 1] == '1'
            a += "1";
          }
        } else {  // a[i - 1] == '1'
          if (b[i - 1] == '0') {
            a += "1";
          } else {  // b[i - 1] == '1'
            a += "0";
          }
        }
      }
    }

    cout << a << "\n";
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
