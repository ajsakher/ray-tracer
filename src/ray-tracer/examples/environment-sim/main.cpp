#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

#include <ray-tracer/core/util.hpp>
#include <ray-tracer/display/Canvas.hpp>
#include <ray-tracer/display/CanvasToPPM.hpp>
#include <ray-tracer/examples/environment-sim/Environment.hpp>
#include <ray-tracer/examples/environment-sim/EnvironmentSim.hpp>
#include <ray-tracer/examples/environment-sim/Projectile.hpp>
#include <ray-tracer/spatial/Point.hpp>
#include <ray-tracer/spatial/Vector.hpp>

const RayTracer::Display::Color CANVAS_COLOR(1.0, 0, 0);

int main(int argc, char* argv[]) {
    if (argc != 1 && argc != 13) {
        std::cout << "Argument format: gravity_x gravity_y gravity_z"
            << " wind_x wind_y wind_z position_x position_y position_z"
            << " velocity_x velocity_y velocity_z\n";
        return -1;
    }
    RayTracer::Spatial::Vector gravity(0, -0.1, 0);
    RayTracer::Spatial::Vector wind(-0.01, 0.0, 0.0);
    RayTracer::EnvironmentSim::Environment e(gravity, wind);

    RayTracer::Spatial::Point start_position(0, 1, 0);
    RayTracer::Spatial::Vector start_velocity(1, 1.8, 0);
    RayTracer::EnvironmentSim::Projectile projectile(start_position, start_velocity.normalize() * 11.25);

    RayTracer::Display::Canvas c(900, 550);

    int num_ticks = 0;
    while (projectile.get_position().get_y() > 0.0) {
        projectile = RayTracer::EnvironmentSim::tick(e, projectile);
        RayTracer::Core::write_pixels_around(
            c, projectile.get_position().get_x(), c.get_height() - projectile.get_position().get_y(), CANVAS_COLOR);
        ++num_ticks;
    }
    std::cout << "Final projectile position: (" << projectile.get_position().get_x()
        << ", " << projectile.get_position().get_y() << ", " << projectile.get_position().get_z()
        << ")\n";
    std::cout << "Number of ticks to hit y == 0: " << num_ticks << std::endl;
    bool success = RayTracer::Core::write_file(RayTracer::Display::canvasToPPM(c), "./test-output.ppm");
    if (success) {
        std::cout << "Successfully wrote PPM outfile\n";
    }
    return 0;
}
