#include "counter.h"

template <class InputIt>
Counter<ValueType<InputIt>> BuildCounter(InputIt first, InputIt last) {
  Counter<ValueType<InputIt>> counter;
  for (auto it = first; it != last; ++it) {
    ++counter[*it];
  }
  return counter;
}
