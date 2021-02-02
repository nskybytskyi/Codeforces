#include <iostream>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int left, right, down, up;
    cin >> left >> right >> down >> up;

    int start_x, start_y, left_border, right_border,
      bottom_border, top_border;
    cin >> start_x >> start_y >> left_border
      >> bottom_border >> right_border >> top_border;

    bool possible = true;
    if (bottom_border == top_border) {
      if (down || up) {
        possible = false;
      }
    } else {
      const int shift_y = up - down;
      const int final_y = start_y + shift_y;
      if (final_y < bottom_border || final_y > top_border) {
        possible = false;
      }
    }

    if (left_border == right_border) {
      if (left || right) {
        possible = false;
      }
    } else {
      const int shift_x = right - left;
      const int final_x = start_x + shift_x;
      if (final_x < left_border || final_x > right_border) {
        possible = false;
      }
    }

    cout << (possible ? "YES" : "NO") << "\n";
  }

  return 0;
}
