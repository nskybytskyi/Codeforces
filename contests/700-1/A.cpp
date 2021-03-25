#include <bits/stdc++.h>
using namespace std;

int ask(int i) {
  cout << "?" << " " << i + 1 << endl;
  cout.flush();
  int answer;
  cin >> answer;
  return answer;
}

void answer(int k) {
  cout << "!" << " " << k + 1 << endl;
  cout.flush();
  exit(0);
} 

int main() {
  int n;
  cin >> n;

  if (n == 1) {
    answer(0);
  }

  vector<int> a(n);

  int l = 0, m, r = n - 1;
  while (l <= r) {
    m = (l + r) >> 1;

    if (m && !a[m - 1])
      a[m - 1] = ask(m - 1);
    if (!a[m])
      a[m] = ask(m);
    if (m + 1 < n && !a[m + 1])
      a[m + 1] = ask(m + 1);

    if ((!m || a[m - 1] > a[m]) && (m + 1 == n || a[m + 1] > a[m])) {
      answer(m);
    } else if (m && a[m - 1] < a[m]) {
      r = m;
    } else { // m + 1 && a[m + 1] < a[m]
      l = m;
    }
  }

  return 0;
}
