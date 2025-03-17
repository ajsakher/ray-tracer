#include <cmath>

#include <ray-tracer/core/Tuple.hpp>
#include <ray-tracer/core/util.hpp>
#include <ray-tracer/spatial/Point.hpp>
#include <ray-tracer/spatial/Vector.hpp>

namespace RayTracer {
namespace Spatial {

Vector::Vector() {
    values = { 0, 0, 0, 0 };
}

Vector::Vector(double _x, double _y, double _z) {
   values = { _x, _y, _z, 0 };
}

Vector Vector::operator+(const Vector& rhs) const {
    return Vector(this->get_x() + rhs.get_x(), this->get_y() + rhs.get_y(), this->get_z() + rhs.get_z());
}

Vector& Vector::operator+=(const Vector& rhs) {
    this->values[0] += rhs.get_x();
    this->values[1] += rhs.get_y();
    this->values[2] += rhs.get_z();
    return *this;
}

Vector Vector::operator-(const Vector& rhs) const {
    return Vector(this->get_x() - rhs.get_x(), this->get_y() - rhs.get_y(), this->get_z() - rhs.get_z());
}

Vector& Vector::operator-=(const Vector& rhs) {
    this->values[0] -= rhs.get_x();
    this->values[1] -= rhs.get_y();
    this->values[2] -= rhs.get_z();
    return *this;
}

Vector Vector::operator-() const {
    return Vector(-get_x(), -get_y(), -get_z());
}

Vector Vector::operator*(const double scalar) const {
    return Vector(scalar * get_x(), scalar * get_y(), scalar * get_z());
}

Vector& Vector::operator*=(const double scalar) {
    this->values[0] *= scalar;
    this->values[1] *= scalar;
    this->values[2] *= scalar;
    return *this;
}

Vector Vector::operator/(const double scalar) const {
    return Vector(get_x() / scalar, get_y() / scalar, get_z() / scalar);
}

Vector& Vector::operator/=(const double scalar) {
    this->values[0] /= scalar;
    this->values[1] /= scalar;
    this->values[2] /= scalar;
    return *this;
}

bool Vector::operator==(const Vector& b) const {
    return Core::essentially_equal(this->get_x(), b.get_x()) &&
        Core::essentially_equal(this->get_y(), b.get_y()) &&
        Core::essentially_equal(this->get_z(), b.get_z());
}

double Vector::magnitude() const {
    return std::sqrt(get_x() * get_x() + get_y() * get_y() + get_z() * get_z());
}

Vector Vector::normalize() const {
    double magnitude = this->magnitude();
    return Vector(get_x() / magnitude, get_y() / magnitude, get_z() / magnitude);
}

double compute_dot_product(const Vector& a, const Vector& b) {
    return a.get_x() * b.get_x() +
        a.get_y() * b.get_y() +
        a.get_z() * b.get_z();
}

double dot(const Vector& a, const Vector& b) {
    return compute_dot_product(a, b);
}

double Vector::dot(const Vector& v) const {
    return compute_dot_product(*this, v);
}

Vector compute_cross_product(const Vector& a, const Vector& b) {
    return Vector(
        a.get_y() * b.get_z() - a.get_z() * b.get_y(),
        a.get_z() * b.get_x() - a.get_x() * b.get_z(),
        a.get_x() * b.get_y() - a.get_y() * b.get_x()
    );
}

Vector Vector::cross(const Vector& v) const {
    return compute_cross_product(*this, v);
}

Vector cross(const Vector& a, const Vector& b) {
    return compute_cross_product(a, b);
}

Vector Vector::reflect(const Vector& normal) const {
    return *this - normal * 2 * this->dot(normal);
}

}
} // namespace RayTracer

