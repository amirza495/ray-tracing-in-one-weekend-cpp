#pragma once

#include "color.h"
#include "material/material.h"

class Metal : public Material {
public:
  Metal(const Color &albedo, double fuzziness)
      : albedo_{albedo}, fuzz_{fuzziness < 1 ? fuzziness : 1} {}

  bool Scatter(const Ray &ray_in, const HitRecord &hit_record,
               Color &attenuation, Ray &scattered) const override {
    Vec3 reflected =
        reflect(unit_vector(ray_in.direction()), hit_record.normal);
    reflected = unit_vector(reflected) + fuzz_ * random_unit_vector();
    scattered = Ray(hit_record.p, reflected);
    attenuation = albedo_;
    return (dot(scattered.direction(), hit_record.normal) > 0);
  }

private:
  Color albedo_;
  double fuzz_;
};
