#include <iostream>

#include <ray-tracer/core/util.hpp>
#include <ray-tracer/display/Canvas.hpp>
#include <ray-tracer/display/CanvasToPPM.hpp>
#include <ray-tracer/display/Color.hpp>
#include <ray-tracer/display/Lighting.hpp>
#include <ray-tracer/display/Material.hpp>
#include <ray-tracer/display/PointLight.hpp>
#include <ray-tracer/geometry/Shape.hpp>
#include <ray-tracer/geometry/Sphere.hpp>
#include <ray-tracer/ray-cast/Ray.hpp>
#include <ray-tracer/spatial/Point.hpp>
#include <ray-tracer/spatial/Transform.hpp>
#include <ray-tracer/spatial/Vector.hpp>

const RayTracer::Display::Color CANVAS_COLOR(0, 1.0, 0);

const double CANVAS_SIZE = 500;

int main() {
    RayTracer::Display::Canvas c(CANVAS_SIZE, CANVAS_SIZE);
    RayTracer::Geometry::Sphere s;

    RayTracer::Display::Material m;
    m.color = RayTracer::Display::Color(1.0, 0.2, 1.0);
    RayTracer::Display::PointLight pl(
        RayTracer::Spatial::Point(-10, 10, -10),
        RayTracer::Display::Color(1, 1, 1)
    );
    s.set_material(m);

    double wall_z = 10.0;
    double wall_size = 7.0;
    double pixel_size = wall_size / CANVAS_SIZE;
    double half = wall_size / 2.0;
    RayTracer::Spatial::Point origin({0, 0, -10});

    for (int i = 0; i < CANVAS_SIZE; ++i) {
        double world_y = half - pixel_size * i;
        for (int j = 0; j < CANVAS_SIZE; ++j) {
            double world_x = pixel_size * j - half;
            RayTracer::Spatial::Point wall_position({world_x, world_y, wall_z});
            RayTracer::RayCast::Ray r(
                origin,
                (wall_position - origin).normalize()
            );
            const std::unique_ptr<RayTracer::RayCast::Intersection> hit_i = RayTracer::Geometry::hit(RayTracer::Geometry::get_intersections(s, r));
            if (hit_i) {
                RayTracer::Spatial::Point hit_point = RayTracer::RayCast::position(r, hit_i->get_t());
                RayTracer::Spatial::Vector hit_normal = hit_i->get_object().normal_at(hit_point);
                RayTracer::Spatial::Vector eye_v = -r.get_direction();
                RayTracer::Display::Color draw_color =
                    RayTracer::Display::lighting(
                        hit_i->get_object().get_material(),
                        pl,
                        hit_point,
                        eye_v,
                        hit_normal
                    );
                c.write_pixel(i, j, draw_color);
            }
        }
    }
    bool success = RayTracer::Core::write_file(RayTracer::Display::canvasToPPM(c), "./test-output.ppm");
    if (success) {
        std::cout << "Successfully wrote PPM outfile\n";
    }
    return 0;
}
