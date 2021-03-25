#include <iostream>
#include <utility>
#include <vector>

using namespace std;

const int kMod = 998'244'353;

inline void imodadd(int& first, int second, int mod = kMod) {
  first += second;
  if (first >= mod)
    first -= mod;
}

inline int modadd(int first, int second, int mod = kMod) {
  imodadd(first, second);
  return first;
}

inline int modsub(int first, int second, int mod = kMod) {
  first -= second;
  if (first < 0)
    first += mod;
  return first;
}

inline int modmul(int first, int second, int mod = kMod) {
  return (first * 1ll * second) % mod;
}

inline void imodmul(int& first, int second, int mod = kMod) {
  first = modmul(first, second, mod);
}

using Graph = vector<vector<int>>;

// {colored, not colored, disconnected}
vector<int> dfs(const Graph& g, int v, int p) {
  vector<int> answer = {1, 1, 1};
  for (auto u : g[v]) {
    if (u != p) {
      auto sub_answer = dfs(g, u, v);
      imodmul(answer[0], modsub(modadd(sub_answer[0], modmul(2, sub_answer[1])), sub_answer[2]));
      imodmul(answer[1], modsub(modadd(modmul(2, sub_answer[0]), modmul(2, sub_answer[1])), sub_answer[2]));
      imodmul(answer[2], modsub(modadd(sub_answer[0], sub_answer[1]), sub_answer[2]));
    }
  }
  return answer;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  Graph g(n);
  for (int e = 1, u, v; e < n; ++e) {
    cin >> u >> v;
    --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  auto answer = dfs(g, 0, -1);
  cout << modsub(modsub(modadd(answer[0], answer[1]), answer[2]), 1) << "\n";

  return 0;
}
