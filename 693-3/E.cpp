#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

using Person = pair<pair<int, int>, int>;

std::vector<Person> ReadArray(int size = 0, std::istream& in_stream = std::cin) {
  if (!size) {
    in_stream >> size;
  }
  std::vector<Person> array(size);
  for (auto& element : array) {
    in_stream >> element.first.first >> element.first.second;
  }
  return array;
}

Person Key(const Person& person) {
  return {{person.first.first, -person.first.second}, person.second};
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    auto people = ReadArray();
    const int num_people = people.size();
    for (int person_id = 0; person_id < num_people; ++person_id) {
      auto& person = people[person_id];
      if (person.first.first > person.first.second) {
        swap(person.first.first, person.first.second);
      }
      person.second = person_id;
    }


    sort(people.begin(), people.end(),
      [] (const Person& first, const Person& second) -> bool {
        return Key(first) < Key(second);
      });

    vector<int> answer(num_people, -1);
    int min_height_index = 0;
    for (int person_id = 0; person_id < num_people; ++person_id) {
      const auto& person = people[person_id];
      if (people[min_height_index].first.second > person.first.second) {
        min_height_index = person_id;
      } 
      if (people[min_height_index].first.second < person.first.second) {
        answer[person.second] = people[min_height_index].second + 1;
      }
    }

    for (auto element : answer) {
      cout << element << " ";
    }
    cout << "\n";
  }

  return 0;
}
