template <unsigned int N = 30> 
class BitTrie {
  private:
    struct Node {
      std::unique_ptr<Node> zero_child, one_child;
    };

  public:
    void Insert(int number, Node* node = nullptr, int offset = N) {
      if (!node) {
        node = root_.get();
      }
      while (offset >= 0) {
        if (number & (1ll << offset)) {
          if (!node->one_child) {
            node->one_child = std::make_unique<Node>();
          }
          node = node->one_child.get();
        } else {
          if (!node->zero_child) {
            node->zero_child = std::make_unique<Node>();
          }
          node = node->zero_child.get();
        }
        --offset;
      }
    }

    int FindMaximumXor(int number, Node* node = nullptr, int offset = N) {
      if (!node) {
        node = root_.get();
      }
      int answer = 0;
      while (offset >= 0) {
        if (number & (1ll << offset)) {
          if (node->zero_child) {
            node = node->zero_child.get();
          } else if (node->one_child) {
            answer |= 1ll << offset;
            node = node->one_child.get();
          } else {
            return -1;
          }
        } else {
          if (node->one_child) {
            node = node->one_child.get();
            answer |= 1ll << offset;
          } else if (node->zero_child) {
            node = node->zero_child.get();
          } else {
            return -1;
          }
        }
        --offset;
      }
      return answer;
    }

  private:
    std::unique_ptr<Node> root_ = std::make_unique<Node>();
};

// Example Usage
// # Maximum XOR Queries

// You are given a list of non-negative integers nums and a two-dimensional list 
// of integers queries where each element contains [x, limit].

// Return a list such that for each query [x, limit], we find an e in nums such 
// that e ≤ limit and XOR(e, x) is maximized. If there's no such e, use -1.

// ## Constraints

// - n ≤ 100,000 where n is the length of nums
// - m ≤ 100,000 where m is the length of queries

// ## Example 1

// ### Input
// nums = [2, 4, 8]
// queries = [
//     [3, 5],
//     [2, 0]
// ]

// ### Output
// [4, -1]

// ### Explanation
// For the first query, we can use 2 or 4 in nums. 2 ^ 3 = 1 while 4 ^ 3 = 7 so 
// we pick 4 which yields the bigger XOR. In the second query, there's no number 
// that's less than or equal to 0, so we set it to -1.

#include <tuple>

#include "enumerate.h"

using Query = std::vector<int>;

std::vector<int> solve(std::vector<int>& nums, std::vector<Query>& queries) {
  const int queries_count = queries.size();

  // process queries in sorted order
  auto indexed_queries = Enumerate(queries.begin(), queries.end());
  std::sort(indexed_queries.begin(), indexed_queries.end(),
    [] (const std::pair<int, Query>& first, const std::pair<int, Query>& second) -> bool {
      return std::make_tuple(first.second[1], first.second[0], first.first)
        < std::make_tuple(second.second[1], second.second[0], second.first);
    });

  BitTrie bit_trie;

  // insert numbers in sorted order
  std::sort(nums.begin(), nums.end());
  auto nums_it = nums.begin();

  std::vector<int> answer(queries_count);

  for (const auto& [query_index, query] : indexed_queries) {
    while (nums_it != nums.end() && *nums_it <= query[1]) {
      bit_trie.Insert(*nums_it);
      ++nums_it;
    }
    answer[query_index] = bit_trie.FindMaximumXor(query[0]);
  }

  return answer;
}
