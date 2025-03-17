#pragma once

namespace RayTracer {

namespace Geometry {
    class Shape;
}

namespace RayCast {

class Intersection {
    const RayTracer::Geometry::Shape& object;
    double t;
public:
    Intersection(const RayTracer::Geometry::Shape& o, double t) : object(o), t(t) {}
    bool operator==(const Intersection& b) const {
        return &(b.object) == &(this->object) && b.t == this->t;
    }
    double get_t() const { return t; }
    const RayTracer::Geometry::Shape& get_object() const { return object; };
};

}
}
