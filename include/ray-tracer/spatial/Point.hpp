#ifndef RAYTRACER_SPATIAL_POINT_HPP
#define RAYTRACER_SPATIAL_POINT_HPP

#include <ray-tracer/core/Tuple.hpp>

namespace RayTracer {
namespace Spatial {

class Vector;

class Point : public Core::Tuple {
public:
    Point();
    Point(double x, double y, double z);
    double get_x() const { return this->values[0]; }
    double get_y() const { return this->values[1]; }
    double get_z() const { return this->values[2]; }
    double get_w() const { return this->values[3]; }

    Point operator+(const Vector&) const;
    Point operator-(const Vector&) const;
    Vector operator-(const Point&) const;

    Point& operator+=(const Vector&);
    Point& operator-=(const Vector&);

    bool operator==(const Point&) const;

    Point operator-() const;
};

}
}

#endif
