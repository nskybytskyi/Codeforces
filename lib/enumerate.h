#include <iterator>
#include <utility>

template <typename Iterator>
using ValueType = typename std::iterator_traits<Iterator>::value_type;

template <typename T>
using IndexedValue = std::pair<int, T>;

template <class InputIt>
std::vector<IndexedValue<ValueType<InputIt>>> Enumerate(InputIt first, InputIt last);
