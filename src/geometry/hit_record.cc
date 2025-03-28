#include "geometry/hit_record.h"

void HitRecord::set_face_normal(const Ray &ray, const Vec3 &outward_normal) {
  front_face = dot(ray.direction(), outward_normal) < 0;
  normal = front_face ? outward_normal : -outward_normal;
}
