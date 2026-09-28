#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "point3.h"
#include <gsl/util>

namespace config
{
// Image configs
constexpr double test_image_width{256};
constexpr double test_image_height{256};
constexpr double maxDoubleColorValue{255.999};
constexpr int maxColorNum{255};

// define image width and aspect ration
constexpr double aspect_ratio = 16.0 / 9.0;
constexpr int image_width = 400;

// from the aspect ration and the width we calculate the height
constexpr int image_height =
    std::max(gsl::narrow_cast<int>(image_width / aspect_ratio), 1);

// Camera
//  define viewpoint, note here its ok if the numbers are less than 1
constexpr double viewport_height{2.0};
constexpr double viewport_width =
    viewport_height * (static_cast<double>(image_width) / image_height);
constexpr double focal_length{1.0};
point3 camera_center{0, 0, 0};

// Calculate the vectors across the horizontal and down the vertical viewport
// edges.
vec3 viewport_vec_width{viewport_width, 0, 0};
vec3 viewport_vec_height{0, -viewport_height, 0};

// Calculate the horizontal and vertical delta vectors from pixel to pixel
vec3 pixel_delta_w = viewport_vec_width / image_width;
vec3 pixel_delta_h = viewport_vec_height / image_height;

// Calculate the location of the upper left pixel.
point3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) -
                             viewport_vec_width / 2 - viewport_vec_height / 2;
point3 pixel00_loc =
    viewport_upper_left + 0.5 * (pixel_delta_w + pixel_delta_h);

} // namespace config

#endif
