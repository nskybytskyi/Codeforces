#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

inline bool Match(const std::string& string, const std::string& pattern) {
  const int length = string.length();
  for (int i = 0; i < length; ++i) {
    if (string[i] != pattern[i] && pattern[i] != '_') {
      return false;
    }
  }
  return true;
}

using Graph = std::vector<std::vector<int>>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int pattern_count, string_count, length;
  std::cin >> pattern_count >> string_count >> length;
  std::vector<std::string> patterns(pattern_count);
  std::unordered_map<std::string, int> pattern_index;
  for (int i = 0; i < pattern_count; ++i) {
    std::cin >> patterns[i];
    pattern_index[patterns[i]] = i;
  }
  Graph graph(pattern_count);
  while (string_count --> 0) {
    std::string string;
    int first_index;
    std::cin >> string >> first_index;
    --first_index;
    if (!Match(string, patterns[first_index])) {
      std::cout << "NO\n";
      return 0;
    }
    for (int bitmask = 0; bitmask < (1 << length); ++bitmask) {
      std::string pattern;
      for (int i = 0; i < length; ++i) {
        if (bitmask & (1 << i)) {
          pattern += '_';
        } else {
          pattern += string[i];
        }
      }
      if (pattern_index.count(pattern) && pattern_index[pattern] != first_index) {
        graph[first_index].push_back(pattern_index[pattern]);
      }
    }
  }
  bool cycle = false;
  std::vector<int> order, color(pattern_count);
  std::function<void(int)> dfs = [&] (int vertex) -> void {
    color[vertex] = 1;
    for (auto adjacent : graph[vertex]) {
      if (!color[adjacent]) {
        dfs(adjacent);
      } else if (color[adjacent] == 1) {
        cycle = true;
      }
    }
    color[vertex] = 2;
    order.push_back(vertex);
  };
  for (int vertex = 0; vertex < pattern_count; ++vertex) {
    if (!color[vertex]) {
      dfs(vertex);
    }
  }
  std::reverse(order.begin(), order.end());
  if (cycle) {
    std::cout << "NO\n";
  } else {
    std::cout << "YES\n";
    for (auto index : order) {
      std::cout << index + 1 << " ";
    }
    std::cout << "\n";
  }

  return 0;
}
