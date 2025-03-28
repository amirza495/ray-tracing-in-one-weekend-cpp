#pragma once

#include "utils.h"
#include <cmath>
#include <iostream>

struct Vec3 {
  double e[3];

  Vec3() : e{0, 0, 0} {}
  Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

  double x() const { return e[0]; }
  double y() const { return e[1]; }
  double z() const { return e[2]; }

  Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
  double operator[](int i) const { return e[i]; }
  double &operator[](int i) { return e[i]; }

  Vec3 &operator+=(const Vec3 &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }

  Vec3 &operator*=(const double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }

  Vec3 &operator/=(const double t) { return *this *= 1 / t; }

  double length() const { return std::sqrt(norm()); }

  double norm() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }

  static Vec3 random() {
    return Vec3(random_double(), random_double(), random_double());
  }

  static Vec3 random(double min, double max) {
    return Vec3(random_double(min, max), random_double(min, max),
                random_double(min, max));
  }

  bool near_zero() const {
    auto s = 1e-8;
    return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) &&
           (std::fabs(e[2]) < s);
  }
};

// define aliases for points
using Point3 = Vec3; // 3D point

// Utility functions
// He has more in the book, but I think they are at least partially redudant
// with the class overloads?

inline std::ostream &operator<<(std::ostream &out, const Vec3 &v) {
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vec3 operator/(const Vec3 &v, double t) {
  return Vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline Vec3 operator*(double t, const Vec3 &v) {
  return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) { return u + (-v); }

inline double dot(const Vec3 &u, const Vec3 &v) {
  return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
              u.e[2] * v.e[0] - u.e[0] * v.e[2],
              u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline Vec3 unit_vector(const Vec3 &v) { return v / v.length(); }

inline Vec3 random_unit_vector() {
  while (true) {
    auto p = Vec3::random(-1, 1);
    auto norm = p.norm();
    if (1e-160 < norm && norm <= 1) {
      return p / std::sqrt(norm);
    }
  }
}

inline Vec3 random_on_hemisphere(const Vec3 &normal) {
  Vec3 on_unit_sphere = random_unit_vector();
  if (dot(on_unit_sphere, normal) > 0.0) {
    return on_unit_sphere;
  } else {
    return -on_unit_sphere;
  }
}

inline Vec3 reflect(const Vec3 &v, const Vec3 &normal) {
  return v - 2 * dot(v, normal) * normal;
}
