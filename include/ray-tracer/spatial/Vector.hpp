#ifndef RAYTRACER_SPATIAL_VECTOR_HPP
#define RAYTRACER_SPATIAL_VECTOR_HPP

#include <ray-tracer/core/Tuple.hpp>

namespace RayTracer {
namespace Spatial {

class Point;

class Vector : public Core::Tuple {
public:
    Vector();
    double get_x() const { return this->values[0]; }
    double get_y() const { return this->values[1]; }
    double get_z() const { return this->values[2]; }
    double get_w() const { return this->values[3]; }
    Vector(double x, double y, double z);

    Vector operator+(const Vector&) const;
    Vector& operator+=(const Vector&);
    Vector operator-(const Vector&) const;
    Vector& operator-=(const Vector&);
    Vector operator*(const double) const;
    Vector& operator*=(const double) ;
    Vector operator/(const double) const;
    Vector& operator/=(const double) ;

    Vector operator-() const;

    bool operator==(const Vector& b) const;

    double magnitude() const;
    Vector normalize() const;
    double dot(const Vector& v) const;
    Vector cross(const Vector& v) const;

    Vector reflect(const Vector&) const;

    friend double dot(const Vector& a, const Vector& b);
    friend Vector cross(const Vector& a, const Vector& b);
};

double dot(const Vector& a, const Vector& b);
Vector cross(const Vector& a, const Vector& b);

}
}

#endif
