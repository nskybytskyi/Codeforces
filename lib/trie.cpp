class Trie {
  private:
    struct Node {
      bool is_word_end = false;
      std::unordered_map<char, std::unique_ptr<Node>> children;
    };

  public:
    Trie(char wildcard = '.') : kWildcard(wildcard) { }

    void Add(const std::string& word) {
      auto node = root_.get();
      for (auto letter : word) {
        if (!node->children.count(letter)) {
          node->children[letter] = std::make_unique<Node>();
        }
        node = node->children[letter].get();
      }
      node->is_word_end = true;
    }

    bool Exists(const std::string& word, Node* node = nullptr, int offset = 0) const {
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
            any |= Exists(word, child.get(), offset);
          }
          return any;
        }
      }
      return node->is_word_end;
    }

    bool StartsWith(const std::string& prefix, Node* node = nullptr, int offset = 0) const {
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
            any |= StartsWith(prefix, child.get(), offset);
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
        if (letter != kWildcard) {
          if (!node->children.count(letter)) {
            return false; 
          }
          node = node->children[letter].get();
        } else {
          bool any = false;
          for (const auto& [_, child] : node->children) {
            any |= StartsWith(word, child.get(), offset);
          }
          return any;
        }
      }
      return node->is_word_end;
    }

  private:
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
