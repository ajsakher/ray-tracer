#include <iostream>
#include <vector>

#include <ray-tracer/geometry/Shape.hpp>
#include <ray-tracer/geometry/Sphere.hpp>
#include <ray-tracer/ray-cast/Intersection.hpp>
#include <ray-tracer/ray-cast/Ray.hpp>
#include <ray-tracer/spatial/Point.hpp>
#include <ray-tracer/spatial/Vector.hpp>

namespace RayTracer {
namespace Geometry {

const std::vector<double> Sphere::intersect(const RayCast::Ray& init_r) const {
    const RayCast::Ray r = RayCast::transform(init_r, this->get_transform().invert());
    Spatial::Vector sphere_to_ray = r.get_origin() - this->center;
    double a = r.get_direction().dot(r.get_direction());
    double b = 2 * r.get_direction().dot(sphere_to_ray);
    double c = sphere_to_ray.dot(sphere_to_ray) - 1;
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return std::vector<double>();
    }
    return std::vector<double>({
        (-b - std::sqrt(discriminant)) / (2 * a),
        (-b + std::sqrt(discriminant)) / (2 * a),
    });
}

const Spatial::Vector Sphere::normal_at(const Spatial::Point& p) const {
    Spatial::Point object_space_p = this->get_transform().invert() * p;
    Spatial::Vector object_normal = object_space_p - this->center;
    Spatial::Vector world_normal = this->get_transform().invert().transpose() * object_normal;
    return world_normal.normalize();
}

}
}
