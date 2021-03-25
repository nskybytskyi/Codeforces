// Algorithms Live - Episode 3 - Rolling Hashes and Bloom Filters
#include <deque>
#include <string>
#include <vector>

template <int64_t mod>
class ModularInteger {
  public:
    explicit ModularInteger(int64_t value) {
      value_ = value % mod;
      if (value_ < 0) {
        value_ += mod;
      }
    }

    ModularInteger& operator+=(const ModularInteger& other) {
      value_ += other.value_;
      if (value_ >= mod) {
        value_ -= mod;
      }
      return *this;
    }

    ModularInteger& operator-=(const ModularInteger& other) {
      value_ -= other.value_;
      if (value_ < 0) {
        value_ += mod;
      }
      return *this;
    }

    ModularInteger& operator*=(const ModularInteger& other) {
      value_ *= other.value_;
      value_ %= mod;
      return *this;
    }

    ModularInteger& operator+=(int64_t other) {
      return *this += ModularInteger(other);
    }

    ModularInteger& operator-=(int64_t other) {
      return *this -= ModularInteger(other);
    }

    ModularInteger& operator*=(int64_t other) {
      return *this *= ModularInteger(other);
    }

    ModularInteger operator+(const ModularInteger& other) {
      return ModularInteger(*this) += other;
    }

    ModularInteger operator-(const ModularInteger& other) {
      return ModularInteger(*this) -= other;
    }

    ModularInteger operator*(const ModularInteger& other) {
      return ModularInteger(*this) *= other;
    }

    ModularInteger operator+(int64_t other) {
      return *this + ModularInteger(other);
    }

    ModularInteger operator-(int64_t other) {
      return *this - ModularInteger(other);
    }

    ModularInteger operator*(int64_t other) {
      return *this * ModularInteger(other);
    }

    static ModularInteger power(ModularInteger base, int64_t power) {
      ModularInteger result(1);
      while (power) {
        if (power & 1) {
          result *= base;
        }
        base *= base;
        power >>= 1;
      }
      return result;
    }

    static ModularInteger power(int64_t base, int64_t power) {
      return power(ModularInteger(base), power);
    }

    static ModularInteger inverse(ModularInteger number) {
      return power(number, mod - 2);
    }

    static ModularInteger inverse(int64_t number) {
      return power(ModularInteger(number), mod - 2);
    }

    int64_t value() const {
      return value_;
    }

  private:
    int64_t value_;
};

template <int64_t base, int64_t mod>
class RollingHash {
  using mint = ModularInteger<mod>;

  public:
    RollingHash() {}

    explicit RollingHash(size_t max_size) {
      for (size_t power = powers_.size(); power < max_size; ++power) {
        powers_.push_back(powers_.back() * base);
      }
    }

    explicit RollingHash(const std::string& string) {
      for (auto letter : string) {
        push_back(letter);
      }
    }

    void push_back(char letter) {
      letters_.push_back(letter);
      UpdatePowers();
      value_ *= base;
      value_ += LetterValue(letter);
    }

    void push_front(char letter) {
      value_ += powers_[letters_.size()] * LetterValue(letter);
      letters_.push_front(letter);
      UpdatePowers();
    }

    void pop_back() {
      value_ -= LetterValue(letters_.back());
      value_ *= kInverseBase;
      letters_.pop_back();
    }

    void pop_front() {
      value_ -= powers_[letters_.size() - 1] * LetterValue(letters_.front());
      letters_.pop_front();
    }

    int64_t value() const {
      return value_.value();
    }

  private:
    inline static const mint kInverseBase = mint::inverse(base);
    inline static std::vector<mint> powers_ = {mint(1)};

    void UpdatePowers() {
      for (size_t power = powers_.size(); power < letters_.size(); ++power) {
        powers_.push_back(powers_.back() * base);
      }
    }

    int64_t LetterValue(char letter) {
      return letter - 'a' + 1;
    }

    mint value_ = mint(0);
    std::deque<char> letters_;
};

using srh7 = RollingHash<27, 1'000'000'007>;
using srh9 = RollingHash<27, 1'000'000'009>;
using srh23 = RollingHash<27, 1'000'000'023>;

