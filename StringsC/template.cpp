std::vector<int> PrefixFunction(const std::string& string) {
  const int length = string.length();
  std::vector<int> prefix_function(length);
  for (int position = 1; position < length; ++position) {
    int suffix = prefix_function[position - 1];
    while (suffix && string[position] != string[suffix]) {
      suffix = prefix_function[suffix - 1];
    }
    if (string[position] == string[suffix]) {
      ++suffix;
    }
    prefix_function[position] = suffix;
  }
  return prefix_function;  
}

std::vector<int> KMPSearch(const std::string& text,
                           const std::string& pattern,
                           char sentinel) {
  const auto match_length = pattern.length();
  const auto offset = 2 * match_length;
  const auto concatenation = pattern + sentinel + text;
  const auto concatenation_length = concatenation.length();
  const auto prefix_function = PrefixFunction(concatenation);
  std::vector<int> match_positions;
  for (int position = match_length + 1; position < concatenation_length; ++position) {
    if (prefix_function[position] == match_length) {
      match_positions.push_back(position - offset);
    }
  }
  return match_positions;
}

