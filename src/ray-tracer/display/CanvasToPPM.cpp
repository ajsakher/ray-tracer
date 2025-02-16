#include <algorithm>
#include <cmath>
#include <sstream>
#include <string>

#include <ray-tracer/display/Canvas.hpp>
#include <ray-tracer/display/CanvasToPPM.hpp>
#include <ray-tracer/display/Color.hpp>

namespace RayTracer {
namespace Display {

const std::string PPM_VERSION = "P3";
const int PPM_SCALE = 255;

int get_scaled_pixel(double pixel_value) {
    const int pixel_scaled = std::round(pixel_value * PPM_SCALE);
    return std::min(std::max(0, pixel_scaled), PPM_SCALE);
}

std::string canvasToPPM(const Canvas& c) {
    std::stringstream ss;
    ss << PPM_VERSION << "\n";
    ss << c.get_width() << " " << c.get_height() << "\n";
    ss << PPM_SCALE << "\n";
    for (size_t i = 0; i < c.get_height(); ++i) {
        for (size_t j = 0; j < c.get_width(); ++j) {
            if (j > 0) {
                if (j % 5 == 0) {
                    ss << "\n";
                } else {
                    ss << " ";
                }
            }
            const Color& pixel = c.pixel_at(j, i);
            ss << get_scaled_pixel(pixel.get_red()) << " "
                << get_scaled_pixel(pixel.get_green()) << " "
                << get_scaled_pixel(pixel.get_blue());
        }
        ss << "\n";
    }
    ss << "\n";
    return ss.str();
}

}
}
