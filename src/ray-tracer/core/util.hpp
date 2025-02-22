#pragma once

#include <cmath>
#include <fstream>
#include <string>

#include <ray-tracer/display/Canvas.hpp>
#include <ray-tracer/display/Color.hpp>

namespace RayTracer {
namespace Core {

bool write_file(const std::string& file_content, const std::string& filename);

bool essentially_equal(double a, double b, double epsilon);
bool essentially_equal(double a, double b);

void write_pixels_around(Display::Canvas&, size_t, size_t, Display::Color);

}
}
