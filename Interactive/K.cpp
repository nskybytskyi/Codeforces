#include <algorithm>
#include <iostream>
#include <vector>

enum QueryType {
  kArea = 1,
  kCrossProduct = 2
};

int64_t ask(QueryType query_type, int64_t first_index,
            int64_t second_index, int64_t third_index) {
  std::cout << query_type << " " << first_index + 1 << " "
    << second_index + 1 << " " << third_index + 1 << std::endl << std::flush;
  std::cout.flush();

  int64_t answer;
  std::cin >> answer;
  return answer;
}

void answer(const std::vector<int64_t>& permutation) {
  std::cout << "0";
  for (auto index : permutation) {
    std::cout << " " << index + 1;
  }
  std::cout << std::endl << std::flush;
  std::cout.flush();
}

int main() {
  int64_t vertex_count;
  std::cin >> vertex_count;

  std::vector<int64_t> left, right;
  for (int64_t third_index = 2; third_index < vertex_count; ++third_index) {
    if (ask(kCrossProduct, 0, 1, third_index) == 1) {
      left.push_back(third_index);
    } else {  // ask(kCrossProduct, 0, 1, third_index) == -1
      right.push_back(third_index);
    }
  }

  std::vector<int64_t> area(vertex_count);
  for (int64_t third_index = 2; third_index < vertex_count; ++third_index) {
    area[third_index] = ask(kArea, 0, 1, third_index);
  }

  std::vector<int64_t> permutation = {0};

  // solve right half
  if (!right.empty()) {
    int64_t rightmost = *std::max_element(right.begin(), right.end(),
      [&] (int64_t first, int64_t second) -> bool {
        return area[first] < area[second];
      });

    std::vector<int64_t> right_bottom, right_top;

    for (auto vertex : right) {
      if (vertex != rightmost) {
        if (ask(kCrossProduct, 0, rightmost, vertex) == -1) {
          right_bottom.push_back(vertex);
        } else {  // ask(kCrossProduct, 1, rightmost, vertex) == 1
          right_top.push_back(vertex);
        }
      }
    }

    std::sort(right_bottom.begin(), right_bottom.end(),
      [&] (int64_t first, int64_t second) -> bool {
        return area[first] < area[second];
      });

    std::copy(right_bottom.begin(), right_bottom.end(),
      std::back_inserter(permutation));

    permutation.push_back(rightmost);

    std::sort(right_top.begin(), right_top.end(),
      [&] (int64_t first, int64_t second) -> bool {
        return area[first] > area[second];
      });

    std::copy(right_top.begin(), right_top.end(),
      std::back_inserter(permutation));
  }

  permutation.push_back(1);

  // solve left half
  if (!left.empty()) {
    int64_t leftmost = *std::max_element(left.begin(), left.end(),
      [&] (int64_t first, int64_t second) -> bool {
        return area[first] < area[second];
      });

    std::vector<int64_t> left_bottom, left_top;

    for (auto vertex : left) {
      if (vertex != leftmost) {
        if (ask(kCrossProduct, 1, leftmost, vertex) == -1) {
          left_bottom.push_back(vertex);
        } else {  // ask(kCrossProduct, 0, leftmost, vertex) == 1
          left_top.push_back(vertex);
        }
      }
    }

    std::sort(left_bottom.begin(), left_bottom.end(),
      [&] (int64_t first, int64_t second) -> bool {
        return area[first] < area[second];
      });

    std::copy(left_bottom.begin(), left_bottom.end(),
      std::back_inserter(permutation));

    permutation.push_back(leftmost);

    std::sort(left_top.begin(), left_top.end(),
      [&] (int64_t first, int64_t second) -> bool {
        return area[first] > area[second];
      });

    std::copy(left_top.begin(), left_top.end(),
      std::back_inserter(permutation));
  }

  answer(permutation);

  return 0;
}
