# Ray Tracing

C++ project following [Raytracing in Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html). The project generates a scene of spheres and outputs a `.ppm` image of randomly generated spheres of metal, dielectric or matte surfaces using the CPU. See `eg/` to see sample output images.

## Features

The project includes:

- Anti-aliasing.
- Depth of field.
- Matte, metallic and dielectric materials.

## Requirements

- C++20 compatible compiler.
- GNU Make 4.x recommended.

## Usage

```shell
make

./build/rt.out <IMAGE_WIDTH> > <IMAGE_LOCATION.ppm>
```

## Image output

- For a high quality image(s) increase `g_SAMPLES_PER_PIXEL`.

## Future Improvements

- [ ] Utilise GPU instead of CPU
- [ ] Multithreaded rendering
