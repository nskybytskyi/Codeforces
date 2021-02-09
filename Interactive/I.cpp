#include <cassert>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

int ask(const std::vector<int>& set) {
  std::cout << "?" << " " << set.size();
  for (auto index : set) {
    std::cout << " " << index + 1;
  }
  std::cout << std::endl << std::flush;
  std::cout.flush();

  int max;
  std::cin >> max;
  if (max == -1) {
    exit(1);
  } else {
    return max;
  }
}

void answer(const std::vector<int>& password) {
  std::cout << "!";
  for (auto slot : password) {
    std::cout << " " << slot;
  }
  std::cout << std::endl << std::flush;
  std::cout.flush();

  std::string verdict;
  std::cin >> verdict;
  assert(verdict == "Correct");
  if (verdict == "Incorrect") {
    exit(1);
  }
}

int main() {
  int testcase_count;
  std::cin >> testcase_count;
  while (testcase_count --> 0) {
    int array_length, password_length;
    std::cin >> array_length >> password_length;

    std::vector<std::vector<int>> sets(password_length);
    for (auto& set : sets) {
      int set_size;
      std::cin >> set_size;
      set.resize(set_size);
      for (auto& index : set) {
        std::cin >> index;
        --index;
      }
    }

    std::vector<int> is_rest(array_length, true);
    for (auto& set : sets) {
      for (auto index : set) {
        is_rest[index] = false;
      }
    }

    std::vector<int> rest;
    for (int index = 0; index < array_length; ++index) {
      if (is_rest[index]) {
        rest.push_back(index);
      }
    }

    std::vector<int> all(array_length);
    std::iota(all.begin(), all.end(), 0);
    int global_max = ask(all);

    auto helper = [&] (int left_set_index, int right_set_index) -> int {
      std::vector<int> query_set;
      std::copy(rest.begin(), rest.end(), std::back_inserter(query_set));
      for (int set_index = left_set_index; set_index < right_set_index; ++set_index) {
        std::copy(sets[set_index].begin(), sets[set_index].end(),
          std::back_inserter(query_set));
      }
      int max = ask(query_set);
      return max;
    };

    int left_set_index = 0, right_set_index = password_length;
    while (left_set_index + 1 < right_set_index) {
      int middle_set_index = (left_set_index + right_set_index) >> 1;
      int subarray_max = helper(left_set_index, middle_set_index);
      if (subarray_max == global_max) {
        right_set_index = middle_set_index;
      } else {
        left_set_index = middle_set_index;
      }
    }
    int max_set_index = left_set_index;

    std::vector<int> last_query;
    std::copy(rest.begin(), rest.end(), std::back_inserter(last_query));
    for (int set_index = 0; set_index < password_length; ++set_index) {
      if (set_index != max_set_index) {
        std::copy(sets[set_index].begin(), sets[set_index].end(),
          std::back_inserter(last_query));
      }
    }
    int rest_max = ask(last_query);

    std::vector<int> password(password_length);
    for (int set_index = 0; set_index < password_length; ++set_index) {
      if (set_index != max_set_index) {
        password[set_index] = global_max;
      } else {
        password[set_index] = rest_max;
      }
    }
    answer(password);
  }

  return 0;
}
