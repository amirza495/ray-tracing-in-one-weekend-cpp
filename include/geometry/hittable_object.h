#pragma once

#include "geometry/hit_record.h"
#include "interval.h"
#include "ray.h"

class HittableObject {
public:
  // make sure we hit derived destructor
  virtual ~HittableObject() = default;

  /**
   * @brief Check if ray hits the object
   * @param r Ray
   * @param t_min Minimum t value
   * @param t_max Maximum t value
   * @param[out] rec HitRecord
   */
  virtual bool Hit(const Ray &ray, const Interval<double> &ray_interval,
                   HitRecord &hit_record) const = 0;
};
