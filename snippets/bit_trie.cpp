template <unsigned int bits>
class bit_trie {
  public:
    explicit bit_trie(vector<int> a)
        : size_(1), next_(size_, vector<int>(2)) {
      for (auto ai : a) {
        insert(ai);   
      }
    }

    void insert(int ai) {
      auto node = 0;
      for (int j = bits - 1; j >= 0; --j) {
        auto aij = (ai >> j) & 1;
        if (!next_[node][aij]) {
          next_[node][aij] = size_++;
          next_.emplace_back(2);
        }
        node = next_[node][aij];
      }
    }

    auto min_xor(int ai) {
      auto ans = 0, node = 0;
      for (int j = bits - 1; j >= 0; --j) {
        auto aij = (ai >> j) & 1;
        if (next_[node][aij]) {
          node = next_[node][aij];
        } else {
          ans |= 1 << j;
          node = next_[node][!aij];
        }
      }
      return ans;
    }
    
    auto max_xor(int ai) {
      auto ans = 0, node = 0;
      for (int j = bits - 1; j >= 0; --j) {
        auto aij = (ai >> j) & 1;
        if (next_[node][!aij]) {
          ans |= 1 << j;
          node = next_[node][!aij];
        } else {
          node = next_[node][aij];
        }
      }
      return ans;
    }

  private:
    int size_;
    vector<vector<int>> next_;
};
