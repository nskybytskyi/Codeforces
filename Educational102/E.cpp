#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <queue>
#include <unordered_map>
#include <utility>
#include <limits>
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

const int64_t kInfinity = std::numeric_limits<int64_t>::max();

using Edge = std::pair<int, int>;

using Graph = std::vector<std::vector<Edge>>;

std::vector<int64_t> DijkstraHeap(const Graph& graph, int source = 0);

class DSU {
  public:
    explicit DSU(int size);
    int Find(int vertex) const;
    void Union(int first, int second);

  private:
    mutable std::vector<int> parent_;
    std::vector<int> rank_;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n, m;
  cin >> n >> m;
  Graph g(4*n);
  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    --u, --v;
    for (int i : {0, 1, 2, 3}) {
      g[u+i*n].emplace_back(v+i*n, w);
      g[v+i*n].emplace_back(u+i*n, w);
    }
    for (int i : {0, 2}) {
      g[u+i*n].emplace_back(v+(1|i)*n, 0);
      g[v+i*n].emplace_back(u+(1|i)*n, 0);
    }
    for (int i : {0, 1}) {
      g[u+i*n].emplace_back(v+(2|i)*n, 2*w);
      g[v+i*n].emplace_back(u+(2|i)*n, 2*w);
    }
  }

  auto d = DijkstraHeap(g);
  for (int i = 1; i < n; ++i) {
    cout << min(d[i], d[i+3*n]) << " ";
  }
  cout << "\n";

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

DSU::DSU(int size) {
  rank_.resize(size);
  parent_.resize(size);
  std::iota(parent_.begin(), parent_.end(), 0);
}

int DSU::Find(int vertex) const {
  return (vertex == parent_[vertex]) ? vertex : (parent_[vertex] = Find(parent_[vertex]));
}

void DSU::Union(int first, int second) {
  first = Find(first), second = Find(second);
  if (first != second) {
    if (rank_[first] < rank_[second]) {
      std::swap(first, second);
    }
    parent_[second] = first;
    if (rank_[first] == rank_[second]){
      ++rank_[first];
    }
  }
}

std::vector<int64_t> DijkstraHeap(const Graph& graph, int source) {
  const int vertex_count = graph.size();
  std::vector<int64_t> distance(vertex_count, kInfinity);
  distance[source] = 0;
  std::priority_queue<std::pair<int64_t, int>,
                      std::vector<std::pair<int64_t, int>>,
                      std::greater<std::pair<int64_t, int>>> heap;
  heap.emplace(0, source);

  while (!heap.empty()) {
    // select closest unused vertex in O(log n)
    const auto [closest_distance, closest_vertex] = heap.top();
    heap.pop();
    if (closest_distance < kInfinity) {
      if (distance[closest_vertex] == closest_distance) {
        // process all outgoing edges from it
        for (const auto& [adjacent, edge_length] : graph[closest_vertex]) {
          if (distance[adjacent] > closest_distance + edge_length) {
            distance[adjacent] = closest_distance + edge_length;
            heap.emplace(distance[adjacent], adjacent);
          }
        }
      }  // else this is a fake pair
    } else {  // no more iterations needed, remaining vertices are unreachable
      break;
    }
  }

  return distance;
}
