#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  auto ask = [&] (int l, int r) -> int {
    cout << "? " << l + 1 << " " << r << endl << flush;
    int i;
    cin >> i;
    --i;
    return i;
  };
  auto answer = [&] (int p) -> void {
    cout << "! " << p + 1 << endl << flush;
  };
  int n;
  cin >> n;
  int l = 0, r = n;
  int pa = ask(l, r);
  while (l + 3 < r) {
    int m = (l + r) >> 1;
    if (pa < m) {
      int a = ask(l, m);
      if (a == pa) {
        r = m;
      } else {
        l = m;
        pa = ask(m, r);
      }
    } else {  // pa >= m
      int a = ask(m, r);
      if (a == pa) {
        l = m;
      } else {
        r = m;
        pa = ask(l, m);
      }
    }
  }
  if (r == l + 2) {
    if (l == pa) {
      answer(l + 1);
    } else {
      answer(l);
    }
  } else {  // r == l + 3
    if (l == pa) {
      pa = ask(l + 1, r);
      if (pa == l + 1) {
        answer(l + 2);
      } else {
        answer(l + 1);
      }
    } else if (l + 1 == pa) {
      int a = ask(l, r - 1);
      if (a == pa) {
        answer(l);
      } else {
        answer(l + 2);
      }
    } else {
      pa = ask(l, r - 1);
      if (pa == l) {
        answer(l + 1);
      } else {
        answer(l);
      }
    }
  }
  return 0;
}
