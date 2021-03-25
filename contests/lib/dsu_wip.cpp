class DSU {
  public:
    explicit DSU(int size);
    inline int GetComponentsCount() const;
    int Find(int vertex) const;
    void Union(int first, int second);

  private:
    int components_count_;
    mutable std::vector<int> parent_;
    std::vector<int> rank_;
};

DSU::DSU(int size) : components_count_(size) {
  rank_.resize(size);
  parent_.resize(size);
  std::iota(parent_.begin(), parent_.end(), 0);
}

int DSU::GetComponentsCount() const {
  return components_count_;
}

int DSU::Find(int vertex) const {
  return (vertex == parent_[vertex]) ? vertex : (parent_[vertex] = Find(parent_[vertex]));
}

void DSU::Union(int first, int second) {
  first = Find(first), second = Find(second);
  if (first != second) {
    --components_count_;
    if (rank_[first] < rank_[second]) {
      std::swap(first, second);
    }
    parent_[second] = first;
    if (rank_[first] == rank_[second]){
      ++rank_[first];
    }
  }
}
