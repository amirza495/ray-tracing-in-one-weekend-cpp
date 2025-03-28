#pragma once

#include "color.h"
#include "geometry/hit_record.h"
#include "material/material.h"

class Lambertian : public Material {
public:
  Lambertian(const Color &albedo) : albedo_{albedo} {}

  bool Scatter(const Ray &ray_in, const HitRecord &hit_record,
               Color &attenuation, Ray &scattered) const override {
    Vec3 scatter_direction = hit_record.normal + random_unit_vector();

    if (scatter_direction.near_zero()) {
      scatter_direction = hit_record.normal;
    }

    scattered = Ray(hit_record.p, scatter_direction);
    attenuation = albedo_;
    return true;
  }

private:
  Color albedo_;
};
