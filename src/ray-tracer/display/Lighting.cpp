#include <ray-tracer/display/Color.hpp>
#include <ray-tracer/display/Material.hpp>
#include <ray-tracer/display/PointLight.hpp>
#include <ray-tracer/spatial/Point.hpp>
#include <ray-tracer/spatial/Vector.hpp>

namespace RayTracer {
namespace Display {

Color lighting(
    const Material& m,
    const PointLight& pl,
    const Spatial::Point& position,
    const Spatial::Vector& eye_vector,
    const Spatial::Vector& surface_normal
) {
    Color effective_color = m.color * pl.get_intensity();
    Spatial::Vector to_light = (pl.get_position() - position).normalize();
    Color ambient = effective_color * m.ambient;

    Color diffuse;
    Color specular;
    double light_dot_normal = surface_normal.dot(to_light);
    if (light_dot_normal > 0) {
        diffuse = effective_color * m.diffuse * light_dot_normal;
        Spatial::Vector reflect_v = (-to_light).reflect(surface_normal);
        double reflect_dot_eye = reflect_v.dot(eye_vector);
        if (reflect_dot_eye > 0) {
            double factor = std::pow(reflect_dot_eye, m.shininess);
            specular = pl.get_intensity() * m.specular * factor;
        }
    }
    return ambient + diffuse + specular;

}

}
} // namespace RayTracer
