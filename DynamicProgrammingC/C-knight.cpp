#include <iostream>
#include <vector>

namespace combinatorics {
  class FactorialsComputer {
    public:
      __int128 ComputeFactorial(int n);

    private:
      int size_ = 1;
      std::vector<__int128> factorials_ = {1};
  };

  class BinomialCoefficientsComputer {
    public:
      inline int64_t ComputeBinomialCoefficient(int n, int k);

    private:
      FactorialsComputer factorials_computer_;
  };
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("knight.in", "r", stdin);
  std::freopen("knight.out", "w", stdout);

  int row_count, column_count;
  std::cin >> row_count >> column_count;
  --row_count, --column_count;

  if ((row_count + column_count) % 3) {
    std::cout << 0 << "\n";
  } else {
    const int total_moves = (row_count + column_count) / 3;
    const int right_moves = 2 * total_moves - row_count;
    std::cout << combinatorics::BinomialCoefficientsComputer()\
      .ComputeBinomialCoefficient(total_moves, right_moves) << "\n";
  }

  return 0;
}

namespace combinatorics {
  __int128 FactorialsComputer::ComputeFactorial(int n) {
    while (size_ <= n) {
      factorials_.push_back(factorials_.back() * size_);
      ++size_;
    }
    return factorials_[n];
  }

  int64_t BinomialCoefficientsComputer::ComputeBinomialCoefficient(int n, int k) {
    return factorials_computer_.ComputeFactorial(n) \
      / (factorials_computer_.ComputeFactorial(k) \
        * factorials_computer_.ComputeFactorial(n - k));
  }
};
