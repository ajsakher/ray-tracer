#include <iostream>
#include <numbers>

#include <ray-tracer/core/util.hpp>
#include <ray-tracer/display/Canvas.hpp>
#include <ray-tracer/display/CanvasToPPM.hpp>
#include <ray-tracer/spatial/Point.hpp>
#include <ray-tracer/spatial/Transform.hpp>

const RayTracer::Display::Color CANVAS_COLOR(255, 255, 255);

int main() {
    RayTracer::Display::Canvas c(500, 500);
    RayTracer::Spatial::Matrix rotation =
        RayTracer::Spatial::rotate_z(std::numbers::pi / 6);
    RayTracer::Spatial::Point clock_position({100, 0, 0});

    for (int i = 0; i < 12; ++i) {
        RayTracer::Core::write_pixels_around(
            c, 250 + clock_position.get_x(), 250 + clock_position.get_y(), CANVAS_COLOR);
        clock_position = rotation * clock_position;
    }
    bool success = RayTracer::Core::write_file(RayTracer::Display::canvasToPPM(c), "./test-output.ppm");
    if (success) {
        std::cout << "Successfully wrote PPM outfile\n";
    }
    return 0;
}
