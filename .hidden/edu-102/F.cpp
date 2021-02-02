#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <unordered_set>
#include <limits>
#include <vector>

using namespace std;

const int kMaxVertices = 4'000;
const int kMaxEdges = 100'000;
const int kInfinity = 200'000'000;

template <typename T = int>
std::vector<T> ReadArray(int size = 0, std::istream& in_stream = std::cin);

class DinicSolver {
public:
  DinicSolver();
  void AddEdge(int source, int destination, int capacity_);
  int MaxFlow(int source, int sink, int last_id);
    
private:
  int edge_count = 2;
  std::vector<int> head, current, distance;
  std::vector<int> to, next, capacity, flow;

  bool Bfs(int source, int sink);
  int Dfs(int current_, int sink, int incoming_flow);
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n;
  cin >> n;
  auto a = ReadArray(n), b = ReadArray(n);
  DinicSolver dinic_solver;

  int s = n, t = n + 1, answer = 0;
  for (int i = 0; i < n; ++i) {
    if (b[i] < 0) {
      dinic_solver.AddEdge(i, t, -b[i]);
    } else {
      answer += b[i];
      dinic_solver.AddEdge(s, i, b[i]);
    }
  }
  for (int i = 0; i < n; ++i) {
    unordered_set<int> divs;
    for (int j = i - 1; j >= 0; --j) {
      if (a[i] % a[j] == 0 && !divs.count(a[j])) {
        dinic_solver.AddEdge(i, j, kInfinity / 2);
        divs.insert(a[j]);
      }
    }
  }

  cout << answer - dinic_solver.MaxFlow(s, t, n + 1) << "\n";

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

DinicSolver::DinicSolver() : edge_count(2) {
  head.resize(kMaxVertices, 0);
  current.resize(kMaxVertices, 0);
  distance.resize(kMaxVertices, 0);

  to.resize(kMaxEdges, 0);
  next.resize(kMaxEdges, 0);
  capacity.resize(kMaxEdges, 0);
  flow.resize(kMaxEdges, 0);
}

void DinicSolver::AddEdge(int source, int destination, int capacity_) {
  to[edge_count] = destination;
  capacity[edge_count] = capacity_;
  flow[edge_count] = 0;
  next[edge_count] = head[source];
  head[source] = edge_count++;

  to[edge_count] = source;
  capacity[edge_count] = 0;
  flow[edge_count] = 0;
  next[edge_count] = head[destination];
  head[destination] = edge_count++;
}

bool DinicSolver::Bfs(int source, int sink) {
  std::fill(distance.begin(), distance.end(), 0);
  std::deque<int> bfs = {source};
  distance[source] = 1;
  while (!bfs.empty()) {
    int current_ = bfs.front();
    bfs.pop_front();
    for (int edge = head[current_]; edge; edge = next[edge]) {
      int next_ = to[edge];
      if (!distance[next_] && capacity[edge] > flow[edge]) {
        distance[next_] = distance[current_] + 1;
        bfs.push_back(next_);
        if (next_ == sink) {
          return true;
        }
      }
    }
  }
  return distance[sink];
}

int DinicSolver::Dfs(int current_, int sink, int incoming_flow) {
  if ((current_ == sink) || !incoming_flow) {
    return incoming_flow;
  }
  int outgoing_flow = 0, flow_;
  for (int& edge = current[current_]; edge; edge = next[edge]) {
    int next_ = to[edge];
    if ((distance[current_] + 1 == distance[next_]) &&
      (flow_ = Dfs(next_, sink,
        std::min(incoming_flow, capacity[edge] - flow[edge]))) > 0) {
      flow[edge] += flow_;
      flow[edge ^ 1] -= flow_;
      outgoing_flow += flow_;
      incoming_flow -= flow_;
      if (!incoming_flow) {
        break;
      }
    }
  }
  return outgoing_flow;
}

int DinicSolver::MaxFlow(int source, int sink, int last_id) {
  int answer = 0;
  while (Bfs(source, sink)) {
    for (int id = 0; id <= last_id; ++id) {
      current[id] = head[id];
    }
    answer += Dfs(source, sink, kInfinity);
  }
  return answer;
}
