#pragma once

#include <ray-tracer/spatial/Matrix.hpp>
#include <ray-tracer/spatial/Point.hpp>
#include <ray-tracer/spatial/Vector.hpp>

namespace RayTracer {
namespace RayCast {

class Ray {
private:
    Spatial::Point origin;
    Spatial::Vector direction;
public:
    Ray(const Spatial::Point& p, const Spatial::Vector& v)
        : origin(p), direction(v) {}
    const Spatial::Point& get_origin() const { return origin; }
    const Spatial::Vector& get_direction() const { return direction; }
    bool operator==(const Ray& lhs) const {
        return origin == lhs.origin && direction == lhs.direction;
    }
};

Spatial::Point position(const Ray&, const double);
Ray transform(const Ray&, const Spatial::Matrix&);

}
}