std::string::size_type RabinKarp(const std::string& text,
                                 const std::string& pattern,
                                 bool safe = false) {
  const auto text_length = text.length(); 
  const auto pattern_length = pattern.length();

  if (pattern_length > text_length) {
    return std::string::npos;
  }

  const auto ph7 = srh7(pattern).value();
  const auto ph9 = srh9(pattern).value();
  const auto ph23 = srh23(pattern).value();

  const auto prefix = text.substr(0, pattern_length);

  srh7 rh7(prefix);
  srh9 rh9(prefix);
  srh23 rh23(prefix);

  auto position = 0;

  auto match = [&] () -> bool {
    return rh7.value() == ph7 && rh9.value() == ph9 && rh23.value() == ph23
      && (!safe || text.substr(position, pattern_length) == pattern);
  };

  while (position + pattern_length < text_length) {
    if (match()) {
      return position;
    }

    const auto letter = text[position + pattern_length];

    rh7.push_back(letter);
    rh9.push_back(letter);
    rh23.push_back(letter);

    rh7.pop_front();
    rh9.pop_front();
    rh23.pop_front();

    ++position;
  }

  if (match()) {
    return position;
  } else {
    return std::string::npos;
  }
}

#include <cassert>
#include <iostream>

int main() {
  {  // test 1
    std::string word = "helloworld";
    srh7 rh(word.length());

    std::vector<int> expected = {0, 8, 221, 5'979, 161'445, 4'359'030,
      117'693'833, 177'733'485, 798'804'085, 567'710'160, 328'174'219,
      548'721'358, 401'048'837, 876'811'283, 227'765'443, 12'531'838, 308'695,
      13'450, 328, 4, 0};

    std::vector<int> actual;

    actual.push_back(rh.value());
    for (auto letter : word) {
      rh.push_back(letter);
      actual.push_back(rh.value());
    }
    for (auto letter : word) {
      rh.pop_front();
      actual.push_back(rh.value());
    }

    assert(actual == expected);
  }  // test 1

  {  // test 2
    std::string word = "helloworld";
    RollingHash<28, 1'000'000'007> rh(word.length());

    std::vector<int> expected = {0, 8, 229, 6'424, 179'884, 5'036'767,
      141'029'499, 948'825'966, 567'126'884, 879'552'659, 627'474'288,
      980'439'420, 970'460'963, 55'319'946, 272'636'340, 14'480'820, 343'732,
      14'452, 340, 4, 0};

    std::vector<int> actual;

    actual.push_back(rh.value());
    for (auto letter : word) {
      rh.push_back(letter);
      actual.push_back(rh.value());
    }
    for (auto letter : word) {
      rh.pop_front();
      actual.push_back(rh.value());
    }

    assert(actual == expected);
  }  // test 2

  {  // test 3
    std::string word = "helloworld";
    RollingHash<27, 998'244'353> rh(word.length());

    std::vector<int> expected = {0, 8, 221, 5'979, 161'445, 4'359'030,
      117'693'833, 183'000'447, 948'034'675, 640'827'412, 332'186'127,
      261'206'767, 629'283'857, 883'833'899, 227'765'443, 12'531'838, 308'695,
      13'450, 328, 4, 0};

    std::vector<int> actual;

    actual.push_back(rh.value());
    for (auto letter : word) {
      rh.push_back(letter);
      actual.push_back(rh.value());
    }
    for (auto letter : word) {
      rh.pop_front();
      actual.push_back(rh.value());
    }

    assert(actual == expected);
  }  // test 3

  {  // test 4
    std::string text = "helloworld";
    std::string pattern = "hello";

    auto expected = text.find(pattern);

    auto actual = RabinKarp(text, pattern);

    assert(actual == expected);
  }  // test 4

  {  // test 5
    std::string text = "helloworld";
    std::string pattern = "world";

    auto expected = text.find(pattern);

    auto actual = RabinKarp(text, pattern);

    assert(actual == expected);
  }  // test 5

  {  // test 6
    std::string text = "helloworld";
    std::string pattern = "false";

    auto expected = text.find(pattern);

    auto actual = RabinKarp(text, pattern);

    assert(actual == expected);
  }  // test 6

  return 0;
}
