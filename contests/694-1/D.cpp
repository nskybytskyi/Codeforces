#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <typename T = int>
std::vector<T> ReadArray(int size = 0, std::istream& in_stream = std::cin);

// c[v] = 0 - not visited, 1 - teacher, 2 - student
void dfs(vector<vector<int>>& g, vector<int>& c, vector<bool>& s, int v) {
  if (c[v] == 1) {  
    for (int w : g[v]) {
      s[w] = true;
    }
  }
  for (int w : g[v]) {
    if (!c[w]) {
      if (!s[w]) {
        c[w] = 1;
      } else {
        c[w] = 2;
      }
      dfs(g, c, s, w);
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
      int u, v;
      cin >> u >> v;
      --u, --v;
      g[u].push_back(v);
      g[v].push_back(u);
    }

    vector<int> c(n, 0);
    vector<bool> s(n, false);
    c[0] = 1;
    dfs(g, c, s, 0);

    if (count(c.begin(), c.end(), 0)) {
      cout << "NO\n";  // not connected
    } else {
      cout << "YES\n";
      cout << count(c.begin(), c.end(), 1) << "\n";
      for (int i = 0; i < n; ++i) {
        if (c[i] == 1) {
          cout << i + 1 << " ";
        }
      }
      cout << "\n";
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
