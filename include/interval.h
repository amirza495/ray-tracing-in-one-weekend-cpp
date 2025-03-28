#pragma once

#include <limits>

template <typename T> class Interval {
public:
  Interval()
      : min_(std::numeric_limits<T>::infinity()),
        max_(-std::numeric_limits<T>::infinity()) {}

  Interval(T min, T max) : min_(min), max_(max) {}

  T size() const { return max_ - min_; }

  bool contains(T t) const { return min_ <= t && t <= max_; }

  bool surrounds(T t) const { return min_ < t && t < max_; }

  T clamp(T x) const {
    if (x < min_)
      return min_;
    if (x > max_)
      return max_;
    return x;
  }

  T max() const { return max_; }

  T min() const { return min_; }

  static constexpr Interval<T> empty() {
    return Interval<T>(std::numeric_limits<T>::infinity(),
                       -std::numeric_limits<T>::infinity());
  }

  static constexpr Interval<T> universe() {
    return Interval<T>(-std::numeric_limits<T>::infinity(),
                       std::numeric_limits<T>::infinity());
  }

  static constexpr Interval<T> forward() {
    return Interval<T>(0.0, std::numeric_limits<T>::infinity());
  }

private:
  T min_;
  T max_;
};
