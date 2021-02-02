#include <iostream>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int k;
  cin >> k;

  cout << 2 << " " << 3 << "\n";
  cout << (1 << 18) - 1 << " " << (1 << 17) << " " << 0 << "\n";
  cout << k << " " << (1 << 18) - 1 << " " << k << "\n";

  return 0;
}
