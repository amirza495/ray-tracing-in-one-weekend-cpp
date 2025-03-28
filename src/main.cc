#include "camera.h"
#include "geometry/hittable_object_list.h"
#include "geometry/sphere.h"
#include "material/lambertian.h"
#include "material/metal.h"
#include "vec3.h"

#include <iostream>

int main() {

  // Image
  const double aspect_ratio = 16.0 / 9.0;
  const int image_width = 1600;
  double vfov = 60.0;
  const int samples_per_pixel = 500;

  Camera camera(aspect_ratio, image_width, vfov, samples_per_pixel,
                Point3{-12, 6, 1}, Point3{0, 0, -1});

  HittableObjectList world;
  // Diffuse object
  world.Add(std::make_unique<Sphere>(
      Point3{0, 1, -1.2}, 1,
      std::make_unique<Lambertian>(Color{0.1, 0.2, 0.5})));

  // Metal objects
  world.Add(std::make_unique<Sphere>(
      Point3{-4, 1, -1}, 1,
      std::make_unique<Metal>(Color{0.8, 0.8, 0.8}, 0.0)));
  world.Add(std::make_unique<Sphere>(
      Point3{4, 1, -1}, 1, std::make_unique<Metal>(Color{0.8, 0.6, 0.2}, 0.0)));

  // generate a bunch of random objects in random places
  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      auto choose_mat = random_double();
      Point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

      if (((center - Point3{4, 0.2, 0}).length() > 0.9) &&
          ((center - Point3{0, 0.2, 0}).length() > 0.9) &&
          ((center - Point3{-4, 0.2, 0}).length() > 0.9)) {
        if (choose_mat > 0.8) {
          // diffuse
          world.Add(std::make_unique<Sphere>(
              center, 0.2,
              std::make_unique<Lambertian>(Color::random() * Color::random())));

        } else {
          // metal
          world.Add(std::make_unique<Sphere>(
              center, 0.2,
              std::make_unique<Metal>(Color::random(0.5, 1.0),
                                      0.5 * random_double())));
        }
      }
    }
  }

  // Ground
  world.Add(std::make_unique<Sphere>(
      Point3{0, -10000, -1}, 10000,
      std::make_unique<Lambertian>(Color{0.5, 0.5, 0.5})));

  camera.Render(world);

  return 0;
}
