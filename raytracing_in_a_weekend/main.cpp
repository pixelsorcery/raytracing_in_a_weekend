#include <iostream>
#include <cassert>
#include <limits>
#include <random>
#include "stb_image_write.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"

#if DEBUG
#define ASSERT(x) assert(x);
#else
#define ASSERT(x)
#endif

using namespace std;

const int32_t WIDTH = 1024;
const int32_t HEIGHT = 768;

uint32_t image[WIDTH * HEIGHT];

template <typename T>
constexpr uint32_t make_rgb(T r, T g, T b)
{
    return r | g << 8 | b << 16 | 0xff << 24;
}

// test
static_assert(make_rgb(4, 3, 2) == 0xff020304, "constexpr is not constexpr\n");

// todo: change this maybe?
using datatype = float;

using vec3         = vec3_t<datatype>;
using ray          = ray_t<datatype>;
using hit_record   = hit_record_t<datatype>;
using hitable      = hitable_t<datatype>;
using hitable_list = hitable_list_t<datatype>;
using sphere       = sphere_t<datatype>;
using camera       = camera_t<datatype>;

std::mt19937 rng(123);

vec3 random_in_unit_sphere()
{
    std::uniform_real_distribution<datatype> rand_dis(0, 1);
    vec3 p;
    do
    {
        p = 2.0f * vec3(rand_dis(rng), rand_dis(rng), rand_dis(rng)) - vec3(1, 1, 1);
    } while (p.squared_length() >= 1.0);

    return p;
}

vec3 color(const ray& r, hitable* world, int depth)
{
    hit_record rec;

    if (world->hit(r, 0.001f, std::numeric_limits<float>::max(), rec))
    {
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.pMat->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * color(scattered, world, depth + 1);
        }
        else
        {
            return vec3(0.0f, 0.0f, 0.0f);
        }
    }
    else
    {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5f * (unit_direction.y() + 1.0f);
        return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
    }
}

int main()
{
    std::uniform_real_distribution<datatype> rand_dis(0.0, 1.0);
    int nx = WIDTH;
    int ny = HEIGHT;
    int ns = 100;

    hitable* list[4];
    // todo: make all of these unique pointers
    list[0] = new sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f, new lambertian<datatype>(vec3(0.8f, 0.3f, 0.3f)));
    list[1] = new sphere(vec3(0.0f, -100.5f, -1.0f), 100.0f, new lambertian<datatype>(vec3(0.8f, 0.8f, 0.0f)));
    list[2] = new sphere(vec3(1.0f, 0.0f, -1.0f), 0.5f, new metal<datatype>(vec3(0.8f, 0.6f, 0.2f)));
    list[3] = new sphere(vec3(-1.0f, -0.0, -1.0f), 0.5f, new metal<datatype>(vec3(0.8f, 0.8f, 0.8f)));
    hitable *world = new hitable_list(list, 4);
    camera cam;

    for (int j = ny-1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            vec3 col(0.0f, 0.0f, 0.0f);
            for (int s = 0; s < ns; s++)
            {
                float u = float(i + rand_dis(rng)) / float(nx);
                float v = float(j + rand_dis(rng)) / float(ny);
                ray r = cam.get_ray(u, v);
                //vec3 p = r.point_at_parameter(2.0);
                col += color(r, world, 0);
            }
            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            image[(ny - 1 - j) * WIDTH + i] = make_rgb(ir, ig, ib);
        }
    }

    int result = stbi_write_bmp("output.bmp", WIDTH, HEIGHT, 4, image);

    ASSERT(result != 0);

    return 0;
}