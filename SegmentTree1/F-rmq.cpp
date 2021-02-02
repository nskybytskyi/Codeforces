#include <iostream>
#include <memory>
#include <random>

struct Treap {
  inline static std::mt19937 generator{0};

  int key, priority, min, size;
  Treap *left, *right;

  explicit Treap(int key) : key(key), min(key), size(1),
      left(nullptr), right(nullptr) {
    std::uniform_int_distribution<int> distribution(
      std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    priority = distribution(generator);
  }
};

using pTreap = Treap*;

void Update(pTreap treap);

int RangeMin(pTreap treap, int left, int right);

void Insert(pTreap& treap, int index, int value);

void Split(pTreap treap, int index, pTreap& left_treap, pTreap& right_treap);

pTreap Merge(pTreap left_treap, pTreap right_treap);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("rmq.in", "r", stdin);
  std::freopen("rmq.out", "w", stdout);

  pTreap treap = nullptr;

  int query_count;
  std::cin >> query_count;
  while (query_count --> 0) {
    char query_type;
    std::cin >> query_type;

    if (query_type == '+') {
      int index, value;
      std::cin >> index >> value;
      Insert(treap, index, value);
    } else {  // query_type == '?'
      int left, right;
      std::cin >> left >> right;
      std::cout << RangeMin(treap, left - 1, right - 1) << "\n";
    }
  }

  return 0;
}

void Update(pTreap treap) {
  treap->size = 1;
  treap->min = treap->key;
  if (treap->left) {
    treap->size += treap->left->size;
    treap->min = std::min(treap->min, treap->left->min);
  }
  if (treap->right) {
    treap->size += treap->right->size;
    treap->min = std::min(treap->min, treap->right->min);
  }
}

int RangeMin(pTreap treap, int left, int right) {
  pTreap left_treap, middle_treap, right_treap;
  Split(treap, left, left_treap, middle_treap);
  Split(middle_treap, right - left + 1, middle_treap, right_treap);
  const int min = middle_treap->min;
  treap = Merge(left_treap, Merge(middle_treap, right_treap));
  return min;
}

void Insert(pTreap& treap, int index, int value) {
  auto node = new Treap(value);
  pTreap left_treap, right_treap;
  Split(treap, index, left_treap, right_treap);
  treap = Merge(left_treap, Merge(node, right_treap));
}

void Split(pTreap treap, int index, pTreap& left_treap, pTreap& right_treap) {
  if (!treap) {
    left_treap = right_treap = nullptr;
  } else {
    const int root_index = 1 + (treap->left ? treap->left->size : 0);
    if (root_index <= index) {
      Split(treap->right, index - root_index, treap->right, right_treap);
      Update(treap);
      left_treap = treap;
    } else {  // root_index > index
      Split(treap->left, index, left_treap, treap->left);
      Update(treap);
      right_treap = treap;
    }
  }
}

pTreap Merge(pTreap left_treap, pTreap right_treap) {
  if (!left_treap) {
    return right_treap;
  } else if (!right_treap) {
    return left_treap;
  } else if (left_treap->priority < right_treap->priority) {
    left_treap->right = Merge(left_treap->right, right_treap);
    Update(left_treap);
    return left_treap;
  } else {  // left_treap->priority >= right_treap->priority
    right_treap->left = Merge(left_treap, right_treap->left);
    Update(right_treap);
    return right_treap;
  }
}
