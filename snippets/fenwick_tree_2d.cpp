template <typename T>
struct fenwick_tree_2d {
  int h, w;
  vector<vector<T>> t;
 
  explicit fenwick_tree_2d(int h, int w)
    : h(h), w(w), t(h, vector<T>(w)) { }
 
  void add(int x, int y, T add) {
    for (int i = x; i < h; i = (i | (i + 1))) {
      for (int j = y; j < w; j = (j | (j + 1))) {
        t[i][j] += add;
      }
    }
  }
 
  T sum(int xl, int xr, int yl, int yr) {
    return sum(xr, yr) - sum(xl - 1, yr) - sum(xr, yl - 1) + sum(xl - 1, yl - 1);
  }
 
  T sum(int x, int y) {
    T sum = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
      for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
        sum += t[i][j];
      }
    }
    return sum;
  }
};
