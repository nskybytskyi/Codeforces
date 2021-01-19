#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <numeric>
#include <set>
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

struct Solution {
  int x;
  std::vector<std::pair<int, int>> ops;
  explicit Solution(int x_) : x(x_) { }
};

void PrintSolution(const Solution& solution) {
  std::cout << "YES\n";
  std::cout << solution.x << "\n";
  for (const auto& [first, second] : solution.ops) {
    std::cout << first << " " << second << "\n";
  }
}

std::pair<bool, Solution> TrySolve(std::multiset<int> a, int x) {
  Solution solution(x);
  bool success = true;
  while (!a.empty()) {
    const auto second_it = prev(a.end());
    const int second_val = *second_it;
    a.erase(second_it);
    const auto first_it = a.lower_bound(x - second_val);
    if (first_it == a.end() || *first_it + second_val != x) {
      success = false;
      break;
    } else {
      const int first_val = *first_it;
      a.erase(first_it);
      x = second_val;
      solution.ops.emplace_back(first_val, second_val);
    }
  }
  return {success, solution};
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    multiset<int> a;
    for (int i = 0, ai; i < (n << 1); ++i) {
      cin >> ai;
      a.insert(ai);
    }

    bool any = false;
    for (int ai : a) {
      auto [success, solution] = TrySolve(a, ai + *a.rbegin());
      any |= success;
      if (success) {
        PrintSolution(solution);
        break;
      }
    }

    if (!any) {
      cout << "NO\n";
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
