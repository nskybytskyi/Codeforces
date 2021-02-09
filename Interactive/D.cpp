#include <algorithm>
#include <iostream>
#include <vector>

int ask(const std::vector<int>& first_part, const std::vector<int>& second_part) {
  std::cout << first_part.size() << " " << second_part.size();
  for (auto vertex : first_part) {
    std::cout << " " << vertex + 1; 
  }
  for (auto vertex : second_part) {
    std::cout << " " << vertex + 1;
  }
  std::cout << std::endl << std::flush;
  std::cout.flush();

  int answer;
  std::cin >> answer;
  if (answer == -1) {
    exit(1);
  } else {
    return answer;
  }
}

void answer(int max_distance) {
  std::cout << -1 << " " << max_distance << std::endl << std::flush;
  std::cout.flush();
  exit(0);
}

int main() {
  int testcase_count;
  std::cin >> testcase_count;
  while (testcase_count --> 0) {
    int vertex_count;
    std::cin >> vertex_count;
    int max_distance = 0;
    for (int query = 1; query < vertex_count; query <<= 1) {
      std::vector<int> first_part, second_part;
      for (int vertex = 0; vertex < vertex_count; ++vertex) {
        if (vertex & query) {
          first_part.push_back(vertex);
        } else {
          second_part.push_back(vertex);
        }
      }
      max_distance = std::max(max_distance, ask(first_part, second_part));
    }
    answer(max_distance);
  }
  return 0;
}
