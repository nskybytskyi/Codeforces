#include <bits/stdc++.h>
using namespace std;
int count_occurences(string text, string pattern) {
  int occurences_count = 0, position = 0;
  while ((position = text.find(pattern, position)) != string::npos) {
    ++occurences_count;
    ++position;
  }
  return occurences_count;
}
struct StringInfo {
  string prefix, suffix;
  int64_t haha_count = 0;
  StringInfo() { }
  StringInfo(string& string) {
    haha_count = count_occurences(string, "haha");
    int length = string.length();
    int ps_length = min(length, 3);
    prefix = string.substr(0, ps_length);
    suffix = string.substr(length - ps_length, ps_length);
  }
  StringInfo operator+(StringInfo other) const {
    StringInfo concatenation;
    auto concatenation_prefix = prefix + other.prefix;
    concatenation.prefix = concatenation_prefix.substr(0, min(concatenation_prefix.length(), static_cast<size_t>(3)));
    auto concatenation_suffix = suffix + other.suffix;
    auto cs_length = concatenation_suffix.length();
    auto cs_length_ = min(cs_length, static_cast<size_t>(3));
    concatenation.suffix = concatenation_suffix.substr(cs_length - cs_length_, cs_length_);
    concatenation.haha_count = haha_count + count_occurences(suffix + other.prefix, "haha") + other.haha_count;
    return concatenation;
  }
};
int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t; cin >> t; while (t--) {
    map<string, StringInfo> mp;
    string variable, operation, value, first_operand, second_operand;
    int n; cin >> n; while (n--) {
      cin >> variable >> operation;
      if (operation == ":=") {
        cin >> value;
        mp[variable] = StringInfo(value);
      } else {  // operation == "="
        cin >> first_operand >> operation >> second_operand;
        mp[variable] = mp[first_operand] + mp[second_operand];
      }
    }
    cout << mp[variable].haha_count << "\n";
  }
  return 0;
}