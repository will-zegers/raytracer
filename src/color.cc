#include <iostream>

#include "raytracer/color.h"

void WriteColor(std::ostream &out, Color pixel_color, int samples_per_pixel) {
    auto scale = 1.0 / samples_per_pixel;

    // Divide the color by the number of samples.
    auto r = sqrt(pixel_color.r()*scale);
    auto g = sqrt(pixel_color.g()*scale);
    auto b = sqrt(pixel_color.b()*scale);

    // Write the translated [0,255] value of each Color component.
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}
