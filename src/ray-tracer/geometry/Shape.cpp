#include <iostream>
#include <vector>

#include <ray-tracer/geometry/Shape.hpp>
#include <ray-tracer/ray-cast/Intersection.hpp>

namespace RayTracer {
namespace Geometry {

const std::vector<RayCast::Intersection> get_intersections(const Shape& s, const RayCast::Ray& r) {
    const std::vector<double> intersections = s.intersect(r);
    std::vector<RayCast::Intersection> result;
    result.reserve(intersections.size());
    for (int i = 0; i < intersections.size(); ++i) {
        //std::cout << "INTERSECT SHAPE: " << s << "\n";
        result.push_back(RayCast::Intersection(s, intersections.at(i)));
    }
    return result;
}

const std::unique_ptr<RayCast::Intersection> hit(const std::vector<RayCast::Intersection>& intersections) {
    const RayCast::Intersection* hit_i = nullptr;
    for (const auto& intersection : intersections) {
        if (intersection.get_t() >= 0) {
            if (!hit_i || hit_i->get_t() > intersection.get_t()) {
                hit_i = &intersection;
            }
        }
    }
    if (!hit_i) {
        return nullptr;
    }
    return std::make_unique<RayCast::Intersection>(RayCast::Intersection(hit_i->get_object(), hit_i->get_t()));
}

}
}
