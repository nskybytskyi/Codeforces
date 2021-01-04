#include <cstdio>
#include <functional>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <utility>
#include <vector>

struct TimetableSegment {
  int time, velocity;
  TimetableSegment(int time_ = 0, int velocity_ = 0) : time(time_), velocity(velocity_) { }
  friend std::istream& operator>>(std::istream& in_stream, TimetableSegment& timetable_segment);
};

template <typename T = int>
T BinarySearch(T lower_bound, T upper_bound, std::function<bool(T)> unary_predicate, T precision = 1);

template <typename T = int>
std::vector<T> ReadArray(int size = 0, std::istream& in_stream = std::cin);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::freopen("trains.in", "r", stdin);
  std::freopen("trains.out", "w", stdout);

  int minimal_distance;
  std::cin >> minimal_distance;
  int timetable_segments_count;
  std::cin >> timetable_segments_count;
  auto timetable_segments = ReadArray<TimetableSegment>(timetable_segments_count);

  std::partial_sum(timetable_segments.begin(), timetable_segments.end(), timetable_segments.begin(),
    [] (TimetableSegment accumulator, TimetableSegment timetable_segment) -> TimetableSegment {
      return {accumulator.time + timetable_segment.time, timetable_segment.velocity};
    });

  long double lower_bound = 0, upper_bound = 1e9, precision = 1e-6;
  auto unary_predicate = [&] (long double train_departure_interval) -> bool {
    long double time = 0.;
    int first_index = 0, second_index = -1;
    long double first_position = 0., second_position = 0.;

    while (first_index < timetable_segments_count) {
      long double first_time = timetable_segments[first_index].time;
      long double second_time = train_departure_interval;
      if (second_index != -1) {
        second_time += timetable_segments[second_index].time;
      }

      long double next_time = std::min(first_time, second_time);

      first_position += timetable_segments[first_index].velocity * (next_time - time);
      if (second_index != -1) {
        second_position += timetable_segments[second_index].velocity * (next_time - time);
      }

      time = next_time;

      if (first_time < second_time) {
        ++first_index;
      } else if (first_time > second_time) {
        ++second_index;
      } else {
        ++first_index;
        ++second_index;
      }

      if (second_index != -1 && first_position - second_position < minimal_distance) {
        return true;
      }
    }
    return false;
  };

  std::cout << std::fixed << std::setprecision(10) \
    << BinarySearch<long double>(lower_bound, upper_bound, unary_predicate, precision) << "\n";

  return 0;
}

std::istream& operator>>(std::istream& in_stream, TimetableSegment& timetable_segment) {
  in_stream >> timetable_segment.time >> timetable_segment.velocity;
  return in_stream;
}

template <typename T>
T BinarySearch(T lower_bound, T upper_bound, std::function<bool(T)> unary_predicate, T precision) {
  while (lower_bound + precision < upper_bound) {
    T middle = lower_bound + (upper_bound - lower_bound) / 2;
    if (unary_predicate(middle)) {
      lower_bound = middle;
    } else {
      upper_bound = middle;
    }
  }
  return lower_bound;
}

template <typename T>
std::vector<T> ReadArray(int size, std::istream& in_stream) {
  if (!size) {
    in_stream >> size;
  }
  std::vector<T> array(size);
  for (auto& element : array) {
    in_stream >> element;
  }
  return array;
}
