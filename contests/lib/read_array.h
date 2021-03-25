#include <iostream>
#include <vector>

/* reads an array of given size from the input stream
 * if size is not provided then first reads the size from the input stream
 * before reading the array itself */ 
template <typename T = int>
std::vector<T> ReadArray(int size = 0, std::istream& in_stream = std::cin) {
  if (!size) {
    in_stream >> size;
  }
  std::vector<T> array(size);
  for (auto& element : array) {
    in_stream >> element;
  }
  return array;
}
