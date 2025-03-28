#pragma once

#include "interval.h"
#include "vec3.h"

#include <iostream>

using Color = Vec3;

namespace colors {
const Color white{1.0, 1.0, 1.0};
const Color black{0.0, 0.0, 0.0};
const Color red{1.0, 0.0, 0.0};
const Color green{0.0, 1.0, 0.0};
const Color blue{0.0, 0.0, 1.0};
const Color light_blue{0.5, 0.7, 1.0};
} // namespace colors

inline double LinearToGamma(double linear) {
  if (linear > 0) {
    return std::sqrt(linear);
  }

  return 0;
}

inline void WriteColor(std::ostream &out, const Color &pixel_color) {
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  r = LinearToGamma(r);
  g = LinearToGamma(g);
  b = LinearToGamma(b);

  // feels inefficient to use ints here, but utin8_t doesn't print correctly
  static const Interval<double> intensity{0.0, 0.999};
  int ir = static_cast<int>(255.999 * intensity.clamp(r));
  int ig = static_cast<int>(255.999 * intensity.clamp(g));
  int ib = static_cast<int>(255.999 * intensity.clamp(b));

  out << ir << ' ' << ig << ' ' << ib << '\n';
}
