#include <algorithm>
#include <iostream>
#include <vector>

struct Entity {
  int64_t attack, health;
  friend std::istream& operator>>(std::istream& is, Entity& entity) {
    is >> entity.attack >> entity.health;
    return is;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int testcase_count;
  std::cin >> testcase_count;
  while (testcase_count --> 0) {
    Entity hero;
    int monsters_count;
    int64_t total_damage = 0, max_damage = 0;
    std::cin >> hero >> monsters_count;
    std::vector<Entity> monsters(monsters_count);
    for (auto& monster : monsters) {
      std::cin >> monster.attack;
    }
    for (auto& monster : monsters) {
      std::cin >> monster.health;
    }
    for (auto monster : monsters) {
      total_damage += ((monster.health + hero.attack - 1) / hero.attack) * monster.attack;
      max_damage = std::max(max_damage, monster.attack);
    }
    if (total_damage - max_damage < hero.health) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
    }
  }

  return 0;
}
