#include <ray-tracer/core/Tuple.hpp>
#include <ray-tracer/core/util.hpp>
#include <ray-tracer/spatial/Point.hpp>
#include <ray-tracer/spatial/Vector.hpp>

namespace RayTracer {
namespace Spatial {

Point::Point() {
    values = { 0.0, 0.0, 0.0, 1.0 };
}

Point::Point(double _x, double _y, double _z) {
    values = { _x, _y, _z, 1.0 };
}

Point Point::operator+(const Vector& v) const {
    return Point(this->get_x() + v.get_x(), this->get_y() + v.get_y(), this->get_z() + v.get_z());
}

Point Point::operator-(const Vector& v) const {
    return Point(this->get_x() - v.get_x(), this->get_y() - v.get_y(), this->get_z() - v.get_z());
}

Vector Point::operator-(const Point& v) const {
    return Vector(this->get_x() - v.get_x(), this->get_y() - v.get_y(), this->get_z() - v.get_z());
}

Point& Point::operator+=(const Vector& v) {
    this->values[0] += v.get_x();
    this->values[1]+= v.get_y();
    this->values[2] += v.get_z();
    return *this;
}

Point& Point::operator-=(const Vector& v) {
    this->values[0] -= v.get_x();
    this->values[1] -= v.get_y();
    this->values[2] -= v.get_z();
    return *this;
}

bool Point::operator==(const Point& p) const {
    return Core::essentially_equal(this->get_x(), p.get_x()) &&
        Core::essentially_equal(this->get_y(), p.get_y()) &&
        Core::essentially_equal(this->get_z(), p.get_z());
}

Point Point::operator-() const {
    return Point(-get_x(), -get_y(), -get_z());
}

}
}
