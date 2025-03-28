#pragma once

#include "geometry/hittable_object.h"

#include <memory>
#include <vector>

class HittableObjectList : public HittableObject {
public:
  HittableObjectList() {}
  HittableObjectList(std::unique_ptr<HittableObject> object) {
    Add(std::move(object));
  }

  void Add(std::unique_ptr<HittableObject> object) {
    objects_.push_back(std::move(object));
  }

  void Clear() { objects_.clear(); }

  bool Hit(const Ray &ray, const Interval<double> &ray_interval,
           HitRecord &hit_record) const override {
    HitRecord temp_hit_record;
    bool hit_anything = false;
    auto closest_so_far = ray_interval.max();

    for (const auto &object : objects_) {
      if (object->Hit(ray, Interval(ray_interval.min(), closest_so_far),
                      temp_hit_record)) {
        hit_anything = true;
        if (temp_hit_record.t < closest_so_far) {
          closest_so_far = temp_hit_record.t;
          hit_record = temp_hit_record;
        }
      }
    }
    return hit_anything;
  }

private:
  std::vector<std::unique_ptr<HittableObject>> objects_;
};
