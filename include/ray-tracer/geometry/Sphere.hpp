#pragma once

#include <string>
#include <vector>

#include <ray-tracer/display/Material.hpp>
#include <ray-tracer/geometry/Shape.hpp>
#include <ray-tracer/ray-cast/Intersection.hpp>
#include <ray-tracer/spatial/Matrix.hpp>
#include <ray-tracer/spatial/Point.hpp>

namespace RayTracer {
namespace Geometry {

class Sphere : public Shape {
private:
    Spatial::Matrix transform;
    Spatial::Point center;
    Display::Material material;
public:
    Sphere():
        center({0, 0, 0}),
        transform(Spatial::Matrix::get_identity(4)) {
            material.ambient = 1.0;
        }
    const std::string get_name() const { return "sphere"; }
    void set_material(const Display::Material& m) { material = m; }
    const Display::Material& get_material() const { return material; }
    void set_transform(const Spatial::Matrix& t) { transform = t; }
    const Spatial::Matrix& get_transform() const { return transform; }
    const std::vector<double> intersect(const RayCast::Ray&) const;
    const Spatial::Vector normal_at(const Spatial::Point&) const;
};

}
}
