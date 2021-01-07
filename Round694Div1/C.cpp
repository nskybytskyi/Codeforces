#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

template <typename T = int>
std::vector<T> ReadArray(int size = 0, std::istream& in_stream = std::cin);

// answer is always <= 2 k 
vector<int> past_answers;

inline int ask(int q) {
  cout << "?" << " " << q + 1 << "\n";
  cout.flush();
  cin >> past_answers[q];
  return past_answers[q];
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n, k;
  cin >> n >> k;
  past_answers.resize(n);

  // 'traitor' always has k cards
  // also if n is even then direct opposite always has k cards
  // people in (traitor, opposite) have more cards after some step
  // people in (opposite, traitor) have less cards after some step
  // cards[traitor + i] + cards[traitor - i] = 2k

  int q = 0, step = 1;
  for (int i = 0; i < 2; ++i) {  // must hit answer != k unless something 'special' happens
    while (q < n) {  // q = 1 3 6 12 ...
      if (step == 1) assert(q == 0);
      if (step == 2) assert(q == 2);
      if (step == 3) assert(q == 6);
      if (step == 4) assert(q == 12);
      // q = step^2 - step + 1
      // 330^2 - 330 + 1 > 100'000
      // so at most 330 questions here

      int answer = ask(q);
      if (answer > k) { // traitor in (q - step, q)
        for (int t = max(0, q - step + 1); t < q; ++t) {
          if (ask(t) == k) {
            cout << "!" << " " << t + 1 << "\n";
            cout.flush();
            return 0;
          }
        }
      } 
      if (answer < k) {  // traitor in (q, q + step)
        for (int t = q + 1; t < min(n, q + step); ++t) {
          if (ask(t) == k) {
            cout << "!" << " " << t + 1 << "\n";
            cout.flush();
            return 0;
          }
        }
      }

      q += step << 1;
      ++step;
    }
  }

  // n <= 10;
  for (int i = 0; i < n; ++i) {
    ask(i);
  }
  for (int i = 0; i < n; ++i) {
    if (ask(i) == k) {  // either a traitor or a direct opposite of a traitor
      int prev = i ? i - 1 : n - 1;
      if (ask(prev) < k) {
        cout << "!" << " " << i + 1 << "\n";
        cout.flush();
        return 0;
      } else {  // n is even
        int traitor = i + (n >> 1);
        if (traitor > n)
          traitor -= n;
        cout << "!" << " " << traitor + 1 << "\n";
        cout.flush();
        return 0;
      }
    }
  }

  return 0;
}

template <typename T>
std::vector<T> ReadArray(int size, std::istream& in_stream) {
  if (!size) {
    in_stream >> size;
  }
  std::vector<T> array(size);
  for (auto& element : array) {
    in_stream >> element;
  }
  return array;
}
