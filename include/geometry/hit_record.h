#pragma once

#include "ray.h"
#include "vec3.h"

class Material;

struct HitRecord {
  double t;
  Point3 p;
  Vec3 normal;
  bool front_face;
  Material *material;

  /**
   * @brief Sets the hit record normal vector
   *
   * @param ray Ray
   * @param outward_normal Normal vector (unit length)
   */
  void set_face_normal(const Ray &ray, const Vec3 &outward_normal);
};
