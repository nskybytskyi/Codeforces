#include <numeric>
#include <utility>

#include "dsu.h"

class DSU {
  public:
    explicit DSU(int size) {
      rank_.resize(size);
      parent_.resize(size);
      std::iota(parent_.begin(), parent_.end(), 0);
    }

    int Find(int vertex) const {
      return (vertex == parent_[vertex]) ? vertex : (parent_[vertex] = Find(parent_[vertex]));
    }

    void Union(int first, int second) {
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

  private:
    mutable std::vector<int> parent_;
    std::vector<int> rank_;
};
