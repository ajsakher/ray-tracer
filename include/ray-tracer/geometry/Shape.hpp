#pragma once

#include <string>
#include <vector>

#include <ray-tracer/display/Material.hpp>
#include <ray-tracer/ray-cast/Ray.hpp>
#include <ray-tracer/ray-cast/Intersection.hpp>
#include <ray-tracer/spatial/Point.hpp>
#include <ray-tracer/spatial/Vector.hpp>

namespace RayTracer {
namespace Geometry {

class Shape {
public:
    virtual ~Shape() {}
    virtual const std::string get_name() const = 0;
    virtual const Display::Material& get_material() const = 0;
    virtual const std::vector<double> intersect(const RayCast::Ray&) const = 0;
    virtual const Spatial::Vector normal_at(const Spatial::Point&) const = 0;
};

const std::vector<RayCast::Intersection> get_intersections(const Shape&, const RayCast::Ray&);
const std::unique_ptr<RayCast::Intersection> hit(const std::vector<RayCast::Intersection>&);

}
}
