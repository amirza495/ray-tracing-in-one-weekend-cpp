#pragma once

#include "color.h"
#include "geometry/hit_record.h"
#include "geometry/hittable_object.h"
#include "material/material.h"
#include "utils.h"

class Camera {
public:
  Camera(double aspect_ratio, int image_width, double vertical_fov,
         int samples_per_pixel, const Vec3 &camera_center, const Vec3 &look_at)
      : image_width_(image_width), aspect_ratio_(aspect_ratio),
        vertical_fov_{vertical_fov}, samples_per_pixel_{samples_per_pixel},
        camera_center_{camera_center}, look_at_{look_at}, up_{0, 1, 0} {
    // Calculate image height
    image_height_ = static_cast<int>(image_width / aspect_ratio);
    image_height_ = (image_height_ < 1) ? 1 : image_height_;

    // Simple Camera
    double focal_length = 1.0;
    double theta = degrees_to_radians(vertical_fov);
    double h = std::tan(theta / 2.0);
    double viewport_height = 2.0 * h * focal_length;
    double viewport_width =
        viewport_height * (static_cast<double>(image_width) / image_height_);

    Vec3 w = unit_vector(camera_center - look_at);
    Vec3 u = unit_vector(cross(up_, w));
    Vec3 v = cross(w, u);

    Vec3 viewport_u = viewport_width * u;
    Vec3 viewport_v = viewport_height * -v;

    // Calculate the pixel deltas in terms of viewport units
    pixel_du_ = viewport_u / image_width_;
    pixel_dv_ = viewport_v / image_height_;

    // Calculation location of "origin" pixel (upper left corner)
    Vec3 viewport_upper_left =
        camera_center_ - focal_length * w - viewport_u / 2.0 - viewport_v / 2.0;
    // pixel center is shifted in from the corner of the viewport
    pixel_origin_ = viewport_upper_left + 0.5 * (pixel_du_ + pixel_dv_);
  }

  void Render(const HittableObject &world) {

    // Render
    std::cout << "P3\n" << image_width_ << " " << image_height_ << "\n255\n";

    for (int j = 0; j < image_height_; j++) {
      std::clog << "\rScanlines remaining: " << image_height_ - j << ' '
                << std::flush;
      for (int i = 0; i < image_width_; i++) {
        Color pixel_color(0, 0, 0);
        for (int sample = 0; sample < samples_per_pixel_; sample++) {
          Ray ray = GetRay(i, j);
          pixel_color += RayColor(world, ray, 0);
        }

        WriteColor(std::cout,
                   pixel_color / static_cast<double>(samples_per_pixel_));
      }
    }

    std::clog
        << "\rDone.                                                     \n";
  }

private:
  double aspect_ratio_;
  int image_width_;
  int image_height_;
  double vertical_fov_;
  int samples_per_pixel_;
  Point3 camera_center_;
  Point3 look_at_;
  Point3 up_;
  Vec3 pixel_origin_;
  Vec3 pixel_du_;
  Vec3 pixel_dv_;
  static constexpr int max_depth_ = 50;

  Ray GetRay(int i, int j) const {
    auto offset = SampleSquare();
    auto pixel_sample = pixel_origin_ + (i + offset.x()) * pixel_du_ +
                        (j + offset.y()) * pixel_dv_;
    auto ray_direction = pixel_sample - camera_center_;
    return Ray{camera_center_, ray_direction};
  }

  Vec3 SampleSquare() const {
    return Vec3{random_double(), random_double(), 0.0};
  }

  Color Lerp(const Color &a, const Color &b, double t) const {
    return (1.0 - t) * a + t * b;
  }

  Color RayColor(const HittableObject &world, const Ray &r, int depth) const {
    if (depth >= max_depth_) {
      return colors::black;
    }

    HitRecord hit_record;
    if (world.Hit(r, Interval<double>(0.001, infinity), hit_record)) {
      Ray scattered;
      Color attenuation;
      if (hit_record.material) {
        if (hit_record.material->Scatter(r, hit_record, attenuation,
                                         scattered)) {
          return attenuation * RayColor(world, scattered, depth + 1);
        }
      }
      return Color(0, 0, 0);
    }

    Vec3 unit_direction = unit_vector(r.direction());
    double a = 0.5 * (unit_direction.y() + 1.0);
    return Lerp(colors::white, colors::light_blue, a);
  }
};
