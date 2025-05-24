#include "rtutil.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

int main() {

    // clang++ -std=c++11 -stdlib=libc++ main.cpp -o raytracer

    hittable_list world;

// Mirror
    auto ground_material = make_shared<metal>(color(0.7, 0.6, 0.8), 0.02);
    world.add(make_shared<sphere>(point3(0, -2003, 0), 2000, ground_material));

// Twisting helix of spheres
    const int num_spheres = 100;
    const double radius = 2.5;
    const double height = 5.0;
    const double twist = 5.0;

    for (int i = 0; i < num_spheres; ++i) {
        double t = i / double(num_spheres);
        double angle = twist * 2 * pi * t;
        double x = radius * cos(angle);
        double z = radius * sin(angle);
        double y = height * (t - 0.5);

        double scale = 0.1 + 0.3 * sin(6 * pi * t);
        auto center = point3(x, y, z);

        shared_ptr<material> mat;

        if (i % 3 == 0) {
            mat = make_shared<dielectric>(1.5);
        } else if (i % 3 == 1) {
            mat = make_shared<lambertian>(color(0.1 + 0.8 * t, 0.2, 0.6 + 0.4 * (1 - t)));
        } else {
            mat = make_shared<metal>(color(0.6, 0.6 * (1 - t), 0.9), 0.05);
        }

        world.add(make_shared<sphere>(center, scale, mat));
    }

// Central glowing orb
    auto core_material = make_shared<lambertian>(color(4.0, 4.0, 4.0));
    world.add(make_shared<sphere>(point3(0, 0, 0), 0.6, core_material));

// Camera setup
    camera cam;
    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 800;
    cam.samples_per_pixel = 400;
    cam.max_depth         = 70;

    cam.vfov     = 50;
    cam.lookfrom = point3(6, 0, 6);
    cam.lookat   = point3(0, -0.5, 0);
    cam.vup      = vec3(0, 1, 0);

    cam.defocus_angle = 0.2;
    cam.focus_dist    = 7.0;


    cam.render(world);
}