#pragma once

#include "geometry/hittable_object.h"
#include "material/material.h"
#include "vec3.h"
#include <memory>

class Sphere : public HittableObject {
public:
  Sphere(const Point3 &center, double radius,
         std::unique_ptr<Material> material)
      : center_(center), radius_(radius), material_{std::move(material)} {}

  bool Hit(const Ray &ray, const Interval<double> &ray_interval,
           HitRecord &hit_record) const override {

    Vec3 oc = center_ - ray.origin();
    auto a = dot(ray.direction(), ray.direction());
    // use h = b/(-2) in the quadratic to simplify some of the math
    auto h = dot(oc, ray.direction());
    auto c = dot(oc, oc) - radius_ * radius_;
    auto discriminant = h * h - a * c;

    if (discriminant < 0) {
      return false;
    }

    auto discriminant_sqrt = std::sqrt(discriminant);
    auto root = (h - discriminant_sqrt) / a;
    if (!ray_interval.surrounds(root)) {
      root = (h + discriminant_sqrt) / a;
      if (!ray_interval.surrounds(root)) {
        return false;
      }
    }

    // populate hit record
    hit_record.t = root;
    hit_record.p = ray.at(hit_record.t);
    Vec3 outward_normal = (hit_record.p - center_) / radius_;
    hit_record.set_face_normal(ray, outward_normal);
    hit_record.material = material_.get();

    return true;
  }

private:
  Point3 center_;
  double radius_;
  std::unique_ptr<Material> material_;
};
