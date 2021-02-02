#include <string>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <vector>

class Trie {
  private:
    struct Node {
      bool is_word_end = false;
      std::unordered_map<char, std::unique_ptr<Node>> children;
    };

  public:
    Trie(char wildcard = '.') : kWildcard(wildcard) { }

    inline int Size() const {
      return size_;
    }

    void Add(const std::string& word) {
      auto node = root_.get();
      for (auto letter : word) {
        if (!node->children.count(letter)) {
          node->children[letter] = std::make_unique<Node>();
        }
        node = node->children[letter].get();
      }
      if (!node->is_word_end) {
        ++size_;
        node->is_word_end = true;
      }
    }

    void AddPrefixes(const std::string& word) {
      auto node = root_.get();
      for (auto letter : word) {
        if (!node->children.count(letter)) {
          node->children[letter] = std::make_unique<Node>();
        }
        node = node->children[letter].get();
        if (!node->is_word_end) {
          ++size_;
          node->is_word_end = true;
        }
      }
    }

    bool Find(const std::string& word, Node* node = nullptr, int offset = 0) const {
      if (!node) {
        node = root_.get();
      }
      for (auto letter : word.substr(offset)) {  // todo: do not generate substring explicitly
        ++offset;
        if (letter != kWildcard) {
          if (!node->children.count(letter)) {
            return false; 
          }
          node = node->children[letter].get();
        } else {
          bool any = false;
          for (const auto& [_, child] : node->children) {
            any |= Find(word, child.get(), offset);
          }
          return any;
        }
      }
      return node->is_word_end;
    }

    bool FindPrefix(const std::string& prefix, Node* node = nullptr, int offset = 0) const {
      if (!node) {
        node = root_.get();
      }
      for (auto letter : prefix.substr(offset)) {  // todo: do not generate substring explicitly
        ++offset;
        if (letter != kWildcard) {
          if (!node->children.count(letter)) {
            return false; 
          }
          node = node->children[letter].get();
        } else {
          bool any = false;
          for (const auto& [_, child] : node->children) {
            any |= FindPrefix(prefix, child.get(), offset);
          }
          return any;
        }
      }
      return true;
    }

    bool IsConcatenation(const std::string& word, Node* node = nullptr, int offset = 0) const {
      if (!node) {
        node = root_.get();
      }
      for (auto letter : word.substr(offset)) {  // todo: do not generate substring explicitly
        if (node->is_word_end) {
          if (IsConcatenation(word, nullptr, offset)) {
            return true;
          }
        }
        ++offset;
        if (!node->children.count(letter)) {
          return false; 
        }
        node = node->children[letter].get();
      }
      return node->is_word_end;
    }

    bool DPGame(Node* node = nullptr) const {
      if (!node) {
        node = root_.get();
      }
      if (node->is_word_end) {
        return true;
      }
      bool any = false;
      for (const auto& [letter, child] : node->children) {
        any |= !DPGame(child.get());
      }
      return any;
    }

    using Board = std::vector<std::vector<std::string>>;

    void BoardDepthFirstSearch(Board& board, int row, int column,
        std::unordered_set<std::string>& output, Node* node = nullptr, std::string word = "") {
      if (!node) {
        node = root_.get();
      }
      const auto letter = board[row][column][0];
      if (letter != '#' && node->children[letter]) {
        word += letter;
        node = node->children[letter].get();

        if (node->is_word_end) {
          output.insert(word);
        }

        board[row][column][0] = '#';

        for (int row_delta = -1; row_delta <= 1; ++row_delta) {
          for (int column_delta = -1; column_delta <= 1; ++column_delta) {
            if (0 <= row + row_delta && row + row_delta < 4 &&
                0 <= column + column_delta && column + column_delta < 4) {
              BoardDepthFirstSearch(board, row + row_delta, column + column_delta,
                output, node, word);  // do not pass word by value
            }
          }
        }

        board[row][column][0] = letter;
        word.pop_back();
      }
    }

  private:
    int size_ = 0;
    const char kWildcard; 
    std::unique_ptr<Node> root_ = std::make_unique<Node>();
};

// Example Usage
// # Word Concatenation

// Given a list of unique strings words, return the number of words that are 
// concatenations of other words in the list. You can reuse words when 
// concatenating and concatenate any number of times.

// ## Constraints

// - n ≤ 100,000 where n is the length of words
// - m ≤ 100 where m is the max length of a string in words

// ## Example 1

// ### Input
// words = ["news", "paper", "newspaper", "binary", "search", "binarysearch"]

// ### Output
// 2

// ### Explanation
// "newspaper" is concatenation of "news" and "paper". 
// "binarysearch" is concatenation of "binary" and "search".

// ## Example 2

// ### Input
// words = ["cc", "c"]

// ### Output
// 1

// ### Explanation
// "cc" is a concatenation of "c" and "c".

#include <algorithm>

int solve(std::vector<std::string>& words) {
  // shorter words have to be processed first
  std::sort(words.begin(), words.end(),
    [] (const std::string& first, const std::string& second) -> bool {
      return first.length() < second.length();
    });

  Trie trie;
  int answer = 0;
  for (const auto& word : words) {
    if (trie.IsConcatenation(word)) {
      ++answer;
    }
    trie.Add(word);
  }
  return answer;
}

// Example Usage
// # Distinct Substrings

// Given a string s, return the number of distinct non-empty substrings.

// ## Constraints

// - 0 ≤ n ≤ 1,000 where n is the length of s

// ## Example 1

// ### Input
// s = "aaab"

// ### Output
// 7

// ### Explanation
// We have the following distinct substrings:

// "a"
// "aa"
// "aaa"
// "aaab"
// "aab"
// "ab"
// "b"

int solve(const std::string& string) {
  Trie trie;
  const int length = string.length();
  for (int position = 0; position < length; ++position) {
    trie.AddPrefixes(string.substr(position));
  }
  return trie.Size();
}

// Example Usage
// # Mindboggling

// Given a 4 x 4 board of letters and a list of valid words, return the largest 
// number of words that can be formed in the board by a sequence of adjacent 
// letters, using each cell at most once per word (but you can reuse cells for 
// other words). You can go up, down, left, right, or diagonal.

// ## Example 1

// ### Input
// matrix = [
//     ["a", "b", "c", "d"],
//     ["x", "a", "y", "z"],
//     ["t", "z", "r", "r"],
//     ["s", "q", "q", "q"]
// ]
// words = ["bar", "car", "cat"]

// ### Output
// 3

// ### Explanation
// We can form "bar" [0,1] -> [1,1] -> [2,0],
// "car" [0,2] -> [1,1] -> [2,2], and "cat" [0,2] -> [1,1] -> [2,0].

using Board = std::vector<std::vector<std::string>>;

int solve(Board& board, std::vector<std::string>& words) {
  std::unordered_set<std::string> found;
  Trie trie;
  for (const auto& word : words) {
    trie.Add(word);
  }
  for (auto row = 0; row < 4; ++row) {
    for (auto column = 0; column < 4; ++column) {
      trie.BoardDepthFirstSearch(board, row, column, found);
    }
  }
  return found.size();
}
