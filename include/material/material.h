#pragma once

#include "color.h"
#include "geometry/hit_record.h"
#include "ray.h"

class Material {
public:
  virtual ~Material() = default;

  virtual bool Scatter(const Ray &ray_in, const HitRecord &hit_record,
                       Color &attenuation, Ray &scattered) const {
    return false;
  }
};
