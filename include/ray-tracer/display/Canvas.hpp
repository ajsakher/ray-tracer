#pragma once

#include <vector>

#include <ray-tracer/display/Color.hpp>

namespace RayTracer {
namespace Display {

class Canvas {
private:
    int width;
    int height;
    std::vector<Color> canvas;
public:
    Canvas(size_t width, size_t height);

    const size_t get_width() const { return width; }
    const size_t get_height() const { return height; }
    void write_pixel(size_t x, size_t y, Color c);
    const Color& pixel_at(size_t x, size_t y) const;
};

}
}
