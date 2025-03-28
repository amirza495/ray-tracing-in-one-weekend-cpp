## Ray Tracing in One Weekend

I followed [this book](https://raytracing.github.io/books/RayTracingInOneWeekend.html) to create a basic ray tracer.

I was mostly true to the book, but made some stylistic changes to the code. Additionally, I did not implement the sections on dielectric materials and defocus blur.

### Building and running

The project is runnable like a standard cmake project:
```bash
mkdir build && cd build
cmake ..
make
./main > image.ppm
```

This will produce a ppm image, which can be opened in most standard image viewers.


### Converting ppm image to jpeg

The ppm image can be converted into jpeg using `ffmpeg`.
```bash
ffmpeg -i input_image.ppm output_image_name.jpg
```
