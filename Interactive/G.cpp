#include <array>
#include <iostream>

int ask(const std::array<int, 100>& array) {
  std::cout << "?";
  for (auto element : array) {
    std::cout << " " << element;
  }
  std::cout << std::endl << std::flush;
  std::cout.flush();

  int answer;
  std::cin >> answer;
  return answer;
}

void answer(int secret) {
  std::cout << "!" << " " << secret << std::endl << std::flush;
  std::cout.flush();
  exit(0);
}

int main() {
  std::array<int, 100> giant_array, baby_array;
  for (int i = 0; i < 100; ++i) {
    giant_array[i] = (i + 1) << 7;
    baby_array[i] = i;
  }
  auto baby_bits = ask(giant_array) & 127;
  auto giant_bits = ask(baby_array) & (127 << 7);
  answer(baby_bits | giant_bits);
  return 0;
}
