#include <sstream>
#include <stdexcept>

#include <ray-tracer/display/Canvas.hpp>
#include <ray-tracer/display/Color.hpp>

namespace RayTracer {
namespace Display {

const size_t MAX_CANVAS_DIMENSION = 100000;

Canvas::Canvas(size_t w, size_t h) : width(w), height(h) {
    if (
        width == 0 || height == 0 ||
        width > MAX_CANVAS_DIMENSION ||
        height > MAX_CANVAS_DIMENSION
    ) {
        throw std::invalid_argument("Invalid width or height when creating canvas.");
    }
    canvas = std::vector<Color>(height * width);
}

void Canvas::write_pixel(size_t x, size_t y, Color c) {
    if (y >= this->get_height() || x >= this->get_width()) {
        throw std::invalid_argument("Invalid x or y when attempting to set pixel.");
    }
    canvas[y * width + x] = c;
}

const Color& Canvas::pixel_at(size_t x, size_t y) const {
    if (y >= this->get_height() || x >= this->get_width()) {
        std::stringstream ss;
        ss << "Invalid x or y when attempting to get pixel: " << x << " " << y;
        throw std::invalid_argument(ss.str());
    }
    return canvas[y * width + x];
}

}
}
