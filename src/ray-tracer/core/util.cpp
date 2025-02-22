#include <cmath>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

#include <ray-tracer/core/util.hpp>

namespace RayTracer {
namespace Core {

bool write_file(const std::string& file_content, const std::string& filename) {
    std::ofstream out_file(filename);
    if (out_file.is_open()) {
        out_file << file_content;
        out_file.close();
        return true;
    }
    return false;
}

const double DEFAULT_EPSILON = 0.00001;

bool essentially_equal(double a, double b, double epsilon) {
    return fabs(a - b) <= epsilon;
}

bool essentially_equal(double a, double b) {
    return essentially_equal(a, b, DEFAULT_EPSILON);
}

const std::vector< std::pair<int, int> > POINTS_AROUND = {
    std::make_pair(0, 0),
    std::make_pair(0, 1),
    std::make_pair(1, 1),
    std::make_pair(1, 0),
    std::make_pair(1, -1),
    std::make_pair(0, -1),
    std::make_pair(-1, -1),
    std::make_pair(-1, 0),
    std::make_pair(-1, 1),
};

void write_pixels_around(Display::Canvas& c, size_t x, size_t y, Display::Color color) {
    for (auto& point_adjust : POINTS_AROUND) {
        try {
            c.write_pixel(x + point_adjust.first, y + point_adjust.second, color);
        } catch (std::invalid_argument) {
            continue;
        }
    }
}

}
}
