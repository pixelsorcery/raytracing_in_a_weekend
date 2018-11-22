#include <iostream>
#include <cassert>
#include <limits>
#include "stb_image_write.h"
#include "sphere.h"
#include "hitable_list.h"

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

using vec3 = vec3_t<datatype>;
using ray = ray_t<datatype>;
using hit_record = hit_record_t<datatype>;
using hitable = hitable_t<datatype>;
using hitable_list = hitable_list_t<datatype>;
using sphere = sphere_t<datatype>;

vec3 color(const ray& r, hitable* world)
{
    hit_record rec;
    if (world->hit(r, 0.0f, std::numeric_limits<float>::max(), rec))
    {

    }
    if (t > 0)
    {
        vec3 N = (r.point_at_parameter(t) - vec3(0.0f, 0.0f, -1.0f));
        return 0.5f * vec3(N.x() + 1, N.y() + 1, N.z() + 1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5f * (unit_direction.y() + 1.0f);
    return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}

int main()
{
    int nx = WIDTH;
    int ny = HEIGHT;

    vec3 lower_left_corner(-WIDTH/2, -HEIGHT/2, -HEIGHT/2);
    vec3 horizontal(WIDTH, 0.0, 0.0);
    vec3 vertical(0.0, HEIGHT, 0.0);
    vec3 origin(0.0f, 0.0f, 0.0f);

    hitable* list[2];
    list[0] = new sphere(vec3(0, 0, -1), 0.5);
    list[1] = new sphere(vec3(0, -100.5, -1), 100);
    hitable *world = new hitable_list(list, 2);

    for (int j = ny-1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            vec3 col = color(r);
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