#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

using Tree = std::vector<std::vector<int>>;

std::pair<int, Tree> ReadRootedTreeParentList(int vertex_count = 0,
  std::istream& in_stream = std::cin);

std::pair<std::vector<int>, std::vector<int>>
ComputeTimes(const Tree& tree, int source);

void ComputeTimesDepthFirstSearch(const Tree& tree, int vertex, int parent,
  int* timer_ptr, std::pair<std::vector<int>, std::vector<int>>* times_ptr);

using AncestorQuery = std::pair<int, int>;

AncestorQuery ReadAncestorQuery(std::istream& in_stream = std::cin);

std::vector<AncestorQuery> ReadAncestorQueries(int query_count = 0,
  std::istream& in_stream = std::cin);

using Answer = int;

Answer AnswerAncestorQuery(const AncestorQuery& ancestor_query,
  const std::vector<int>& time_in, const std::vector<int>& time_out);

std::vector<Answer>
AnswerAncestorQueries(const std::vector<AncestorQuery>& ancestor_queries,
  const std::vector<int>& time_in, const std::vector<int>& time_out);

void PrintAnswer(const Answer& answer, std::ostream& out_stream = std::cout);

void PrintAnswers(const std::vector<Answer>& answers,
  std::ostream& out_stream = std::cout);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("ancestor.in", "r", stdin);
  std::freopen("ancestor.out", "w", stdout);

  const auto [root, tree] = ReadRootedTreeParentList();
  const auto [time_in, time_out] = ComputeTimes(tree, root);
  const auto ancestor_queries = ReadAncestorQueries();
  const auto answers = AnswerAncestorQueries(ancestor_queries, time_in, time_out);
  PrintAnswers(answers);

  return 0;
}

std::pair<int, Tree> ReadRootedTreeParentList(int vertex_count,
    std::istream& in_stream) {
  if (!vertex_count) {
    in_stream >> vertex_count;
  }
  int root = -1;
  Tree tree(vertex_count);
  for (int vertex = 0, parent; vertex < vertex_count; ++vertex) {
    in_stream >> parent;
    if (!parent) {
      assert(root == -1);  // there can be only one root
      root = vertex;
    } else {
      assert(0 < parent && parent <= vertex_count);
        // parent id should be in range (0, vertex_count]
      tree[parent - 1].push_back(vertex);
    }
  }
  return {root, tree};
}

std::pair<std::vector<int>, std::vector<int>>
ComputeTimes(const Tree& tree, int source) {
  int timer = 0;
  const int vertex_count = tree.size();
  std::pair<std::vector<int>, std::vector<int>> times;
  times.first.resize(vertex_count);
  times.second.resize(vertex_count);
  ComputeTimesDepthFirstSearch(tree, source, -1, &timer, &times);
  return times;
}

void ComputeTimesDepthFirstSearch(const Tree& tree, int vertex, int parent,
    int* timer_ptr, std::pair<std::vector<int>, std::vector<int>>* times_ptr) {
  times_ptr->first[vertex] = *timer_ptr;
  ++(*timer_ptr);
  for (auto adjacent : tree[vertex]) {
    if (adjacent != parent) {
      ComputeTimesDepthFirstSearch(tree, adjacent, vertex, timer_ptr, times_ptr);
    }
  }
  times_ptr->second[vertex] = *timer_ptr;
  ++(*timer_ptr);
}

AncestorQuery ReadAncestorQuery(std::istream& in_stream) {
  AncestorQuery ancestor_query;
  auto& [ancestor, vertex] = ancestor_query;
  in_stream >> ancestor >> vertex;
  // assert(0 < ancestor && ancestor <= vertex_count);
  //   // ancestor id should be in range (0, vertex_count]
  // assert(0 < vertex && vertex <= vertex_count);
  //   // vertex id should be in range (0, vertex_count]
  --ancestor, --vertex;
  return ancestor_query;
}

std::vector<AncestorQuery> ReadAncestorQueries(int query_count,
    std::istream& in_stream) {
  if (!query_count) {
    in_stream >> query_count;
  }
  std::vector<AncestorQuery> ancestor_queries(query_count);
  for (auto& ancestor_query : ancestor_queries) {
    ancestor_query = ReadAncestorQuery(in_stream);
  }
  return ancestor_queries;
}

Answer AnswerAncestorQuery(const AncestorQuery& ancestor_query,
    const std::vector<int>& time_in, const std::vector<int>& time_out) {
  const auto [ancestor, vertex] = ancestor_query;
  return time_in[ancestor] <= time_in[vertex] &&
    time_out[vertex] <= time_out[ancestor];
}

std::vector<Answer>
AnswerAncestorQueries(const std::vector<AncestorQuery>& ancestor_queries,
    const std::vector<int>& time_in, const std::vector<int>& time_out) {
  const int query_count = ancestor_queries.size();
  std::vector<int> answers(query_count);
  for (int query_index = 0; query_index < query_count; ++query_index) {
    answers[query_index] = AnswerAncestorQuery(ancestor_queries[query_index],
      time_in, time_out);
  }
  return answers;
}

void PrintAnswer(const Answer& answer, std::ostream& out_stream) {
  out_stream << answer;
}

void PrintAnswers(const std::vector<Answer>& answers, std::ostream& out_stream) {
  for (auto answer : answers) {
    PrintAnswer(answer, out_stream);
    out_stream << "\n";
  }
}
