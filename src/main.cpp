#include "color.h"
#include "constants.h"
#include "point3.h"
#include "ray.h"
#include "vec3.h"
#include <filesystem>
#include <fstream>
#include <print>

void write_file(const std::filesystem::path& path)
{
    std::ofstream out{path, std::ios::out | std::ios::trunc};
    if (!out)
    {
        throw std::runtime_error("cannot open " + path.string());
    }

    std::println(out, "P3");
    std::println(out, "{} {}", config::image_width, config::image_height);
    std::println(out, "{}", config::maxColorNum);

    for (int j{0}; j < config::image_height; ++j)
    {
        for (int i{0}; i < config::image_width; ++i)
        {
            point3 pixel_center = config::pixel00_loc +
                                  (i * config::pixel_delta_w) +
                                  (j * config::pixel_delta_h);

            // note ray_direction is not a unit vector to have less rounding
            // errors
            vec3 ray_direction = pixel_center - config::camera_center;
            ray r{config::camera_center, ray_direction};

            color pixel_color = ray_color(r);
            std::println(out, "{}", pixel_color);
        }
    }
    // here the "out" object should die and release the resource
}

int main()
{
    try
    {
        write_file("output.ppm");
    }
    catch (const std::exception& e)
    {
        std::println(stderr, "Error: {}", e.what());
    }
    catch (...)
    {
        std::println(stderr, "Unknown error");
    }
}
