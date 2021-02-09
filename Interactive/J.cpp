#include <iostream>
#include <string>
#include <vector>

int ask(const std::string& spell) {
  std::cout << spell << std::endl << std::flush;
  std::cout.flush();

  int edit_distance;
  std::cin >> edit_distance;
  if (!edit_distance) {
    exit(0);
  } else if (edit_distance == -1) {
    exit(1);
  } else {
    return edit_distance;
  }
}

int main() {
  const int max_length = 300;
  int a_count = max_length - ask(std::string(max_length, 'a'));
  int b_count = max_length - ask(std::string(max_length, 'b'));
  const int length = a_count + b_count;

  std::vector<int> answers = {b_count};
  for (int query = 0; query + 1 < length; ++query) {
    const std::string prefix = std::string(query + 1, 'b');
    const std::string suffix = std::string(length - query - 1, 'a');
    answers.push_back(ask(prefix + suffix));
  }

  std::string spell;
  for (int query = 0; query + 1 < length; ++query) {
    if (answers[query + 1] < answers[query]) {
      spell += 'b';
      --b_count;
    } else {  // answers[query + 1] > answers[query]
      spell += 'a';
      --a_count;
    }
  }

  if (a_count) {
    spell += 'a';
  } else {  // b_count;
    spell += 'b';
  }

  ask(spell);

  return 0;
}
